#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){


    // cargar del directorio y popular el directorio con la ruta
	// listDir(string path)
	directorio.listDir("imagenes");
	//directorio.stable_sort();

    // dimensionamos el tamano del vector de imagenes
    // al tamano de los archivos en el directorio*2
    imagenes.resize(directorio.numFiles()*2);
    	for(int i = 0; i < directorio.numFiles(); ++i) {

        cargadorImagenes.loadFromDisk(imagenes[i*2],directorio.getPath(i));
        //imprime todos los path de las fotos y el numero de fotos
        // en el directorio
        //ofLogNotice(directorio.getPath(i));
        //cout<<"numero de fototos"<< "\t"<< directorio.numFiles()<<endl;
	}
    // velocidad de reproduccion de la secuencia
    // independiente de la aplicacion
    bFrameindependiente = true;
    // fps de la secuencia y la app
    secuenciafps = 24;
    aplicacionfps =  60;
    // set del framerate
    ofSetFrameRate(aplicacionfps);

}

//--------------------------------------------------------------
void testApp::update(){

    tiempoTotalanimacion = imagenes.size()/secuenciafps;
}

//--------------------------------------------------------------
void testApp::draw(){

    // indice del frame donde estoy
    int frameIndex = 0;

    if(bFrameindependiente){

        // calcula el tiempo del frame basado en el tiempo de la app
        // y del tiempo deseado para la secuencia
        frameIndex = (int)(ofGetElapsedTimef() * secuenciafps) % imagenes.size();
    }
    else {
        // calcula el frame basado en el conteo de frames de la app
        frameIndex = ofGetFrameNum() % imagenes.size();
    }
    // dibuja la secuencia en mousex, mousey
    imagenes[frameIndex].draw(ofGetMouseX(),ofGetMouseY());

    // how fast is the app running and some other info
    ofSetColor(50);
    ofRect(0, 0, 250, 200);
    ofSetColor(200);
    string info;
    info += ofToString(frameIndex)+" indice de la secuencia\n";
    info += ofToString(aplicacionfps)+"/"+ofToString(ofGetFrameRate(), 0)+" fps\n";
    info += ofToString(secuenciafps)+" Secuencia fps\n\n";
    info += "Keys:\narriba & abajo para\ncambiar aplicacion fps\n\n";
    info += "izquierda & derecha para\ncambiar secuencia fps";
    info += "\n\n't'  toggle\nframe independiente("+ofToString(bFrameindependiente)+")";

    ofDrawBitmapString(info, 15, 20);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){


    if(key == OF_KEY_UP)      aplicacionfps ++;
    if(key == OF_KEY_DOWN)    aplicacionfps --;
    if(key == OF_KEY_LEFT)    secuenciafps --;
    if(key == OF_KEY_RIGHT)   secuenciafps ++;
    if(key == 't')            bFrameindependiente = !bFrameindependiente;

    // check for less than zero...
    secuenciafps = MAX(secuenciafps, 1);
    aplicacionfps = MAX(aplicacionfps, 1);

    ofSetFrameRate(aplicacionfps);

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
