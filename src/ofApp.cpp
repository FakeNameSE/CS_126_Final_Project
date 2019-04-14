#include "ofApp.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

//--------------------------------------------------------------
bool ofApp::LoadJson(string filepath) {
    bool parsingSuccessful = dino_info_json_.open(filepath);
    ofLogNotice("ofApp::setup") << dino_info_json_.getRawString();

    return parsingSuccessful;
}

string ofApp::RetrieveNewDinoInfo(ofxJSONElement dino_info) {
    string dino_info_string;
    // Randomly select a dinosaur
    int dino_index = rand() % dino_info["dinosaurs"].size();

    // Put the information together nicely.
    dino_info_string = "Common name: " + dino_info["dinosaurs"][dino_index]["common_name"].asString()
    + "\n" + "Scientific name: " + dino_info["dinosaurs"][dino_index]["scientific_name"].asString()
    + "\n" + "Fact: " + dino_info["dinosaurs"][dino_index]["fact"].asString();

    return dino_info_string;
}

void ofApp::DinoInfoButtonToggled(bool& new_val) {
    // Set a new dinosaur's information to display.
    string dino_info_string = RetrieveNewDinoInfo(dino_info_json_);
    if (json_loaded_) {
        dino_text_.set(dino_info_string);
    }
    // Handle JSON data not being loaded.
    else {
        dino_text_.set("Unable to load dinosaur JSON data.");
    }
}

void ofApp::setup() {
    // Disable repainting the background.
    ofSetBackgroundAuto(false);
}

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

    // Set listeners.
    // Put at end, since otherwise the premature reference to the json object
    // results in a floating point runtime error.
    dino_info_panel_->getVisible().addListener(this, &ofApp::DinoInfoButtonToggled);
}

//--------------------------------------------------------------
void ofApp::exit(){
	dino_info_panel_->getVisible().removeListener(this, &ofApp::DinoInfoButtonToggled);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args) {
}


void ofApp::DrawWithPen(int thickness, ofColor color) {
    ofLogNotice("ofApp::mouse") << ofGetMouseX() << ", " << ofGetMouseY() << std::endl;
    ofSetColor(color);

    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), thickness);
    ofDrawCircle(ofGetPreviousMouseX(), ofGetPreviousMouseY(), thickness);
    ofDrawCircle((ofGetMouseX() + ofGetPreviousMouseX()) / 2, (ofGetMouseY() + ofGetPreviousMouseY()) / 2, thickness);


    int cartesian_x_change = ofGetMouseX() - ofGetPreviousMouseX();
    int cartesian_y_change = ofGetMouseY() - ofGetPreviousMouseY();

    float screen_x_change = cartesian_x_change + (ofGetWindowWidth() / 2);
    float screen_y_change = (ofGetWindowHeight() / 2) - cartesian_y_change;
    float slope = screen_y_change / screen_x_change;

    ofSetRectMode(OF_RECTMODE_CENTER);
    ofLogNotice("ofApp::slope") << screen_x_change << " " << screen_y_change << " " << slope << std::endl;

    for (int x = ofGetPreviousMouseX(); x < ofGetMouseX(); x += (thickness * kBrushInterpolationStepCoeff)) {
        ofDrawCircle(x, slope * (x - ofGetPreviousMouseX()) + ofGetPreviousMouseY(), thickness * kBrushInterpolationSizeCoeff);
    }
}

//--------------------------------------------------------------
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
