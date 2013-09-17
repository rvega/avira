#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class Animacion{
   public:
      explicit Animacion(int x, int y, int fps);
      virtual ~Animacion();
      float x;
      float y;
      float height;
      float width;
      int fps;
      void draw();
      void play();
      void stop();
      void setPath(string val);

   private:
      bool playing;
      std::vector<ofImage> imagenes;
      ofxThreadedImageLoader cargadorImagenes;
};
