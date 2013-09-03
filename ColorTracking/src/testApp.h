#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //declaramos variables para capturar con la camara
    //video-grabber se usa para "capturar" los frames de el video
    ofVideoGrabber video;
    int w;
    int h;
    
    //Threshold
    //---------------------- declaracion de variables para el threshold
    
    //bits para procesar la imagen, esto es un puntero, positivo (0 -> 255)
    unsigned char* outImage;
    //Textura del procesamiento de la imagen
    ofTexture outImageTexture;
    
    //_______________________ declaracion de variables para el epicentro del trackin
    //coordenadas del objeto
    ofPoint pos; 
    
    ofVideoPlayer captura;
    
    
};
