#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"
#include "ofxTween.h"

class AnimacionPajaro: public Animacion{
   public:
      explicit AnimacionPajaro(float x, float y);
      virtual ~AnimacionPajaro();
      void play();
      void draw();

   private:
      float duracionRecorrido;

      ofxTween tween;
      ofxEasingQuad suavizado;
};
