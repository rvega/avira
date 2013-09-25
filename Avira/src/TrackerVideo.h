#pragma once

#include "ofxOpenCv.h"
#include "Persona.h"

class TrackerVideo: public ofThread{
   public:
      explicit TrackerVideo();
      virtual ~TrackerVideo();
      void start();
      void stop();
      std::map<int, Persona> getGente();
      ofxCvColorImage getImgInput();
      ofxCvGrayscaleImage getImgFondo();
      ofxCvGrayscaleImage getImgPaso1();
      ofxCvGrayscaleImage getImgPaso2();
      ofxCvGrayscaleImage getImgPaso3();
      ofxCvGrayscaleImage getImgPaso4();
		void gotMessage(ofMessage& msg);
   
   private:
      ofVideoGrabber camara;
      ofVideoPlayer pelicula;
      ofxCvColorImage imgInput;
      ofxCvGrayscaleImage imgPaso1;
      ofxCvGrayscaleImage imgPaso2;
      ofxCvGrayscaleImage imgPaso3;
      ofxCvGrayscaleImage imgPaso4;
      ofxCvGrayscaleImage imgFondo;
      ofxCvGrayscaleImage imgWork;

      map<int, Persona> gente;
      bool fullscreen;
      bool useCamara;
      int threshold;
      int threshold2;
      int tamano;
      int tamanoMax;
      int blur;
      int frameCounter;

      void captureFondo();
      void threadedFunction();

      TrackerVideo(const TrackerVideo&);
      TrackerVideo& operator=(const TrackerVideo&);
};
