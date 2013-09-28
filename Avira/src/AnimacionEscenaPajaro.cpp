#include "AnimacionEscenaPajaro.h"
#include "AnimacionPajaro.h"
#include "AnimacionMundo.h"
#include "AnimacionBurbujas.h"
#include "AnimacionProbeta.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscenaPajaro::AnimacionEscenaPajaro(float x, float y):
Animacion(x,y)
{
   // fps=15;
   // width=0.1;
   elAccesorio = "probeta";

    // principal
   AnimacionPajaro* pajaro = new AnimacionPajaro(0,0);
   animaciones.push_back(pajaro);

    // accesorio default
   AnimacionMundo* mundi = new AnimacionMundo(pajaro -> getX(), pajaro -> getY());
   animaciones.push_back(mundi);

   // Consecuencia accesorio default:
    AnimacionMundo* mundi_concecuente = new AnimacionMundo(x, y);
    animaciones.push_back(mundi_concecuente);
    setCualAccesorio(elAccesorio);


}


// AnimacionEscenaPajaro::~AnimacionEscenaPajaro(){ }

void AnimacionEscenaPajaro::setCualAccesorio(string val){
//    // Quitar animaciones.at(1) osea el accesorio.
//    // Quitar animaciones.at(2) osea la consecuencia del accesorio (borbujas p. ej.)
     for( unsigned int i = 0; i<animaciones.size();i++)
     {
         animaciones.pop_back();


     }
    if(val == "probeta"){
       AnimacionProbeta* probeta = new AnimacionProbeta(animaciones.at(0)->getX(), animaciones.at(0)->getY());
       animaciones.push_back(probeta);

       AnimacionBurbujas* burbujas = new AnimacionBurbujas(animaciones.at(1)->getX(), animaciones.at(1)->getY());
       animaciones.push_back(burbujas);
    }
    else if(val=="mundo"){
            //SET en las posiciones del pajaro
       AnimacionMundo* mundi = new AnimacionMundo(animaciones.at(0)->getX(), animaciones.at(0)->getY());
       animaciones.push_back(mundi);

       AnimacionMundo* mundi2 = new AnimacionMundo(animaciones.at(1)->getX(), animaciones.at(1)->getY());
       animaciones.push_back(mundi2); // En el caso del mundo, la consecuencia es la misma animacion de el accesorio.
    }
//    // etc...
}


void AnimacionEscenaPajaro::play(){
   int duracionMovimientoPajaro = 5000;
   int delayMovimientoPajaro = 2000;
   tween.setParameters(easingLinear, ofxTween::easeInOut,0.01, 1,duracionMovimientoPajaro, delayMovimientoPajaro);

   animaciones.at(0)->play();
   animaciones.at(1)->stop();
   animaciones.at(2)->stop();

   Animacion::play();
}

void AnimacionEscenaPajaro::draw(){
   // Aqiui falta poner condicionales, tiempos, loquesea para mostrar la consecuencia.


   bool teAtrape = false;

   animaciones.at(0)->setX(tween.update());
    if(animaciones.at(0)->getX()>= 1)
    {
        tween.addValue(animaciones.at(0)->getX(),0);
        tween.start();
    }
   // si el pajaro.x es mayor o igual a el blob.x
   //TODO: medir distancia entre los dos puntos
   if(!animaciones.at(1)->playing && abs((animaciones.at(0)-> getX()-x)) >= 0.5 && !animaciones.at(2)->playing ){

      animaciones.at(1)->setX( animaciones.at(0)->getX() );
      animaciones.at(1)->setY( animaciones.at(0)->getY()+0.1 );

      animaciones.at(1)->play();
    // movimiento del accesorio
      multitween.setParameters(easingLinear,ofxTween::easeInOut,animaciones.at(1)->getX(),x+0.1, 1000, 50);
      multitween.addValue(animaciones.at(1)->getY(),y);
      multitween.start();


   }
    if(animaciones.at(1)->playing)
    {
        animaciones.at(1)->setX(multitween.update());
      animaciones.at(1)->setY(multitween.getTarget(1));

    }
   //compara la posicion de la animacion con la del blob
    // depurar
   if(ofDist(animaciones.at(0)-> getX(),animaciones.at(0)-> getY(),x,y) <= 0.05)
   {

      teAtrape = true;

   }
 ofLogNotice()<<"el absoluto"<<":   " << ofDist(animaciones.at(0)-> getX(),animaciones.at(0)-> getY(),x,y)<<endl;



   Animacion::draw();
}

