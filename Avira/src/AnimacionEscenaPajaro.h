#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"

class AnimacionEscenaPajaro: public Animacion{
   public:
      explicit AnimacionEscenaPajaro(float x, float y);
      void play();
      void draw();
      void setCualAccesorio(string val);
      bool isComplete();
      void setX(float val);
      void setY(float val);

   private:
      string elAccesorio;
      string estado;
      float timer;
      bool complete;

      Animacion* accesorio;
      Animacion* consecuencia;
};
