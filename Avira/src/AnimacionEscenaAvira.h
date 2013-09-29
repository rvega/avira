#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"
#include "ofxTween.h"

class AnimacionEscenaAvira: public Animacion{
   public:
      explicit AnimacionEscenaAvira(float x, float y);
      virtual ~AnimacionEscenaAvira();

      void play();
      void draw();
      bool isComplete();

   private:
      bool complete;
};
