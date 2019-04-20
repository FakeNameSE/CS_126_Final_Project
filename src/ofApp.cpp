#include "ofApp.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

/*
Helper method to load the JSON file.

Returns false if there is an error loading it.
*/
bool ofApp::LoadJson(string filepath) {
    bool parsingSuccessful = dino_info_json_.open(filepath);
    //TODO Remove.
    //ofLogNotice("ofApp::setup") << dino_info_json_.getRawString();

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
    + "\n" + "Scientific name: " + dino_info["dinosaurs"][index]["scientifc_name"].asString()
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

void ofApp::BrushToggled(int& index) {
    active_brush_ = (Brushes) index;
}

/*
Run for the canvas window at the beginning.
*/
void ofApp::setup() {
    // Disable repainting the background.
    ofSetBackgroundAuto(false);
    // Set background to white.
    ofBackground(kWhite);
    //ofSetFrameRate(kMaxCanvasFrameRate);
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
    dino_info_panel_->setPosition(20, 10);
    utilities_panel_->setPosition(20, 150);
    paint_palette_panel_->setPosition(20, 220);

    // Build the paint palette panel.
    // Setup and add a parameter group to toggle the brush type.
    brush_toggle_parameters_.setName("Brushes");
	brush_toggle_parameters_.add(pen.set("Pen",true));
	brush_toggle_parameters_.add(bubble_brush.set("Bubble Brush",false));

	brush_toggles_ = paint_palette_panel_->addGroup(brush_toggle_parameters_);
	brush_toggles_->setExclusiveToggles(true);

    // Add a group for brush settings.
    brush_settings_ = paint_palette_panel_->addGroup("Brush Settings:");
    // Setup and add a control for brush thickness.
    brush_thickness_.set("Brush Thickness",10,10,100); // Use the first parameter to set the initial lower value and the min and max value
    brush_settings_->add(brush_thickness_);
    // Setup and add a control for brush color.
    brush_color_.set("Color",ofColor(0,0,0,255), ofColor(0,0,0,0), ofColor(255,255,255,255));
    brush_settings_->add(brush_color_);


    // Add toggle for the dinosaur info panel visibility.
    // Just hook this up to the visibility attribute of the panel directly.
    utilities_panel_->add(dino_info_panel_->getVisible().set("Show dinosaur facts", false));
    // Hide the panel by default.
    dino_info_panel_->getVisible().set(false);

    // Setup labels for dinosaur facts, add them to the dino_info_panel_.
    labels_ = dino_info_panel_->addGroup("The basics:");
    labels_->add(dino_text_);

    // Flip the flag depending on whether loading the json was successful.
    json_loaded_ = LoadJson(kDinoDataFilepath);

    // Set this to a longer one at the beginning to prevent text overflowing on
    // the first toggle.
    dino_text_.set(RetrieveNewDinoInfo(dino_info_json_, 0));

    // Set listeners.
    // Change the brush.
    brush_toggles_->getActiveToggleIndex().addListener(this, &ofApp::BrushToggled);
	brush_toggles_->setActiveToggle(0);
    active_brush_ = (Brushes) 0;

    // To update the dinosaur info for the label.
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
Run once a cycle for the canvas.
*/
void ofApp::draw() {
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        DrawWithBubbleBrush(brush_thickness_, brush_color_);
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
