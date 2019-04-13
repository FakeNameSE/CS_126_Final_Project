#include "ofApp.h"
#include <stdlib.h>
#include <time.h>

//--------------------------------------------------------------
bool ofApp::LoadJson(string filepath) {
    bool parsingSuccessful = dino_info_json_.open(filepath);
    ofLogNotice("ofApp::setup") << dino_info_json_.getRawString();

    return parsingSuccessful;
}

string ofApp::RetrieveNewDinoInfo(ofxJSONElement dino_info) {
    string dino_info_string;
    int dino_index = rand() % dino_info["dinosaurs"].size();
    ofLogNotice("ofApp::setup") << dino_index;
    dino_info_string = "Common name: " + dino_info["dinosaurs"][dino_index]["common_name"].asString()
    + "\n" + "Scientific name: " + dino_info["dinosaurs"][dino_index]["scientific_name"].asString()
    + "\n" + "Fact: " + dino_info["dinosaurs"][dino_index]["fact"].asString();

    return dino_info_string;
}

void ofApp::DinoInfoButtonPressed() {
    // If we are going to make the label visible, then load new data.
    if (!show_dino_info_) {
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

    // Toggle the visibility of the label.
    show_dino_info_.set(!show_dino_info_);
}

void ofApp::setup() {
    ofxBaseGui::setDefaultTextPadding(0);

    // Initialize the random number generator seed.
    srand (time(NULL));

    show_dino_info_.set(false);

    dino_info_button_.addListener(this,&ofApp::DinoInfoButtonPressed);

    utilities_panel_.setup("Dinosaur Facts");
    // TODO change this to a toggle.
    utilities_panel_.add(dino_info_button_.setup("Toggle dino info"));

    // Flip the flag depending on whether loading the json was successful.
    json_loaded_ = LoadJson(kDinoDataFilepath);
    dino_info_label_.setup(dino_text_, 500, 400);

    paint_palette_.setup("Palette");
    paint_palette_.setPosition(0, 50); // sets position to avoid overlaping

}

//--------------------------------------------------------------
void ofApp::exit(){
	dino_info_button_.removeListener(this,&ofApp::DinoInfoButtonPressed);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    utilities_panel_.draw();
    paint_palette_.draw();
    if (show_dino_info_) {
        dino_info_label_.draw();
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
