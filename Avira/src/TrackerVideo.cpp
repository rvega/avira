#include <iostream>
#include "ofMain.h"
#include "TrackerVideo.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//

TrackerVideo::TrackerVideo():
   useCamara(true),
   threshold(THRESHOLD_DEFAULT)
{
   imgInput.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso1.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso2.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso3.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgFondo.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);

   ofRegisterGetMessages(this);
}

TrackerVideo::~TrackerVideo(){
   ofUnregisterGetMessages(this);

   imgInput.clear();
   imgPaso1.clear();
   imgPaso2.clear();
   imgPaso3.clear();
   imgFondo.clear();
}

void TrackerVideo::start(){
   if(useCamara){
      // Abrir el stream de la camara
      camara.setVerbose(false);
      camara.setDeviceID(2);
      camara.setDesiredFrameRate(30);
      camara.initGrabber(CAMARA_WIDTH, CAMARA_HEIGHT);
   }
   else{
      // Abrir archivo de la pelicula
      pelicula.loadMovie("referencia.webm");
      pelicula.play();
   }

   // Cargar imagen de fondo
   try{
      ofImage img;
      img.loadImage("fondo.png");
      imgFondo.setFromPixels( img.getPixelsRef() );
   }
   catch(int e){
      // Nada, siga fresco.
   }

   startThread(false, false); // non blocking, not verbose;
}

void TrackerVideo::stop(){
   if(useCamara){
      camara.close();
   }
   else{
      pelicula.stop();
   }
   stopThread();
}

//===========================================//
//  MENSAJES QUE LLEGAN DESDE OTROS OBJETOS  //
//===========================================//
void TrackerVideo::gotMessage(ofMessage& msg){
   if(msg.message == "CAPTURAR_FONDO"){
      captureFondo();
   }
   else if(msg.message == "USAR_CAMARA"){
      stop();
      useCamara = true;
      start();
   }
   else if(msg.message == "USAR_PELICULA"){
      stop();
      useCamara = false;
      start();
   }

   if(string::npos != msg.message.find("THRESHOLD")){
      string val = msg.message.substr( msg.message.find(" ") ); 
      threshold = ofToFloat(val);
   }
}

void TrackerVideo::captureFondo(){
   ofImage img;
   while (!lock()){
      sleep(1);
   }
   imgFondo = getImgInput();
   img.setFromPixels( imgFondo.getPixelsRef() );
   unlock();
   img.saveImage("fondo.png");
}

//=============//
//  ACCESSORS  //
//=============//

// OJO! toca hacer lock() antes de llamar los siguientes metodos
ofxCvGrayscaleImage TrackerVideo::getImgPaso1(){
   ofxCvGrayscaleImage img = imgPaso1;
   return img;
}

ofxCvGrayscaleImage TrackerVideo::getImgPaso2(){
   ofxCvGrayscaleImage img = imgPaso2;
   return img;
}

ofxCvGrayscaleImage TrackerVideo::getImgPaso3(){
   ofxCvGrayscaleImage img = imgPaso3;
   return img;
}

ofxCvGrayscaleImage TrackerVideo::getImgFondo(){
   ofxCvGrayscaleImage img = imgFondo;
   return img;
}

ofxCvColorImage TrackerVideo::getImgInput(){
   ofxCvColorImage img = imgInput;
   return img;
}

std::map<int, Persona> TrackerVideo::getGente(){
   return gente;
}

//==========//
//  WORKER  //
//==========//
void TrackerVideo::threadedFunction(){
   bool frameEsNuevo = false;
   unsigned char* pixels;
   ofxCvContourFinder contourFinder;
   ofRectangle rectangle;
   int i;
   for(i=0; i<NUM_PERSONAS; i++){
      Persona personaNueva;
      personaNueva.setColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
      gente[i] = personaNueva;
   }

   while(isThreadRunning()){
      // Tenemos un frame nuevo?
      if(useCamara){
         camara.update();
         frameEsNuevo = camara.isFrameNew();
      }
      else{
         pelicula.update();
         frameEsNuevo = pelicula.isFrameNew();
      }

      if(frameEsNuevo){
         // Agarre pixeles de la imagen de entrada y convierta a escala de grises
         if(useCamara){
            pixels = camara.getPixels();
         }
         else{
            pixels = pelicula.getPixels();
         }


         // Vamos a escribir a imgInput, pongale lock.
         if(!lock()){
            ofLogNotice() << "Choque de locks. TrackerVideo::threaddedFunction" << "\n";
         }
         else{
            imgInput.setRoiFromPixels(pixels, CAMARA_WIDTH, CAMARA_HEIGHT);
            imgInput.mirror(false, true); // Flip horizontally

            // Convertir a escala de grises
            imgPaso1 = imgInput;

            // Restar la imagen gris (paso1) de el fondo.
            imgPaso2.absDiff(imgFondo, imgPaso1);
            imgPaso3 = imgPaso2;

            // Aplicar threshold a la resta (paso2)
            // TODO: threshold desde GUI
            imgPaso3.threshold(threshold);

            // Encontrar contornos
            // TODO: traer lo de Johnny
            contourFinder.findContours(imgPaso3, PERSONA_TAMANO_MINIMO, PERSONA_TAMANO_MAXIMO, NUM_PERSONAS, false); // false: no busque huecos

            unlock();

            for(i=0; i<contourFinder.nBlobs; i++){
               rectangle = contourFinder.blobs.at(i).boundingRect;
               gente.at(i).width = rectangle.width;
               gente.at(i).height = rectangle.height;
               gente.at(i).x = rectangle.x;
               gente.at(i).y = rectangle.y;
            }
         }
      }
      sleep(1);
   }
}
