#pragma once

#include "ofMain.h"
#include "brushes.h"
#include "ofxGuiExtended.h"
#include "ofxJSONElement.h"

using std::string;

class ofApp : public ofBaseApp {
	public:
		//===================== OpenFrameworks methods. =======================
		void setup();
		void setupGui();
		void exitGui(ofEventArgs & args);
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

		// Framebuffer render that we draw to.
		// First one is for the canvas.
		ofFbo canvas_fbo;
		// Second goes on top for a preview brush that follows the cursor.
		ofFbo preview_brush_fbo;

		//============================= Constants. =============================
		const int kMaxCanvasFrameRate = 60;
		const string kDinoDataFilepath = "dinosaur_data.json";

		const ofColor kWhite = ofColor(255, 255, 255, 255);
		const ofColor kBlack = ofColor(0, 0, 0, 255);
		const ofColor kEmpty = ofColor(0, 0, 0, 0);
		// TODO change this to not rely on something else?
		const ofColor kBackgroundColor = kWhite;


		//============================== Flags. ================================
		// Flag for if the JSON data was properly loaded.
		bool json_loaded_ = false;
		// Flag to prevent Exit() from being called twice on close which would
		// cause a crash.
		bool exiting_ = false;

		//====================== Other non-GUI fields. =========================
		Brushes active_brush_;
		string file_location_ = "";

		//========================== GUI components ============================
		// The base GUI and panels.
		ofxGui gui_;
		ofxGuiPanel* paint_palette_panel_;
		ofxGuiPanel* utilities_panel_;
		ofxGuiPanel* dino_info_panel_;

		// Groups for UI elements.
		ofxGuiGroup* labels_;
		ofxGuiGroup* brush_settings_;
		ofxGuiGroup* brush_toggles_;

		//============================ Parameters. =============================
		// ofParameters, used to store values that can be set through the UI.
		ofParameter<string> dino_text_;
		ofParameter<int> brush_thickness_;
		ofParameter<ofColor> brush_color_;
		ofParameter<void> save_image;

		// Parameters for active brush, used to create the toggles.
		ofParameterGroup brush_toggle_parameters_;
		ofParameter<bool> pen;
		ofParameter<bool> bubble_brush;
		ofParameter<bool> eraser;

		ofxJSONElement dino_info_json_;

		//========================== Helper methods. ===========================
		bool LoadJson(string filepath);
		int PickRandomDinoIndex(ofxJSONElement dino_info);
		string RetrieveNewDinoInfo(ofxJSONElement dino_info, int index);
		bool SaveImage(string filename);
		void SaveImageWrapper(bool pick_new_location);

		//============================ Listeners. ==============================
		void DinoInfoButtonToggled(bool& new_val);
		void BrushToggled(int& index);
};
