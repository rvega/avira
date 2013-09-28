#include "AnimacionPajaro.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionPajaro::AnimacionPajaro(float x, float y):
Animacion(x,y)
{
    yOffset = 1;
   loop=true;
   width=0.4;
   setPath("animaciones/pajaro/pajaro");
}

AnimacionPajaro::~AnimacionPajaro(){ }
