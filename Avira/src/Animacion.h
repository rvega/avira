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
      virtual void setX(float val);
      virtual void setY(float val);
      void setYPersona(float val);
      void setXPersona(float val);
      virtual bool isComplete(){return false;};

   private:
      virtual void drawImagen();
      void drawSubAnimaciones();

      ofxThreadedImageLoader cargadorImagenes;

   protected:
      std::vector<ofImage> imagenes;

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
