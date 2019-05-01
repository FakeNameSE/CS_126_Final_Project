#include "brushes.h"
#include <math.h>
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

    // Now we plot circles along this line to try to fill in some blank areas.
    for (int x = ofGetPreviousMouseX(); x < ofGetMouseX(); x += (thickness / kBrushInterpolationStepCoeff)) {
        ofDrawCircle(x, slope * (x - ofGetPreviousMouseX()) + ofGetPreviousMouseY(), thickness * kBrushInterpolationSizeCoeff);
    }
}

/*
Brush based off of pen but for which the radius and opacity decrease linearly with
respect to the speed of the brush (how far the cursor moved in a cycle).
*/
void DrawWithCalligraphyBrush(int thickness, ofColor color) {
    // Create vectors for the mouse location.
    ofVec2f mouse_pos(ofGetMouseX(), ofGetMouseY());
    ofVec2f prev_mouse_pos(ofGetPreviousMouseX(), ofGetPreviousMouseY());
    int new_thickness = 0;
    ofColor new_color = color;

    int distance_traveled = mouse_pos.distance(prev_mouse_pos);

    // Apply a simple linear function to make thickness and opacity decrease with
    // spead if the stroke. We use absolute value to introduce some irregularities
    // and avoid negatives.
    new_color.a = std::abs(color.a - kCalligraphyAlphaDecrease * distance_traveled);
    new_thickness = std::abs(thickness - kCalligraphyThicknessDecrease * distance_traveled);

    // These values got way to big if they got really small and the absolute value
    // flipped the sign. In this case, it would be invisible, so do nothing.
    // OF crashed drawing circles smaller than this.
    if (new_thickness > thickness || new_thickness < kMinCircleRadius
      || new_color.a > kMaxAlpha) {
          return;
    }

    // Finally, draw using the pen and these modified parameters.
    DrawWithPen(new_thickness, new_color);
}

/*
Helper method to draw a brush consisting of triangles roughly following the mouse.
*/
void DrawWithTriangles(int thickness, ofColor color) {
    ofSetColor(color);

    ofVec2f mouse_pos(ofGetMouseX(), ofGetMouseY());
    // We initialize a triangle at the origin pointing to the right.
    ofVec2f point_1(0, thickness);
    ofVec2f point_2(thickness, 0);
    ofVec2f point_3(0, -1 * thickness);

    // Now we use some trig to calculate the angle to rotate the triangle such
    // that it is facing the mouse.
    float opposite = ofGetMouseY() - ofGetPreviousMouseY();
    float adjacent = ofGetMouseX() - ofGetPreviousMouseX();
    float rotation_rads = atan2(opposite, adjacent);
    // Convert from radians to degrees.
    float rotation_degrees = glm::degrees(rotation_rads);
    // Rotate the tip of the triangle.
    point_2.rotate(glm::degrees(rotation_degrees));

    // Here we shift all three vertices so the triangle is next to the cursor.
    point_1 += mouse_pos;
    point_2 += mouse_pos;
    point_3 += mouse_pos;

    // Finally, draw it.
    ofDrawTriangle(point_1, point_2, point_3);

    // And to add some pizazz, draw a few more near there.
    int num_triangles = ofRandom(0, kTriangleVariance);
    for (int i = 0; i < num_triangles; i++) {
        ofVec2f offset(ofRandom(-1 * kTriangleVariance, kTriangleVariance),
          ofRandom(-1 * kTriangleVariance, kTriangleVariance));
        ofDrawTriangle(point_1, point_2 + offset, point_3);
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

void PreviewBrush(int thickness, ofColor color, Brushes active_brush,
  ofColor background_color) {
    ofColor black = ofColor(0, 0, 0, 255);
    // We want a circle with the current brush color with a black outline,
    // so draw a slightly bigger black cicle, and then the other on top.
    ofSetColor(black);
    // TODO extract to constant.
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 1.2 * thickness);

    // Set the color to the background if the eraser was selected.
    if (active_brush == Brushes::ERASER) {
        ofSetColor(background_color);
    } else {
        ofSetColor(color);
    }

    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), thickness);
}
