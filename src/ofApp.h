#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxJSONElement.h"
#include <utility>
#include "brushes.h"

using std::string;

class ofApp : public ofBaseApp {
	public:
		//===================== OpenFrameworks methods. =======================
		void setup();
		void setupGui();
		void exitGui(ofEventArgs & args);
		void exit();
		void draw();
		void drawGui(ofEventArgs & args);
		void keyPressed(int key);
		void dragEvent(ofDragInfo dragInfo);

		// Framebuffer render that we draw to.
		// First one is for the canvas.
		ofFbo canvas_fbo;
		// Second goes on top for a preview brush that follows the cursor.
		ofFbo preview_brush_fbo;

		//============================= Constants. =============================
		const std::pair<int, int> kDinoPanelPanelCoords = {20, 10};
		const std::pair<int, int> kUtililtyPanelCoords = {20, 150};
		const std::pair<int, int> kPalettePanelCoords = {20, 410};
		const int kMaxCanvasFrameRate = 60;
		const string kDinoDataFilepath = "dinosaur_data.json";

		const ofColor kWhite = ofColor(255, 255, 255, 255);
		const ofColor kBlack = ofColor(0, 0, 0, 255);
		const ofColor kEmpty = ofColor(0, 0, 0, 0);
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
		ofxGuiGroup* dino_info_group_;
		ofxGuiGroup* brush_settings_group_;
		ofxGuiGroup* brush_toggles_group_;
		ofxGuiGroup* instructions_group_;

		//============================ Parameters. =============================
		// ofParameters, used to store values that can be set through the UI.
		// Text to show in the dino information label.
		ofParameter<string> dino_text_;
		// Text to show in the instructions label.
		ofParameter<string> program_instructions_;
		ofParameter<string> welcome_message_;
		// Brush parameters.
		ofParameter<int> brush_thickness_;
		ofParameter<ofColor> brush_color_;

		// Parameters for active brush, used to create the toggles.
		ofParameterGroup brush_toggle_parameters_;
		ofParameter<bool> pen_;
		ofParameter<bool> calligraphy_brush_;
		ofParameter<bool> triangle_brush_;
		ofParameter<bool> bubble_brush_;
		ofParameter<bool> eraser_;

		ofxJSONElement dino_info_json_;

		//========================== Helper methods. ===========================
		bool LoadJson(string filepath);
		int PickRandomDinoIndex(ofxJSONElement dino_info);
		string RetrieveNewDinoInfo(ofxJSONElement dino_info, int index);
		void ClearCanvas();
		bool SaveImage(string filename);
		void SaveImageWrapper(bool pick_new_location);
		bool OpenImage(string filename);
		void OpenImageWrapper();

		//============================ Listeners. ==============================
		void DinoInfoButtonToggled(bool& new_val);
		void BrushToggled(int& index);
};
