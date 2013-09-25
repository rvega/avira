#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxUI.h"

class Gui{
   public:
      explicit Gui();
      virtual ~Gui();
      void setup();
      void exit();

   private:
      bool fullscreen;
      ofxUICanvas gui;
      ofxUICanvas gui2;
      ofxUICanvas gui3;
      void guiEvent(ofxUIEventArgs &e);
      void keyPressed(ofKeyEventArgs& data);
      void mousePressed(ofMouseEventArgs& data);

      Gui(const Gui&);
      Gui& operator=(const Gui&);
};
