#include "AnimacionBurbujas.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionBurbujas::AnimacionBurbujas(float x, float y):
Animacion(x,y)
{
   loop=true;
   width=0.3;
   setPath("animaciones/pajaro/accesorios/burbujas");
}

AnimacionBurbujas::~AnimacionBurbujas(){ }
