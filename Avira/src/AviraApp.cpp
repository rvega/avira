#include "AviraApp.h"

void AviraApp::setup(){
   fullscreen = false;
   renderer.setTitle1("Fondo:");
   gui.setup();
   tracker.start();
   sleep(1);
};

void AviraApp::exit(){
   gui.exit();
   tracker.stop();
}

void AviraApp::update(){
   // ofLogNotice() << "AviraApp::update";

   if(!tracker.lock()){
      // ofLogNotice() << "Choque de locks. AviraApp::update" << "\n";
   }
   else{
      renderer.setImgOutput( tracker.getImgInput() );
      if(!fullscreen){
         renderer.setImg1( tracker.getImgFondo() );
         // renderer.setImg2( tracker.getImgPaso2() );
         // renderer.setImg3( tracker.getImgPaso3() );
      }
      tracker.unlock();
   }
   // gente = tracker->getGente();
  // tracker.getImgInput();
}

void AviraApp::draw(){
   ofBackground(0, 0, 0, 255);
   renderer.draw();
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

