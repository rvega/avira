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
      bool relativoAPersona; // false: dibuja en x + xOffset, true: dibuja en xPersona+xOffset

      virtual void draw();
      virtual void play();
      void stop();
      void setPath(string val);
      void gotMessage(ofMessage& msg);
      float getX();
      float getY();
      void setX(float val);
      void setY(float val);
      void setXPersona(float val);
      void setYPersona(float val);

   private:
      void drawImagen();
      void drawSubAnimaciones();

      std::vector<ofImage> imagenes;
      ofxThreadedImageLoader cargadorImagenes;

   protected:
      float x;   // Posicion inicial de la animacion.
      float y;

      float xPersona;   // Posicion de la persona.
      float yPersona;

      float xOffset;  // Posicion de esta animacion respecto a la persona.
      float yOffset;


      float height;
      float width;
      float startTime;
      bool fullscreen;
      unsigned int frameIndex;
      std::vector<Animacion*> animaciones;
};
