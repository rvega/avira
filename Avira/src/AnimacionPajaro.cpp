#include "AnimacionPajaro.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionPajaro::AnimacionPajaro(float x, float y):
Animacion(x,y)
{
   loop=true;
   width=0.4;
   setPath("animaciones/pajaro/pajaro");

   xOffset = -0.1;
   duracionRecorrido = 10000;
}

AnimacionPajaro::~AnimacionPajaro(){ }

void AnimacionPajaro::play(){
   tween.setParameters(suavizado, ofxTween::easeInOut,-0.2, 1.1,duracionRecorrido,0);
   tween.start();
   Animacion::play();
}

void AnimacionPajaro::draw(){
//   if(tween.isCompleted()){
//       tween.setParameters(suavizado, ofxTween::easeInOut,-0.2, 1.1,duracionRecorrido,0);
//       x = -0.2;
//       tween.start();
//   }
   x = tween.update();

   Animacion::draw();
}
