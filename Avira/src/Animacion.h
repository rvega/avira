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
      virtual void draw();
      virtual void play();
      void stop();
      void setPath(string val);
      void gotMessage(ofMessage& msg);

   private:
      bool playing;
      bool fullscreen;
      std::vector<ofImage> imagenes;
      ofxThreadedImageLoader cargadorImagenes;
      void drawImagen();
      void drawSubAnimaciones();

   protected:
      std::vector<Animacion*> animaciones;

};
