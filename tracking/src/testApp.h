#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();

   private:
      ofVideoPlayer pelicula;
      ofxCvGrayscaleImage imgWork;
      ofxCvColorImage imgInput;
      // ofxCvContourFinder contourFinder;
};
