#include "AnimacionMunecoAvira.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionMunecoAvira::AnimacionMunecoAvira(float x, float y):
Animacion(x,y)
{
   xInicial = x;
   yInicial = y;
   xOffset=-0.25;
   loop=false;
   width=0.4;
   setPath("animaciones/avira/muneco");
}

AnimacionMunecoAvira::~AnimacionMunecoAvira(){ }
