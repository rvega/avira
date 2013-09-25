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
   timer = ofGetElapsedTimef();
   ofLogNotice() << "Play Muneco";
   ofLogNotice() << timer;
   animaciones.at(0)->play();
   Animacion::play();
}

void AnimacionEscenaAvira::draw(){
   if(playing && !animaciones.at(1)->playing && (ofGetElapsedTimef() - timer >= 2)){
      ofLogNotice() << "Play Mask";
      ofLogNotice() << timer;
      animaciones.at(1)->play();
   }
   if(playing && (ofGetElapsedTimef() - timer >= 10)){
      ofLogNotice() << "Stop";
      ofLogNotice() << timer;
      stop();
   }
   Animacion::draw();
}

