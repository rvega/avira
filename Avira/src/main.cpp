#include "ofMain.h"
#include "ofAppGlutWindow.h"

#include "AviraApp.h"
#include "constantes.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, VENTANA_WIDTH, VENTANA_HEIGHT, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new AviraApp());
}
