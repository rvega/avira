#include "AnimacionEscena1.h"
#include "AnimacionMapa.h"
#include "AnimacionAbira.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscena1::AnimacionEscena1(float x, float y):
Animacion(x,y)
{ 
   fps=15;
   width=0.1;

   AnimacionMapa* mapa = new AnimacionMapa(x+0.01, y+0.02);
   mapa->play();
   animaciones.push_back(mapa);

   AnimacionAbira* abira = new AnimacionAbira(x, y);
   abira->play();
   animaciones.push_back(abira);
}

AnimacionEscena1::~AnimacionEscena1(){ } 


void AnimacionEscena1::play(){
   int duracionMovimientoMapa = 2000;
   int delayMovimientoMapa = 2000;
   tween.setParameters(easingLinear, ofxTween::easeInOut, x+0.01, x+0.8,duracionMovimientoMapa, delayMovimientoMapa);

   Animacion::play();
}

void AnimacionEscena1::draw(){
   float mapaX = tween.update(); 
   animaciones.at(0)->x=mapaX;

   Animacion::draw();
}

