#include "AnimacionProbeta.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionProbeta::AnimacionProbeta(float x, float y):
Animacion(x,y)
{
   loop=true;
   width=0.15;
   setPath("animaciones/pajaro/accesorios/probeta");
}

AnimacionProbeta::~AnimacionProbeta(){ }
