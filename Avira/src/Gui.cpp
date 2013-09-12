#include "Gui.h"
#include "constantes.h"

Gui::Gui():
   fullscreen(false),

   // Invoca el constructor de ofxUI para la variable gui:
   gui(GUI_POS_X, GUI_POS_Y, GUI_WIDTH, 0)
{}

Gui::~Gui(){}

void Gui::setup(){
   gui.addLabel("Opciones", OFX_UI_FONT_MEDIUM);
   gui.setWidgetFontSize(OFX_UI_FONT_SMALL);
   gui.addSpacer(GUI_WIDTH,1);
   ofColor bgColor = ofColor(50, 50, 50);
   gui.setColorBack(bgColor);
   gui.addButton("Usar Camara", true);
   gui.addButton("Usar Pelicula", true);
   gui.addButton("Capturar Fondo", true);
   gui.addButton("Pantalla Completa", true);
   gui.addSpacer(GUI_WIDTH, 0);
   gui.addLabel("Cualquier tecla para", OFX_UI_FONT_SMALL);
   gui.addLabel("salir de pantalla", OFX_UI_FONT_SMALL);
   gui.addLabel("completa", OFX_UI_FONT_SMALL);
   gui.addSpacer(GUI_WIDTH, 0);
   gui.autoSizeToFitWidgets();

   ofAddListener(gui.newGUIEvent, this, &Gui::guiEvent);
   ofAddListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
}

void Gui::exit(){
   ofRemoveListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofRemoveListener(ofEvents().keyPressed, this, &Gui::keyPressed);
   ofRemoveListener(gui.newGUIEvent, this, &Gui::guiEvent);
}

void Gui::guiEvent(ofxUIEventArgs &e) {
   bool value = ((ofxUIButton*)(e.widget))->getValue();
   if(e.widget->getName()=="Pantalla Completa" && value) {
      fullscreen = true;
      gui.setVisible(false);
      ofSendMessage("FULLSCREEN_ON");
   }
   if(e.widget->getName()=="Capturar Fondo" && value) {
      ofSendMessage("CAPTURAR_FONDO");
   }
}

void Gui::mousePressed(ofMouseEventArgs& data){
   if(fullscreen){
      fullscreen = false;
      gui.setVisible(true);
      ofSendMessage("FULLSCREEN_OFF");
   }
}

void Gui::keyPressed(ofKeyEventArgs& data){
   if(fullscreen){
      fullscreen=false;
      gui.setVisible(true);
      ofSendMessage("FULLSCREEN_OFF");
   }
}

