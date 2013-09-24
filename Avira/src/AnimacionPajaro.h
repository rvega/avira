#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"


class AnimacionPajaro: public Animacion{
   public:
      explicit AnimacionPajaro(float x, float y);
      virtual ~AnimacionPajaro();
};
