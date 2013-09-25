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
   tamano(SLIDER_TAMANO_DEFAULT),
   tamanoMax(SLIDER_TAMANO_DEFAULT),
   blur(1)

{
   imgInput.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso1.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso2.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso3.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgPaso4.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   imgFondo.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
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
   imgPaso1.clear();
   imgPaso2.clear();
   imgPaso3.clear();
   imgFondo.clear();
   imgWork.clear();
}

void TrackerVideo::start(){
   if(useCamara){
      // Abrir el stream de la camara
      camara.setVerbose(false);
      camara.setDeviceID(2);
      camara.setDesiredFrameRate(1);
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

   else if(string::npos != msg.message.find("BLUR")){
      string val = msg.message.substr( msg.message.find(" ") );

      // Must be an odd number
      float blurTmp = ofToFloat(val);
      if((int)blurTmp%2 == 0){
         blurTmp = blurTmp + 1.0;
      }

      blur = blurTmp;
      ofLogNotice() << "Blur: " << blur;
   }

   else if(string::npos != msg.message.find("TAMANO_MINIMO")){
      string val = msg.message.substr( msg.message.find(" ") );
      tamano = ofToFloat(val);
   }

   else if(string::npos != msg.message.find("TAMANO_MAXIMO")){
      string val = msg.message.substr( msg.message.find(" ") );
      tamanoMax = ofToFloat(val);
   }

   else if(string::npos != msg.message.find("THRESHOLD")){
      string val = msg.message.substr( msg.message.find(" ") );
      threshold = ofToFloat(val);
   }

   else if(msg.message == "FULLSCREEN_ON"){
      fullscreen = true;
   }

   else if(msg.message == "FULLSCREEN_OFF"){
      fullscreen = false;
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

ofxCvGrayscaleImage TrackerVideo::getImgPaso4(){
   ofxCvGrayscaleImage img = imgPaso4;
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
   // int frameCounter = 0;
   int i;

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
         // Agarre pixeles de la imagen de entrada
         if(useCamara){
            pixels = camara.getPixels();
         }
         else{
            pixels = pelicula.getPixels();
         }


         // Vamos a escribir a imgInput, pongale lock.
         // if(!lock()){
         //    ofLogNotice() << "Choque de locks. TrackerVideo::threaddedFunction" << "\n";
         // }
         // else{

            // TODO: explore esto, hacer la deteccion de video, pocas veces por segundo.
            // if(frameCounter != 15){
            //    frameCounter ++;
            //    unlock();
            //    continue;
            // }
            // frameCounter = 0;
            // ofLogNotice() <<  "tick" << "\n";

            // Paso1: Convertir a escala de grises
            if(lock()){
               imgInput.setFromPixels(pixels, CAMARA_WIDTH, CAMARA_HEIGHT);
               imgInput.mirror(false, true); // Flip horizontally
               imgWork = imgInput;

               if(!fullscreen) imgPaso1 = imgInput;

               unlock();
            }

            // Paso2: Restar la imagen gris de el fondo.
            imgWork.absDiff(imgFondo, imgWork);
            if(!fullscreen && lock()){
               imgPaso2 = imgWork;
               unlock();
            } 


            // Paso3: Aplicar threshold
            imgWork.threshold(threshold);
            if(!fullscreen && lock()){
               imgPaso3 = imgWork;
               unlock();
            } 

            // Paso4: Blur
            imgWork.blurGaussian(blur);
            if(!fullscreen && lock()){
               imgPaso4 = imgWork;
               unlock();
            } 

            // Encontrar contornos
            // TODO: traer lo de Johnny
            contourFinder.findContours(imgWork, tamano, tamanoMax, NUM_PERSONAS, false); // false: no busque huecos,

            if(lock()){
               for(i=0; i<NUM_PERSONAS; i++){
                  if(i < contourFinder.nBlobs){
                     rectangle = contourFinder.blobs.at(i).boundingRect;
                     gente.at(i).activa = true;
                     gente.at(i).width = (float)rectangle.width / (float)CAMARA_WIDTH;
                     gente.at(i).height = (float)rectangle.height / (float)CAMARA_HEIGHT;
                     gente.at(i).x = (float)rectangle.x / (float)CAMARA_WIDTH;
                     gente.at(i).y = (float)rectangle.y / (float)CAMARA_HEIGHT;
                  }
                  else{
                     gente.at(i).activa = false;
                  }
               }

               unlock();
            }
         // }
      }
      sleep(1);
   }
}
