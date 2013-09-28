#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class Animacion{
   public:
      explicit Animacion(float x, float y);
      virtual ~Animacion();

      int fps;
      bool loop;
      bool playing;

      virtual void draw();
      virtual void play();
      void stop();
      void setPath(string val);
      void gotMessage(ofMessage& msg);
      float getX();
      float getY();
      void setX(float val);
      void setY(float val);

   private:
      void drawImagen();
      void drawSubAnimaciones();

      std::vector<ofImage> imagenes;
      ofxThreadedImageLoader cargadorImagenes;

   protected:
      float x;
      float y;
      float height;
      float width;
      float xOffset;
      float yOffset;
      float startTime;
      bool fullscreen;
      unsigned int frameIndex;
      std::vector<Animacion*> animaciones;
};
