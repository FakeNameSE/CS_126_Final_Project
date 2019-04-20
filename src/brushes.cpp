#include "brushes.h"
#include "ofApp.h"

/*
Helper method to draw with a pen like brush, takes a color and line thickness as
arguments.

Most of the fancy stuff in here is to reduce the choppy appearance of having
circles with a bunch of gaps between them, which is mainly due to the mouse
moving faster than the draw cycle (does not seem to be fixable).
To accomplish this we use line interpolation and paint a circle where we were before.
*/
void DrawWithPen(int thickness, ofColor color) {
    // TODO remove
    //ofLogNotice("ofApp::mouse") << ofGetMouseX() << ", " << ofGetMouseY() << std::endl;

    // Set the color of the brush.
    ofSetColor(color);

    // Draw one circle where the mouse is, one where we were, and one in between.
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), thickness);
    ofDrawCircle(ofGetPreviousMouseX(), ofGetPreviousMouseY(), thickness);
    ofDrawCircle((ofGetMouseX() + ofGetPreviousMouseX()) / 2, (ofGetMouseY() + ofGetPreviousMouseY()) / 2, thickness);


    // Because the mouse can move faster than the draw cycle updates, we need this
    // fun stuff in a vain attempt to fill in gaps in brush strokes.
    // Here we calculate the "slope" of the line between where we were and where
    // we ended up for line interpolation.
    int cartesian_x_change = ofGetMouseX() - ofGetPreviousMouseX();
    int cartesian_y_change = ofGetMouseY() - ofGetPreviousMouseY();

    // We need to shift our coordinate system to line up with 0 being top left
    // and everything being positive.
    float screen_x_change = cartesian_x_change + (ofGetWindowWidth() / 2);
    float screen_y_change = (ofGetWindowHeight() / 2) - cartesian_y_change;

    float slope = screen_y_change / screen_x_change;

    // TODO remove.
    //ofLogNotice("ofApp::slope") << screen_x_change << " " << screen_y_change << " " << slope << std::endl;

    // Now we plot circles along this line to try to fill in some blank areas.
    for (int x = ofGetPreviousMouseX(); x < ofGetMouseX(); x += (thickness / kBrushInterpolationStepCoeff)) {
        ofDrawCircle(x, slope * (x - ofGetPreviousMouseX()) + ofGetPreviousMouseY(), thickness * kBrushInterpolationSizeCoeff);
    }
}

/*
Method that will paint a bunch of circles of different sizes and lightly varying
colors, can look like spray paint if the opacity is increased.

Takes a color and max circle radius as arguments.

Adapted to work with differing sizes and an arbitrary color from the Glowing line
brush in the OF Book.
*/
void DrawWithBubbleBrush(int thickness, ofColor color) {
    //TODO Move these to header?
    // Determines how wide brush is.
    int max_radius = thickness;
    // The lower this value, the more circles we get.
    int radius_step_size = 3;
    // Determines spread of circles.
    int max_offset_distance = thickness;
    //Determines the lower bound in dimness for the color we select for each circle.
    float dimming_factor = 0.8;

    for (int radius = max_radius; radius > 0; radius -= radius_step_size) {
        // We put the circles in a circle using polar coordinates, so convert and
        // convert those coordinates into radians.
        float angle = ofRandom(ofDegToRad(360.0));
        float distance = ofRandom(max_offset_distance);
        float xOffset = cos(angle) * distance;
        float yOffset = sin(angle) * distance;

        // For every circle, randomly select a color between the selected one and
        // a dimmer version of the selected one.
        ofColor darkened_color = ofColor(color.r * dimming_factor,
          color.g * dimming_factor, color.b * dimming_factor, color.a);
        ofColor in_between_color = color.getLerped(darkened_color, ofRandom(1.0));
        ofSetColor(in_between_color);

        ofDrawCircle(ofGetMouseX()+xOffset, ofGetMouseY()+yOffset, radius);
    }
}

void Eraser(int thickness, ofColor color) {
    // Set the color of the brush (here to the background color).
    ofSetColor(color);

    // Draw one circle where the mouse is, might be choppy but gives much more
    // fine-grained control.
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), thickness);
}
