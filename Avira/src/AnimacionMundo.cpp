#include "AnimacionMundo.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionMundo::AnimacionMundo(float x, float y):
Animacion(x,y)
{
   loop=true;
   width=0.1;
   setPath("animaciones/pajaro/accesorios/mundi");
}

void AnimacionMundo::play(){
    tween.setParameters(suavizado, ofxTween::easeIn, x, xPersona, 1800, 0);
    tween.addValue(y, yPersona);
    tween.start();
    Animacion::play();
}

void AnimacionMundo::draw(){
    x = tween.update();
    y = tween.getTarget(1);
    Animacion::draw();
}

bool AnimacionMundo::isComplete(){
    return tween.isCompleted();
}
