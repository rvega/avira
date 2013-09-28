#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"
#include "ofxTween.h"

class AnimacionEscenaPajaro: public Animacion{
   public:
      explicit AnimacionEscenaPajaro(float x, float y);
      // virtual ~AnimacionEscenaPajaro();
      void play();
      void draw();
      void setCualAccesorio(string val);

   private:
      string elAccesorio;
      ofxTween tween;
      ofxEasingLinear easingLinear;
      ofxTween multitween;
      float timer;

};
