#include "AnimacionEscenaAvira.h"
#include "AnimacionMunecoAvira.h"
#include "AnimacionCabeza.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscenaAvira::AnimacionEscenaAvira(float x, float y):
Animacion(x,y)
{ 
   width=0.1;

   Animacion* muneco = new AnimacionMunecoAvira(x, y);
   animaciones.push_back(muneco);

   Animacion* cabeza = new AnimacionCabeza(x, y);
   animaciones.push_back(cabeza);
}

AnimacionEscenaAvira::~AnimacionEscenaAvira(){ } 

void AnimacionEscenaAvira::play(){
   animaciones.at(0)->play();
   Animacion::play();
}

void AnimacionEscenaAvira::draw(){
   if(!animaciones.at(1)->playing && (ofGetElapsedTimef() - startTime >= 2)){
      animaciones.at(1)->play();
   }
   Animacion::draw();
}

