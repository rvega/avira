#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"


class AnimacionBurbujas: public Animacion{
   public:
      explicit AnimacionBurbujas(float x, float y);
      virtual ~AnimacionBurbujas();
};
