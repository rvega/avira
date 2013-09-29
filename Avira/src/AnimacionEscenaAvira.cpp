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
   cabeza->relativoAPersona = true;
   animaciones.push_back(cabeza);
}

AnimacionEscenaAvira::~AnimacionEscenaAvira(){ }

void AnimacionEscenaAvira::play(){
   ofLogNotice() << "Play Muneco";
   ofLogNotice() << startTime;
   animaciones.at(0)->play();
   Animacion::play();
}

void AnimacionEscenaAvira::draw(){
   float elapsedTime = ofGetElapsedTimef() - startTime;
   if(playing && !animaciones.at(1)->playing && (elapsedTime >= 2)){
      ofLogNotice() << "Play Mask";
      ofLogNotice() << elapsedTime;
      animaciones.at(1)->play();
   }
   if(playing && (elapsedTime >= 10)){
      ofLogNotice() << "Stop";
      ofLogNotice() << elapsedTime;
      stop();
   }
   Animacion::draw();
}

