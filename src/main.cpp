#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
    settings.setSize(1200, 950);
	settings.setPosition(ofVec2f(475,0));
	settings.resizable = false;
	settings.title = "DinoDoodle Canvas";
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    settings.setSize(470, 950);
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = false;
	settings.title = "DinoDoodle Controls";
	// uncomment next line to share main's OpenGL resources with gui
	//settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
	guiWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	mainApp->setupGui();

	ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::drawGui);
	// Listener for closing both windoes when one closes
	ofAddListener(guiWindow->events().exit, mainApp.get(), &ofApp::exitGui);

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
