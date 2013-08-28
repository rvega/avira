#include "testApp.h"

void testApp::setup(){
   // Usamos camara
   // camaraOArchivo = true;    //    <----- 
   
   // Usamos archivo
   camaraOArchivo = false;       //      <-----

   if(camaraOArchivo){
      // Init camara
      camara.setVerbose(true);
      camara.setDeviceID(2);
      camara.setDesiredFrameRate(30);
      camara.initGrabber(320, 240);
   }
   else{
      // Cargar archivo de video
      archivoDeVideo.loadMovie("referencia.webm");
      archivoDeVideo.play();
   }

   // Reservar memoria para las imágenes
   imgInput.allocate(640, 480);
   imgGris.allocate(640, 480);
   imgFondoGris.allocate(640, 480);
   imgDiferencia.allocate(640, 480);

   // Asumimos por ahora que el primer frame de video no tiene personas, es 
   // solo background.
   elFondoEstaVacio = true;
   threshold = 90;
}

void testApp::exit(){
   // Liberar la memoria reservada para las imágenes
   imgInput.clear();
   imgGris.clear();
   imgFondoGris.clear();
   imgDiferencia.clear();
}

//--------------------------------------------------------------
void testApp::update(){
   // Vamos a preguntar (polling) al archivo o a la camara si hay un 
   // frame nuevo:
   bool frameEsNuevo = false;
   if(camaraOArchivo){
      camara.update();
      frameEsNuevo = camara.isFrameNew();
   }
   else{
      archivoDeVideo.update();
      frameEsNuevo = archivoDeVideo.isFrameNew();
   }

   // Si sí hay un frame nuevo, procéselo
   if(frameEsNuevo){
      // 1. Asignamos pixeles a la imgInput
      if(camaraOArchivo){
         imgInput.setRoiFromPixels(camara.getPixels(),640,480);
      }
      else{
         imgInput.setRoiFromPixels(archivoDeVideo.getPixels(),640,480);
      }

      // 2. Hacemos versión en escala de grises
      imgGris=imgInput;

      // 3. Aprendemos el BG
      if(elFondoEstaVacio){
         imgFondoGris = imgGris;
         elFondoEstaVacio = false; // solo necesitamos "aprender" una vez
      }

      // 4. "Restamos" el fondo con la imagen gris y luego threshold
      imgDiferencia.absDiff(imgFondoGris, imgGris);
      imgDiferencia.threshold(threshold);

      // 5. Encontrar contornos de blobs en la imágen de diferencia.
      // Tamaño minimo del blob, máximo, numero máximo de blobs que quiero, 
      // no busque huecos
      contourFinder.findContours(imgDiferencia, 100, (640*480)/4, 6, false);
   }
}



//--------------------------------------------------------------
void testApp::draw(){
   ofSetHexColor(0xffffff);
   imgInput.draw(20,20, 320,240);
   imgGris.draw(20,280, 320,240);
   imgFondoGris.draw(360,20, 320,240);
   imgDiferencia.draw(360,280, 320,240);
            

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
