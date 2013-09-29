#include "AviraApp.h"

void AviraApp::setup(){
   ofSetFrameRate(20);
   fullscreen = false;
   gui.setup();
   tracker.start();
   sleep(1);
};

void AviraApp::exit(){
   gui.exit();
   tracker.stop();
}

void AviraApp::draw(){
   map<int, Persona> gente;

   ofBackground(0, 0, 0, 255);

   tracker.track();

   if(!fullscreen){
      vector<ofxCvImage*> interimImages = tracker.getInterimImages();
      renderer.drawInterimImages(interimImages);
   }

   ofxCvImage* outputImage = tracker.getInputImage();
   renderer.drawOutputImage(outputImage);

   gente = tracker.getGente();

   renderer.drawAnimaciones(gente);
}

void AviraApp::gotMessage(ofMessage msg){
   ofLogNotice() << msg.message << "\n";
   if(msg.message == "FULLSCREENON"){
      fullscreen = true;
   }
   else{
      fullscreen = false;
   }
}

