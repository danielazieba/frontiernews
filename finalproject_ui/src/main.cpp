#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}


/*
 in header file:
 
 ofTrueTypeFont headerFont;
 
 in setup:
 
 headerFont.load("Lora-Regular.ttf", 50, true, true, true);
 
 
 in draw:
 ofSetColor(0, 90, 60);
 ofFill();
 
 
 headerFont.drawString("Hello - I am bitmap", 50, 200);
 */
