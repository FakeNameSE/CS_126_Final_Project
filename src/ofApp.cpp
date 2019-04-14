#include "ofApp.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

//--------------------------------------------------------------
/*
Helper method to load the JSON file.

Returns false if there is an error loading it.
*/
bool ofApp::LoadJson(string filepath) {
    bool parsingSuccessful = dino_info_json_.open(filepath);
    ofLogNotice("ofApp::setup") << dino_info_json_.getRawString();

    return parsingSuccessful;
}

/*
Helper method that returns a random int within the range of the dinosaur JSON array.
*/
int ofApp::PickRandomDinoIndex(ofxJSONElement dino_info) {
    // Randomly select a dinosaur
    int dino_index = rand() % dino_info["dinosaurs"].size();

    return dino_index;
}

/*
Helper method that returns a string containing the information on one dinosaur
in the JSON file.
*/
string ofApp::RetrieveNewDinoInfo(ofxJSONElement dino_info, int index) {
    string dino_info_string;

    // Put the information together nicely.
    dino_info_string = "Common name: " + dino_info["dinosaurs"][index]["common_name"].asString()
    + "\n" + "Scientific name: " + dino_info["dinosaurs"][index]["scientific_name"].asString()
    + "\n" + "Fact: " + dino_info["dinosaurs"][index]["fact"].asString();

    return dino_info_string;
}

/*
Method called when the visibility of the dinosaur information panel is toggled.
This just sets the ofParameter for the label text to a random dinosaur's info
from RetrieveNewDinoInfo.
*/
void ofApp::DinoInfoButtonToggled(bool& new_val) {
    // Only do stuff if the panel will be made visible.
    if (new_val) {
        // Set a new random dinosaur's information to display.
        int dino_index = PickRandomDinoIndex(dino_info_json_);
        string dino_info_string = RetrieveNewDinoInfo(dino_info_json_, dino_index);
        if (json_loaded_) {
            dino_text_.set(dino_info_string);
        }
        // Handle JSON data not being loaded.
        else {
            dino_text_.set("Unable to load dinosaur JSON data.");
        }
    }
}

/*
Run for the canvas window at the beginning.
*/
void ofApp::setup() {
    // Disable repainting the background.
    ofSetBackgroundAuto(false);
    ofSetFrameRate(kMaxCanvasFrameRate);
}

/*
Run by the UI window at the beginning, sets up of the buttons, panels, labels,
and listeners.
*/
void ofApp::setupGui() {
    // Initialize the random number generator seed.
    srand(time(NULL));

    // Add the panels to the GUI.
    paint_palette_panel_ = gui_.addPanel("Palette");
    utilities_panel_ = gui_.addPanel("Utilities");
    dino_info_panel_ = gui_.addPanel("Dinosaur Facts");

    // Set their default locations to prevent overlapping.
    paint_palette_panel_->setPosition(20,20);
	utilities_panel_->setPosition(20,50);
    dino_info_panel_->setPosition(20, 120);

    // Add toggle for the dinosaur info panel visibility.
    // Just hook this up to the visibility attribute of the panel directly.
    utilities_panel_->add(dino_info_panel_->getVisible().set("Show dinosaur facts", false));
    // Hide the panel by default.
    dino_info_panel_->getVisible().set(false);

    // Setup labels for dinosaur facts, add them to the dino_info_panel_.
    labels = dino_info_panel_->addGroup("The basics:");
    labels->add(dino_text_);

    // Flip the flag depending on whether loading the json was successful.
    json_loaded_ = LoadJson(kDinoDataFilepath);

    // Set this to a longer one at the beginning to prevent text overflowing on
    // the first toggle.
    dino_text_.set(RetrieveNewDinoInfo(dino_info_json_, 0));

    // Set listeners.
    // Put at end, since otherwise the premature reference to the json object
    // results in a floating point runtime error.
    dino_info_panel_->getVisible().addListener(this, &ofApp::DinoInfoButtonToggled);
}

/*
Need this to close both windows when one is closed.
*/
void ofApp::exitGui(ofEventArgs & args) {
	exit();
}

/*
Run when the UI window closes, needs to remove listeners and close window.
*/
void ofApp::exit(){
	dino_info_panel_->getVisible().removeListener(this, &ofApp::DinoInfoButtonToggled);

    // Apparently, this is the one that closes when exit is called, so use flag
    // to prevent exiting twice and crashing.
    // Would not have figured this out without https://forum.openframeworks.cc/t/closing-multiple-windows-when-any-are-closed/27833
    if (!exiting_) {
		exiting_ = true;
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args) {
}


/*
Helper method to draw with a pen like brush, takes a color and line thickness as
arguments.

Most of the fancy stuff in here is to reduce the choppy appearance of having
circles with a bunch of gaps between them, which is mainly due to the mouse
moving faster than the draw cycle (does not seem to be fixable).
To accomplish this we use line interpolation and paint a circle where we were before.
*/
void ofApp::DrawWithPen(int thickness, ofColor color) {
    // TODO remove
    //ofLogNotice("ofApp::mouse") << ofGetMouseX() << ", " << ofGetMouseY() << std::endl;

    // Set the color of the brush.
    ofSetColor(color);

    // Draw one circle where the mouse is, one where we were, and one in between.
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), thickness);
    ofDrawCircle(ofGetPreviousMouseX(), ofGetPreviousMouseY(), thickness);
    ofDrawCircle((ofGetMouseX() + ofGetPreviousMouseX()) / 2, (ofGetMouseY() + ofGetPreviousMouseY()) / 2, thickness);


    // Because the mouse can move faster than
    // Here we calculate the "slope" of the line between where we were and where
    // we ended up for line interpolation.
    int cartesian_x_change = ofGetMouseX() - ofGetPreviousMouseX();
    int cartesian_y_change = ofGetMouseY() - ofGetPreviousMouseY();

    float screen_x_change = cartesian_x_change + (ofGetWindowWidth() / 2);
    float screen_y_change = (ofGetWindowHeight() / 2) - cartesian_y_change;
    float slope = screen_y_change / screen_x_change;

    // TODO remove.
    //ofLogNotice("ofApp::slope") << screen_x_change << " " << screen_y_change << " " << slope << std::endl;

    for (int x = ofGetPreviousMouseX(); x < ofGetMouseX(); x += (thickness / kBrushInterpolationStepCoeff)) {
        ofDrawCircle(x, slope * (x - ofGetPreviousMouseX()) + ofGetPreviousMouseY(), thickness * kBrushInterpolationSizeCoeff);
    }
}

/*
Run once a cycle for the canvas.
*/
void ofApp::draw() {
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        ofColor myOrange(255, 132, 0, 255);
        DrawWithPen(10, myOrange);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
