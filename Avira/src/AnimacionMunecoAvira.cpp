#include "AnimacionMunecoAvira.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionMunecoAvira::AnimacionMunecoAvira(float x, float y):
Animacion(x-0.3,y)
{ 
   loop=false;
   width=0.4;
   setPath("animaciones/avira/muneco");
}

AnimacionMunecoAvira::~AnimacionMunecoAvira(){ } 
