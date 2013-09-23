#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class Animacion{
   public:
      explicit Animacion(float x, float y);
      virtual ~Animacion();
      float x;
      float y;
      float height;
      float width;
      int fps;
      bool loop;
      virtual void draw();
      virtual void play();
      void stop();
      void setPath(string val);
      void gotMessage(ofMessage& msg);
      bool playing;

   private:
      bool fullscreen;
      std::vector<ofImage> imagenes;
      ofxThreadedImageLoader cargadorImagenes;
      void drawImagen();
      void drawSubAnimaciones();
      unsigned int frameIndex;

   protected:
      float startTime;
      std::vector<Animacion*> animaciones;
};
