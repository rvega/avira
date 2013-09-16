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
		void gotMessage(ofMessage& msg);
   
   private:
      ofVideoGrabber camara;
      ofVideoPlayer pelicula;
      ofxCvColorImage imgInput;
      ofxCvGrayscaleImage imgPaso1;
      ofxCvGrayscaleImage imgPaso2;
      ofxCvGrayscaleImage imgPaso3;
      ofxCvGrayscaleImage imgFondo;
      bool useCamara;
      std::map<int, Persona> gente;
      int threshold;

      void captureFondo();
      void threadedFunction();

      TrackerVideo(const TrackerVideo&);
      TrackerVideo& operator=(const TrackerVideo&);
};
