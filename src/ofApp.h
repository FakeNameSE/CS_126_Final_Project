#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxJSONElement.h"

using std::string;

class ofApp : public ofBaseApp {
	public:
		void setup();
		void exit();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		const string kDinoDataFilepath = "dinosaur_data.json";

		// Flag for if the JSON data was properly loaded.
		bool json_loaded_ = false;

		ofParameter<bool> show_dino_info_;

		ofxPanel utilities_panel_;
		ofxPanel paint_palette_;
		ofxButton dino_info_button_;

		ofxLabel dino_info_label_;
		ofParameter<std::string> dino_text_;

		ofxJSONElement dino_info_json_;

		bool LoadJson(string filepath);
		string RetrieveNewDinoInfo(ofxJSONElement dino_info);
		void DinoInfoButtonPressed();
};
