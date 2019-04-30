#pragma once

#include "ofMain.h"

//============================ Helpful Constants. ==============================

//------------------------------------ Pen -------------------------------------
// Determines the percentage of the radius that the interpolation circle's
// radius is, the bigger it is the smaller the hole, but the uglier.
const int kBrushInterpolationSizeCoeff = 0.8;
// We divide the radius by this to determine the stepping size for the
// interval over which we draw interpolations.
const int kBrushInterpolationStepCoeff = 4;

//-------------------------------- Calligraphy ---------------------------------
// Linear rates at which the opacity and thickness decrease with respect to speed
// for the calligraphy brush.
const float kCalligraphyAlphaDecrease = 5.0;
const float kCalligraphyThicknessDecrease = 2.5;
// OF crashes drawing smaller circles than this.
const int kMinCircleRadius = 4;
const int kMaxAlpha = 255;

//---------------------------------- Triangle ----------------------------------
// Variance in triangle position and number for the triangle brush.
const int kTriangleVariance = 3;


enum class Brushes {
  PEN,
  CALLIGRAPHY_BRUSH,
  TRIANGLE_BRUSH,
  BUBBLE_BRUSH,
  ERASER
};

//============================= Brushes. ===============================
void DrawWithPen(int thickness, ofColor color);
void DrawWithCalligraphyBrush(int thickness, ofColor color);
void DrawWithTriangles(int thickness, ofColor color);
void DrawWithBubbleBrush(int thickness, ofColor color);
void Eraser(int thickness, ofColor color);
void PreviewBrush(int thickness, ofColor color, Brushes active_brush,
  ofColor background_color);
