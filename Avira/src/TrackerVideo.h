#pragma once

#include "ofxOpenCv.h"
#include "Persona.h"

// class TrackerVideo: public ofThread{
class TrackerVideo{
   public:
      explicit TrackerVideo();
      virtual ~TrackerVideo();
      void start();
      void stop();
      map<int, Persona> getGente();
      vector<ofxCvImage*> getInterimImages();
      ofxCvImage* getInputImage();
		void gotMessage(ofMessage& msg);
      void track();

   private:

      ofVideoGrabber camara;
      ofVideoPlayer pelicula;
      ofxCvColorImage imgInput;
      ofxCvGrayscaleImage imgFondo;
      ofxCvGrayscaleImage imgWork;
      map<int, Persona> gente;
      bool fullscreen;
      bool useCamara;
      int threshold;
      int threshold2;
      int tamanoMin;
      int tamanoMax;
      int blur;
      int frameCounter;
      int roi;

      bool frameEsNuevo;
      unsigned char* pixels;
      ofxCvContourFinder contourFinder;
      ofRectangle rectangle;
      int frameCounterNow;
      int i;

      void captureFondo();
      // void threadedFunction();
      void asignarPersonas(vector<ofxCvBlob> blobs);

      TrackerVideo(const TrackerVideo&);
      TrackerVideo& operator=(const TrackerVideo&);
      int cualPaso;
};
