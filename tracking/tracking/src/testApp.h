#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

   private:
      // Bandera para seleccionar si vamos a capturar video de un archivo o de
      // la camara
      bool camaraOArchivo;

      ofVideoGrabber camara;
      ofVideoPlayer archivoDeVideo;
            
      // Imagenes que usamos para dibujar frames de video.
      ofxCvColorImage imgInput;
      ofxCvGrayscaleImage imgGris;
      ofxCvGrayscaleImage imgFondoGris;
      ofxCvGrayscaleImage imgDiferencia;

      // Esta variable se pone en true a través de espichar la barra espaciadora
      // e indica que en la imágen no hay personas, solo background.
      // Sirve para agarrar ese frame sin personas y usarlo en la diferencia de
      // imágenes.
      bool elFondoEstaVacio;

      // Threshold para usar en el algoritmo de diferencia
      int threshold;

      // Objeto de openCV que encuentra contornos de blobs
      ofxCvContourFinder contourFinder;
};
