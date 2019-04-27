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

    // Prompt the user if there is an issue loading the file.
    if (!(parsingSuccessful)) {
        ofSystemAlertDialog("Error loading dinosaur data!");
    }

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

    // Extract the data.
    string common_name = dino_info["dinosaurs"][index]["common_name"].asString();
    string scientifc_name = dino_info["dinosaurs"][index]["scientifc_name"].asString();
    string fact = dino_info["dinosaurs"][index]["fact"].asString();

    // Fill in the fields if they are empty.
    string placeholder = "";
    if (common_name == "") {
        common_name = placeholder;
    }
    if (scientifc_name == "") {
        scientifc_name = placeholder;
    }
    if (fact == "") {
        fact = placeholder;
    }

    // Put the information together nicely.
    dino_info_string = "Common name: " + common_name + "\n" + "Scientific name: "
    + scientifc_name + "\n" + "Fact: " + fact;

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
    // Convert the index number to the appropriate enum class type.
    active_brush_ = (Brushes) index;
}

/*
Run for the canvas window at the beginning.
*/
void ofApp::setup() {
    // Set background to white.
    ofBackground(kBackgroundColor);
    ofSetFrameRate(kMaxCanvasFrameRate);

    // Allocate memory for the FBO (framebuffer that we render).
    // This one is transparent and is just used for a preview brush circle that
    // follows the cursor when it is not drawing.
    preview_brush_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    // Set the FBO background color.
    preview_brush_fbo.begin();
    ofClear(kEmpty);
    preview_brush_fbo.end();

    // This one is for the actual canvas.
   // Allocate memory for the FBO (framebuffer that we render).
   canvas_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
   // Set the FBO background color.
   canvas_fbo.begin();
   ofClear(kBackgroundColor);
   canvas_fbo.end();
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
	brush_toggle_parameters_.add(pen.set("Pen", true));
	brush_toggle_parameters_.add(bubble_brush.set("Bubble Brush", false));
    brush_toggle_parameters_.add(eraser.set("Eraser" ,false));

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


    // Setup the utilities panel.
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
    // Save an image.
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
    brush_toggles_->getActiveToggleIndex().removeListener(this, &ofApp::BrushToggled);

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

    // Clear the preview fbo (to not leave tracks).
    preview_brush_fbo.begin();
    ofClear(kEmpty);
    preview_brush_fbo.end();

    // Select and call the appropriate brush drawing method if the mouse is
    // pressed.
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        // Render everything after this onto the Fbo renderer instead of the screen.
        // This prevents flickering issues.
        canvas_fbo.begin();
        if (active_brush_ == Brushes::PEN) {
            DrawWithPen(brush_thickness_, brush_color_);
        } else if (active_brush_ == Brushes::BUBBLE_BRUSH) {
            DrawWithBubbleBrush(brush_thickness_, brush_color_);
        } else if (active_brush_ == Brushes::ERASER) {
            Eraser(brush_thickness_, kBackgroundColor);
        }
        canvas_fbo.end();
    }
    // If we are not drawing, follow the cursor with a preview brush circle.
    else {
        preview_brush_fbo.begin();
        // We want a circle with the current brush color with a black outline,
        // so draw a slightly bigger black cicle, and then the other on top.
        ofSetColor(kBlack);
        // TODO extract to constant.
        ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 1.2 * brush_thickness_);

        // Set the color to the background if the eraser was selected.
        if (active_brush_ == Brushes::ERASER) {
            ofSetColor(kBackgroundColor);
        } else {
            ofSetColor(brush_color_);
        }

        ofDrawCircle(ofGetMouseX(), ofGetMouseY(), brush_thickness_);
        preview_brush_fbo.end();
    }

    // Now actually draw the two FBOs on screen, first the preview brush one.
    canvas_fbo.draw(0,0);
    preview_brush_fbo.draw(0,0);
}

void ofApp::SaveImageWrapper(bool pick_new_location) {
    // Handle picking a new file location if necessary.
    if (pick_new_location || file_location_ == "") {
        // Wipe this here to make sure the user properly sets it again, otherwise
        // aborting from choosing the path would still result in saving the image
        // to the old path.
        file_location_ = "";
        ofFileDialogResult result = ofSystemSaveDialog("dino.png", "Save");
        if(result.bSuccess) {
            file_location_ = result.getPath();
        }
    }

    // Once the location has been decided, save the image there.
    if (file_location_ != "") {
        // Inform the user if saving fails.
        if (!(SaveImage(file_location_))) {
            ofSystemAlertDialog("Error saving image!");
        } else {
            ofSystemAlertDialog("Image saved!");
        }
    }
}

bool ofApp::SaveImage(string filename) {
    ofPixels pixels;
    canvas_fbo.readToPixels(pixels);
    return ofSaveImage(pixels, filename + ".png", OF_IMAGE_QUALITY_BEST);
}

/*
void ofApp::LoadImage() {
    ofLoadImage()
}
*/

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 's') {
        SaveImageWrapper(true);
    }

    if (key == 'd') {
        SaveImageWrapper(false);
    }
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
