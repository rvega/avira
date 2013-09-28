#include <iostream>
#include "ofMain.h"
#include "TrackerVideo.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//

TrackerVideo::TrackerVideo():
   fullscreen(false),
   useCamara(true),
   threshold(THRESHOLD_DEFAULT),
   threshold2(THRESHOLD_DEFAULT),
   tamanoMin(SLIDER_TAMANO_DEFAULT),
   tamanoMax(SLIDER_TAMANO_DEFAULT),
   blur(1),
   frameCounter(5),
   frameEsNuevo(false),
   frameCounterNow(0)
{
   imgFondo.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgInput.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgWork.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);

   for(int i=0; i<NUM_PERSONAS; i++){
      Persona personaNueva;
      personaNueva.setBorderColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
      gente[i] = personaNueva;
   }

   ofRegisterGetMessages(this);
}

TrackerVideo::~TrackerVideo(){
   ofUnregisterGetMessages(this);

   imgInput.clear();
   imgFondo.clear();
   imgWork.clear();
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
   ofImage img;
   img.loadImage("fondo.png");
   imgFondo.setFromPixels( img.getPixelsRef() );
}

void TrackerVideo::stop(){
   if(useCamara){
      camara.close();
   }
   else{
      pelicula.stop();
   }
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

   else if(string::npos != msg.message.find("BLUR")){
      string val = msg.message.substr( msg.message.find(" ") );

      // Must be an odd number
      float blurTmp = ofToFloat(val);
      if((int)blurTmp%2 == 0){
         blurTmp = blurTmp + 1.0;
      }

      blur = blurTmp;
   }

   else if(string::npos != msg.message.find("TAMANO_MINIMO")){
      string val = msg.message.substr( msg.message.find(" ") );
      tamanoMin = ofToFloat(val);
   }

   else if(string::npos != msg.message.find("TAMANO_MAXIMO")){
      string val = msg.message.substr( msg.message.find(" ") );
      tamanoMax = ofToFloat(val);
   }

   else if(string::npos != msg.message.find("THRESHOLD1")){
      string val = msg.message.substr( msg.message.find(" ") );
      threshold = ofToFloat(val);
   }

   else if(string::npos != msg.message.find("THRESHOLD2")){
      string val = msg.message.substr( msg.message.find(" ") );
      threshold2 = ofToFloat(val);
   }

   else if(string::npos != msg.message.find("FRAME_COUNTER")){
      string val = msg.message.substr( msg.message.find(" ") );
      frameCounter = ofToInt(val);
      frameCounterNow=0;
   }

   else if(msg.message == "FULLSCREEN_ON"){
      fullscreen = true;
   }

   else if(msg.message == "FULLSCREEN_OFF"){
      fullscreen = false;
   }

   else if(string::npos != msg.message.find("POSICION_PELICULA")){
      string val = msg.message.substr( msg.message.find(" ") );
      pelicula.setPosition(ofToFloat(val));
   }

   else if(msg.message == "PLAY"){
      pelicula.setPaused( !pelicula.isPaused() );
   }
}

void TrackerVideo::captureFondo(){
   imgFondo = imgInput;
   ofImage img;
   img.setFromPixels( imgFondo.getPixelsRef() );
   img.saveImage("fondo.png");
}

//=============//
//  ACCESSORS  //
//=============//
ofxCvImage* TrackerVideo::getInputImage(){
   return &imgInput;
}

vector<ofxCvImage*> TrackerVideo::getInterimImages(){
   vector<ofxCvImage*> images;
   images.push_back(&imgFondo);
   images.push_back(&imgWork);
   return images;
}

std::map<int, Persona> TrackerVideo::getGente(){
   return gente;
}

//==========//
//  WORKER  //
//==========//
void TrackerVideo::track(){


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
      // Agarre pixeles de la imagen de entrada
      if(useCamara){
         pixels = camara.getPixels();
      }
      else{
         pixels = pelicula.getPixels();
      }

      imgInput.setFromPixels(pixels, CAMARA_WIDTH, CAMARA_HEIGHT);
      imgInput.mirror(false, true); // Flip horizontally

      // Hacer la deteccion de video pocas veces por segundo.
      if(frameCounterNow != frameCounter && frameCounter!=0){
         frameCounterNow ++;
         return;
      }
      frameCounterNow = 0;

      // Paso0: Convertir a escala de grises
      imgWork = imgInput;

      // Paso1: Restar la imagen gris de el fondo.
      imgWork.absDiff(imgFondo, imgWork);

      // Paso2 Aplicar threshold
      imgWork.setROI(0, CAMARA_HEIGHT/2, CAMARA_WIDTH, (CAMARA_HEIGHT/2)-1);
      imgWork.threshold(threshold);

      // Paso3: Blur
      imgWork.blurGaussian(blur);

      // Paso4 Threshold otra vez
      imgWork.threshold(threshold2);

      contourFinder.findContours(imgWork, tamanoMin, tamanoMax, NUM_PERSONAS, false); // false: no busque huecos,

      // Encontrar contornos
      for(i=0; i<NUM_PERSONAS; i++){
         if(i < contourFinder.nBlobs){
            rectangle = contourFinder.blobs.at(i).boundingRect;
            gente.at(i).setActiva(true);
            gente.at(i).setDimensions(
               (float)rectangle.x/(float)CAMARA_WIDTH,
               ((float)rectangle.y + CAMARA_HEIGHT/2) / (float)CAMARA_HEIGHT,
               (float)rectangle.width/(float)CAMARA_WIDTH,
               (float)rectangle.height/(float)CAMARA_HEIGHT
            );
         }
         else{
            gente.at(i).setActiva(false);
         }
      }

      imgWork.resetROI();
   }
}
