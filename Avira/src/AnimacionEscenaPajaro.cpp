#include "AnimacionEscenaPajaro.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscenaPajaro::AnimacionEscenaPajaro(float x, float y):
Animacion(x,y)
{ 
   // fps=15;
   // width=0.1;

   // AnimacionMapa* mapa = new AnimacionMapa(x+0.01, y+0.02);
   // mapa->play();
   // animaciones.push_back(mapa);

}

AnimacionEscenaPajaro::~AnimacionEscenaPajaro(){ } 


void AnimacionEscenaPajaro::play(){
   // int duracionMovimientoMapa = 2000;
   // int delayMovimientoMapa = 2000;
   // tween.setParameters(easingLinear, ofxTween::easeInOut, x+0.01, x+0.8,duracionMovimientoMapa, delayMovimientoMapa);

   // Animacion::play();
}

void AnimacionEscenaPajaro::draw(){
   // float mapaX = tween.update(); 
   // animaciones.at(0)->x=mapaX;

   // Animacion::draw();
}

