#include "AnimacionEscenaAvira.h"
#include "AnimacionMunecoAvira.h"
#include "AnimacionCabeza.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscenaAvira::AnimacionEscenaAvira(float x, float y):
Animacion(x,y)
{
   complete = false;
   width=0.1;

   Animacion* muneco = new AnimacionMunecoAvira(x, y);
   animaciones.push_back(muneco);

   Animacion* cabeza = new AnimacionCabeza(x, y);
   cabeza->relativoAPersona = true;
   animaciones.push_back(cabeza);
}

AnimacionEscenaAvira::~AnimacionEscenaAvira(){ }

void AnimacionEscenaAvira::play(){
   animaciones.at(0)->play();
   complete = false;
   Animacion::play();
}

void AnimacionEscenaAvira::draw(){
   float elapsedTime = ofGetElapsedTimef() - startTime;
   if(playing && !animaciones.at(1)->playing && (elapsedTime >= 2)){
      animaciones.at(1)->play();
   }
   if(playing && (elapsedTime >= 10)){
      stop();
      complete = true;
   }
   Animacion::draw();
}

bool AnimacionEscenaAvira::isComplete(){
    return complete;
}
