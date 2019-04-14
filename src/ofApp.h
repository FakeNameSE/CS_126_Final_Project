#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxJSONElement.h"

using std::string;

class ofApp : public ofBaseApp {
	public:
		void setup();
		void setupGui();
		void exit();
		void update();
		void draw();
		void drawGui(ofEventArgs & args);

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
		const int kMaxCanvasFrameRate = 60;
		const string kDinoDataFilepath = "dinosaur_data.json";
		const int kBrushInterpolationSizeCoeff = 0.9;
<<<<<<< HEAD
<<<<<<< HEAD
		const int kBrushInterpolationStepCoeff = 4;
=======
		const int kBrushInterpolationStepCoeff = 0.25;
>>>>>>> 611a791774079239e37771d89051217a2e2e81f7
=======
		const int kBrushInterpolationStepCoeff = 0.25;
>>>>>>> 611a791774079239e37771d89051217a2e2e81f7

		// Flag for if the JSON data was properly loaded.
		bool json_loaded_ = false;

		// The base GUI and panels.
		ofxGui gui_;
		ofxGuiPanel* paint_palette_panel_;
		ofxGuiPanel* utilities_panel_;
		ofxGuiPanel* dino_info_panel_;

		// Groups for UI elements.
		ofxGuiGroup* labels;

		// ofParameters, used to store values that can be set through the UI.
		ofParameter<string> dino_text_;

		ofxJSONElement dino_info_json_;

		bool LoadJson(string filepath);
		int PickRandomDinoIndex(ofxJSONElement dino_info);
		string RetrieveNewDinoInfo(ofxJSONElement dino_info, int index);
		void DinoInfoButtonToggled(bool& new_val);

		void DrawWithPen(int thickness, ofColor color);
};
