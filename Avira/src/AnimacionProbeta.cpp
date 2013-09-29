#include "AnimacionProbeta.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionProbeta::AnimacionProbeta(float x, float y):
Animacion(x,y)
{
   loop=true;
   width=0.15;
   setPath("animaciones/pajaro/accesorios/probeta");
}

void AnimacionProbeta::play(){
    tween.setParameters(suavizado, ofxTween::easeIn, x, xPersona, 1800, 0);
    tween.addValue(y, yPersona);
    tween.start();
    Animacion::play();
}

void AnimacionProbeta::draw(){
    x = tween.update();
    y = tween.getTarget(1);
    Animacion::draw();
}

bool AnimacionProbeta::isComplete(){
    return tween.isCompleted();
}
