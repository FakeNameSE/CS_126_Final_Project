#include "catch.hpp"
#include "ofApp.h"


// ============= Initialize. =============
TEST_CASE( "LoadJson properly returns a json object", "[LoadJson]") {
    bool loadin_worked = ofApp::LoadJson("../bin/data/dinosaur_data.json");
    CHECK( loadin_worked == true );
}

TEST_CASE( "LoadJson returns false on bad data", "[LoadJson]") {
    bool loadin_worked = ofApp::LoadJson("bad_data.json");   
    CHECK( loadin_worked == false );
}

TEST_CASE( "LoadJson returns false on bad filepath", "[LoadJson]") {
    bool loadin_worked = ofApp::LoadJson("bad_path");
    CHECK( loadin_worked == false );
}
