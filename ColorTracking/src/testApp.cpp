#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    pos = ofPoint(0, 0);

    
    //ancho y alto de la pantalla
    w = 320;
    h = 240;
    //conectamos la camara para que empieze a capturar
    video.initGrabber(w, h);
    ofBackground(0);
    //creamos un nuevo puntero, positivo (0, 255) para almacenar
    // el ancho, el alto y los bytes de colores
    // red   = 1 byte
    // green = 2 byte
    // blue  = 3 byte
    outImage = new unsigned char [ w * h * 3];
    
    //creamos una nueva textura para mostrar en la pantalla despues 
    //de el analizis, el .allocate es para atrapar esos pixeles
    outImageTexture.allocate(w, h, GL_RGB);
    
    ofSetFrameRate(30);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    int n = 0; 
    //grabamos un frame
    video.update();
    //si un nuevo frame
    if(video.isFrameNew())
        {
          //creamos un nuevo puntero donde almacenaremos las imagenes
          unsigned char* input = video.getPixels();
            //recorremos la pantalla
            for (int y = 0; y < h; y++)
              {
                  for(int x = 0; x < w; x++)
                  {
                      //input pixel(x, y)
                      //llenamos el puntero input con estos valores
                      int r = input[3 * (x + w * y) + 0];
                      int g = input[3 * (x + w * y) + 1];
                      int b = input[3 * (x + w * y) + 2];
                      //umbral con el color azul
                      //int result = (b > mouseX)? 255: 0;
                      int result = (b > r + mouseX && b > g + mouseX)? 255:0;
                      //esto dibuja una salida en la pantalla negra o blanca
                      outImage[3 * (x + w * y) + 0] = result;
                      outImage[3 * (x + w * y) + 1] = result;
                      outImage[3 * (x + w * y) + 2] = result;
                      //int result = outImage[3 * (x + w * y) + 2];
                      if(result == 255)
                      {
                          pos.x += x;
                          pos.y += y;
                          n++;
                      }
                      
                   
                  }
                  
              }
           
        
            //dibujamos la salida de la imagen con una textura para la nueva pantalla
            outImageTexture.loadData(outImage, w, h, GL_RGB);
            
            //Display average
            if (n> 0) {
            pos.x/= n;
            pos.y/= n;
            }
           
        }
  
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255, 255, 255);
    //output frame
    video.draw(0, 0);
    //salida de el proceso
    outImageTexture.draw(w, 0, w, h);
    //Display circle around the object
    ofSetColor (0, 0, 255); //blue
    ofNoFill (); //Turn off the fill
    ofCircle (pos.x, pos.y, 20); //Draw a circle on the ref. frame 
    ofCircle (pos.x + w, pos.y, 20); //Draw a circle on the Rec. frame


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //setting de la camara
    if (key == 's' || key == 'S'){
        video.videoSettings();
	}
	
	
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
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