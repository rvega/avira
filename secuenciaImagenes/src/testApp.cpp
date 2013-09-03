#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //cantidad de imagenes que vamos a cargar
    numeroImagenes = 12;
    // dimensionamos el tamano del vector de imagenes
    imagenes.resize(numeroImagenes*2);
    	for(int i = 0; i < numeroImagenes; ++i) {
		cargadorImagenes.loadFromDisk(imagenes[i*2], "PT_anim" + ofToString(i) + ".gif");

	}
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){

    	// draw the images.
	ofSetColor(255);
	for(int i = 0; i < (int)imagenes.size(); ++i) {
		int x = (i%8);
		int y = (i/8);
		imagenes[i].draw(x*128,y*128, 128,128);
	}

	// draw the FPS
	ofRect(0,ofGetHeight()-20,30,20);

	ofSetColor(0);
	ofDrawBitmapString(ofToString(ofGetFrameRate(),0),5,ofGetHeight()-5);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
