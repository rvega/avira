#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"
#include "ofxTween.h"

class AnimacionEscena1: public Animacion{
   public:
      explicit AnimacionEscena1(float x, float y);
      virtual ~AnimacionEscena1();
      void play();
      void draw();

   private:
      ofxTween tween;
      ofxEasingLinear easingLinear;
};
