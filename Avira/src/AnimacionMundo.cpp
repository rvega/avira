#include "AnimacionMundo.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionMundo::AnimacionMundo(float x, float y):
Animacion(x,y)
{
   loop=true;
   width=0.15;
   setPath("animaciones/pajaro/accesorios/mundi");
}

AnimacionMundo::~AnimacionMundo(){ }
