#include "Renderer.h",
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
Renderer::Renderer():
   fullscreen(false)
{
   Animacion* escena1 = new Animacion(600, 400, 30);
   escena1->setPath("animaciones/accesorios/mapa");
   escena1->play();
   animaciones.push_back(escena1);

   ofRegisterGetMessages(this);
}

Renderer::~Renderer() {
   for(int i = 0; i < animaciones.size(); i++) {
      delete animaciones.at(i);
   }
   ofUnregisterGetMessages(this);
}

//===========//
//  SETTERS  //
//===========//
void Renderer::setTitle1(string val){
   title1 = val;
}

void Renderer::setTitle2(string val){
   title2 = val;
}

void Renderer::setTitle3(string val){
   title3 = val;
}

void Renderer::setTitle4(string val){
   title4 = val;
}

void Renderer::setImgOutput(ofxCvColorImage val){
   imgOutput = val;
}

void Renderer::setImg1(ofxCvGrayscaleImage val){
   img1 = val;
}

void Renderer::setImg2(ofxCvGrayscaleImage val){
   img2 = val;
}

void Renderer::setImg3(ofxCvGrayscaleImage val){
   img3 = val;
}

void Renderer::setImg4(ofxCvGrayscaleImage val){
   img4 = val;
}

void Renderer::setGente( map<int,Persona> val ){
   gente = val;
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
void Renderer::drawImage(int x, int y, string title, imageType img){
   ofPushMatrix();
   ofTranslate(x, y);
   ofRect(0,0,IMAGEN_PEQUENA_WIDTH+2, IMAGEN_PEQUENA_HEIGHT+2);
   ofDrawBitmapString(title, 0, -5);
   img.draw(1, 1, IMAGEN_PEQUENA_WIDTH, IMAGEN_PEQUENA_HEIGHT);
   ofPopMatrix();
}

void Renderer::draw(){
   ofPushMatrix();
   ofPushStyle();
   ofSetColor(255,255,255);
   if(!fullscreen){
      drawImage<ofxCvGrayscaleImage>(POSICION_1_X, POSICION_1_Y, title1, img1);
      drawImage(POSICION_2_X, POSICION_2_Y, title2, img2);
      drawImage(POSICION_3_X, POSICION_3_Y, title3, img3);
      drawImage(POSICION_4_X, POSICION_4_Y, title4, img4);
      // drawImage(POSICION_5_X, POSICION_5_Y, "Fondo:", imgOutput);
      drawImage<ofxCvColorImage>(POSICION_6_X, POSICION_6_Y, "Output:", imgOutput);

      for(int i=0; i<NUM_PERSONAS; i++){
         if(!gente.at(i).activa) continue;

         ofNoFill();
         ofSetColor(gente.at(i).getColor());
         float x,y,w,h;
         x = POSICION_6_X + (gente.at(i).x * IMAGEN_PEQUENA_WIDTH);
         y = POSICION_6_Y + (gente.at(i).y * IMAGEN_PEQUENA_HEIGHT);
         w = gente.at(i).width * IMAGEN_PEQUENA_WIDTH;
         h = gente.at(i).height * IMAGEN_PEQUENA_HEIGHT;
         ofRect(x,y,w,h);
         ofFill();
      }

      for(int i=0; i<animaciones.size(); i++){
         animaciones.at(i)->draw();
      }
   }
   else{
      imgOutput.draw(0, 0, IMAGEN_GRANDE_WIDTH, IMAGEN_GRANDE_HEIGHT);
   }
   ofPopStyle();
   ofPopMatrix();
}
