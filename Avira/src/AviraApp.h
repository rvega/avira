#pragma once

#include "ofMain.h"
   
#include "TrackerVideo.h"
#include "Persona.h"
#include "Gui.h"
#include "Renderer.h"

class AviraApp : public ofBaseApp{
   private: 
      Gui gui;
      Renderer renderer;
      TrackerVideo tracker;
      std::map<int, Persona> gente;
      bool fullscreen;

	public:
		void setup();
		void exit();
		void update();
		void draw();
		void gotMessage(ofMessage msg);
};
