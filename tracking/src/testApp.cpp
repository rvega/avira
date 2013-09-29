#include "testApp.h"

#define CAMARA_WIDTH 640
#define CAMARA_HEIGHT 480


void testApp::setup(){
   ofSetFrameRate(30);
   // Abrir archivo de la pelicula
   pelicula.loadMovie("referencia.webm");
   pelicula.play();

   // Cargar imagen de fondo
   // try{
   //    ofImage img;
   //    img.loadImage("fondo.png");
   //    imgFondo.setFromPixels( img.getPixelsRef() );
   // }
   // catch(int e){
   //    // Nada, siga fresco.
   // }

}

void testApp::exit(){
   pelicula.stop();
}

void testApp::update(){
   pelicula.update();
   // imgInput.allocate(CAMARA_WIDTH, CAMARA_HEIGHT);
   // imgWork.allocate(CAMARA_WIDTH, CAMARA_HEIGHT/2);
}

void testApp::draw(){
   if(pelicula.isFrameNew()){
      // Agarre pixeles de la imagen de entrada
      unsigned char* pixels = pelicula.getPixels();
      imgInput.setFromPixels(pixels, CAMARA_WIDTH, CAMARA_HEIGHT);

      // Espejo
      imgInput.mirror(false, true); //vertical, horizontal
      imgInput.setROI(0, CAMARA_HEIGHT/2, CAMARA_WIDTH, (CAMARA_HEIGHT/2)-1);
      imgInput.blurGaussian(100);
      // imgInput.resetROI();

      // Paso0: Convertir a escala de grises
      imgWork = imgInput;

      // Dibujar imagenes
      imgInput.draw(10, 10, 0.5*CAMARA_WIDTH, 0.5*CAMARA_HEIGHT);
      imgWork.draw(400, 10, 0.5*CAMARA_WIDTH, 0.5*CAMARA_HEIGHT);
   }
}

      // Paso1: Restar la imagen gris de el fondo.
   //    imgWork.absDiff(imgFondo, imgWork);
   //    if(!fullscreen && lock()){
   //       imgPaso1 = imgWork;
   //       unlock();
   //    } 

   //    // Paso2 Aplicar threshold
   //    imgWork.threshold(threshold);
   //    if(!fullscreen && lock()){
   //       imgPaso2 = imgWork;
   //       unlock();
   //    } 

   //    // Paso3: Blur
   //    imgWork.blurGaussian(blur);
   //    if(!fullscreen && lock()){
   //       imgPaso3 = imgWork;
   //       unlock();
   //    } 

   //    // Paso4 Threshold otra vez
   //    imgWork.threshold(threshold2);
   //    if(!fullscreen && lock()){
   //       imgPaso4 = imgWork;
   //       unlock();
   //    } 

   //    // Encontrar contornos
   //    contourFinder.findContours(imgWork, tamano, tamanoMax, NUM_PERSONAS, false); // false: no busque huecos,

   //    if(lock()){
   //       for(i=0; i<NUM_PERSONAS; i++){
   //          if(i < contourFinder.nBlobs){
   //             rectangle = contourFinder.blobs.at(i).boundingRect;
   //             gente.at(i).setActiva(true);
   //             gente.at(i).setDimensions(
   //                   (float)rectangle.x/(float)CAMARA_WIDTH,
   //                   (float)rectangle.y / (float)CAMARA_HEIGHT,
   //                   (float)rectangle.width/(float)CAMARA_WIDTH,
   //                   (float)rectangle.height/(float)CAMARA_HEIGHT
   //                   );
   //          }
   //          else{
   //             gente.at(i).setActiva(false);
   //          }
   //       }
   //       unlock();
   //    }
   //    }
   //    sleep(1);
   // }
