#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"
#include "ofxTween.h"


class AnimacionProbeta: public Animacion{
   public:
      explicit AnimacionProbeta(float x, float y);
      void play();
      void draw();
      bool isComplete();

   private:
      ofxTween tween;
      ofxEasingQuad suavizado;
};
