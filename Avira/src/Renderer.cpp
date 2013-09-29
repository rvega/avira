#include "Renderer.h"
#include "constantes.h"
#include "AnimacionEscenaPajaro.h"
#include "AnimacionEscenaAvira.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
Renderer::Renderer():
   fullscreen(false)
{
   ofSeedRandom();

   estado = "ESPERANDO";
   timer = ofGetElapsedTimef();

   Animacion* escenaAvira = new AnimacionEscenaAvira(0,0);
   animaciones.push_back(escenaAvira);

    Animacion* escenaPajaro = new AnimacionEscenaPajaro(0, 0);
   animaciones.push_back(escenaPajaro);

   ofRegisterGetMessages(this);
}

Renderer::~Renderer() {
   for(unsigned int i = 0; i < animaciones.size(); i++) {
      delete animaciones.at(i);
   }
   ofUnregisterGetMessages(this);
}

//===========================================//
//  MENSAJES QUE LLEGAN DESDE OTROS OBJETOS  //
//===========================================//
void Renderer::gotMessage(ofMessage& msg){
   if(msg.message == "FULLSCREEN_ON"){
      fullscreen = true;
   }
   else if(msg.message == "FULLSCREEN_OFF"){
      fullscreen = false;
   }
}

//========//
//  DRAW  //
//========//
template<class imageType>
void Renderer::drawImage(int x, int y, string title, imageType *img){
   ofPushMatrix();
   ofSetColor(255,255,255);
   ofTranslate(x, y);
   ofRect(0,0,IMAGEN_PEQUENA_WIDTH+2, IMAGEN_PEQUENA_HEIGHT+2);
   ofDrawBitmapString(title, 0, -5);
   img->draw(1, 1, IMAGEN_PEQUENA_WIDTH, IMAGEN_PEQUENA_HEIGHT);
   ofPopMatrix();
}

void Renderer::drawInterimImages(vector<ofxCvImage*> interimImages){
   drawImage(POSICION_1_X, POSICION_1_Y, "Fondo:", interimImages.at(0));
   drawImage(POSICION_2_X, POSICION_2_Y, "Work:", interimImages.at(1));
}

void Renderer::drawOutputImage(ofxCvImage* outputImage){
   if(!fullscreen){
      drawImage(POSICION_3_X, POSICION_3_Y, "Output:", outputImage);
   }
   else{
      outputImage->draw(0, 0, IMAGEN_GRANDE_WIDTH, IMAGEN_GRANDE_HEIGHT);
   }
}

void Renderer::drawAnimaciones(map<int,Persona> gente){
   // Dibuje borde de blobs
   if(!fullscreen){
      for(unsigned int i=0; i<gente.size(); i++){
         if(gente.at(i).getActiva()){
            gente.at(i).drawBorder();
         }
      }
   }

   triggerAnimacion(gente);

   // dibuje animaciones
   for(unsigned int i=0; i<animaciones.size(); i++){
       animaciones.at(i)->setXPersona(gente.at(personaActiva).getX());
       animaciones.at(i)->setYPersona(gente.at(personaActiva).getY());
       animaciones.at(i)->draw();
    }
}

void Renderer::triggerAnimacion(map<int,Persona> gente){
    // Escoja cual animacion disparar TODO
    if(estado == "ESPERANDO"){
        if(ofGetElapsedTimef() - timer > 10){
            estado = "BUSCANDO_GENTE_QUIETA";
        }
    }

    if(estado == "BUSCANDO_GENTE_QUIETA"){
        for(unsigned int i=0; i<NUM_PERSONAS; i++){
            if(gente.at(i).getActiva() && gente.at(i).getQuieta()){
                estado = "ANIMANDO";
                int cualAnimacion = ofRandom( animaciones.size() );
                animacionActiva = animaciones.at(cualAnimacion);
                personaActiva = i;
                animacionActiva->setX( gente.at(i).getX() );
                animacionActiva->setY( gente.at(i).getY() );
                animacionActiva->setXPersona( gente.at(i).getX() );
                animacionActiva->setYPersona( gente.at(i).getY() );
                animacionActiva->play();
                break;
            }
        }
    }

    if(estado == "ANIMANDO"){
        if(animacionActiva->isComplete()){
            estado = "ESPERANDO";
            timer = ofGetElapsedTimef();
        }
    }
}
