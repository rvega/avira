#include <iostream>
#include "ofMain.h"
#include "TrackerVideo.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//

TrackerVideo::TrackerVideo():
   useCamara(true)
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
      pelicula.loadMovie("test.webm");
      pelicula.play();
   }

   // Cargar imagen de fondo
   ofImage img;
   img.loadImage("fondo.png");
   imgFondo.setFromPixels( img.getPixelsRef() );

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
   std::map<int, Persona> a;
   return a;
}

//==========//
//  WORKER  //
//==========//
void TrackerVideo::threadedFunction(){
   bool frameEsNuevo = false;
   unsigned char* pixels;

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
            // ofLogNotice() << "Choque de locks. TrackerVideo::threaddedFunction" << "\n";
         }
         else{

            // grises automaticamente
            imgInput.setRoiFromPixels(pixels, CAMARA_WIDTH, CAMARA_HEIGHT);
            imgInput.mirror(false, true); // Flip horizontally
            imgPaso1 = imgInput;
            unlock();
         }
      }
      sleep(1);
   }
}
