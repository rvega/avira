#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"

class AnimacionMapa: public Animacion{
   public:
      explicit AnimacionMapa(float x, float y);
      virtual ~AnimacionMapa();
      // float x;
      // float y;
      // float height;
      // float width;
      // int fps;
      // void draw();
      // void play();
      // void stop();
      // void setPath(string val);
      // void gotMessage(ofMessage& msg);

   private:
      // bool playing;
      // bool fullscreen;
      // std::vector<ofImage> imagenes;
      // ofxThreadedImageLoader cargadorImagenes;
};
