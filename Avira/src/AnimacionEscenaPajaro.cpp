#include "AnimacionEscenaPajaro.h"
#include "AnimacionPajaro.h"
#include "AnimacionMundo.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscenaPajaro::AnimacionEscenaPajaro(float x, float y):
Animacion(x,y)
{
   // fps=15;
   // width=0.1;

   AnimacionPajaro* pajaro = new AnimacionPajaro(x+0.01, y+0.02);
   animaciones.push_back(pajaro);

   AnimacionMundo* mundi = new AnimacionMundo(x+0.01, y+0.02);
   animaciones.push_back(mundi);

}

AnimacionEscenaPajaro::~AnimacionEscenaPajaro(){ }


void AnimacionEscenaPajaro::play(){
    int duracionMovimientoPajaro = 5000;
   int delayMovimientoPajaro = 2000;
    tween.setParameters(easingLinear, ofxTween::easeInOut, x+0.01, x+0.8,duracionMovimientoPajaro, delayMovimientoPajaro);



    animaciones.at(0)->play();

    Animacion::play();
}

void AnimacionEscenaPajaro::draw(){
   float mapaX = tween.update();
   animaciones.at(0)->x=mapaX;

        // si el pajaro.x es mayor o igual a el blob.x
    if(!animaciones.at(1)->playing && animaciones.at(0)->x >= 0.6){

       animaciones.at(1)->x = animaciones.at(0)->x;
      animaciones.at(1)->y = animaciones.at(0)->y + 0.1;

      animaciones.at(1)->play();

    multitween.setParameters(easingLinear,ofxTween::easeInOut,animaciones.at(1)->x,animaciones.at(1)->x + 0.3,1000,50);
    multitween.addValue(animaciones.at(1)->y,animaciones.at(1)->y + 0.5);
    multitween.start();


   }else if(animaciones.at(1)->playing){

        float tweenx = multitween.update();
        float tweeny = multitween.getTarget(1);
        //Tween accesorio
            animaciones.at(1) ->x=tweenx;
            animaciones.at(1)->y=tweeny;
   }
    Animacion::draw();
}

