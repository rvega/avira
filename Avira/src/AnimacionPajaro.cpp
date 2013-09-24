#include "AnimacionPajaro.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionPajaro::AnimacionPajaro(float x, float y):
Animacion(x-0.3,y)
{
   loop=true;
   width=0.4;
   setPath("animaciones/pajaro/pajaro");
}

AnimacionPajaro::~AnimacionPajaro(){ }
