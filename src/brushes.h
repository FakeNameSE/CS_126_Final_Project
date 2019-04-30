#pragma once

#include "ofMain.h"

//============================ Helpful Constants. ==============================
// Determines the percentage of the radius that the interpolation circle's
// radius is, the bigger it is the smaller the hole, but the uglier.
const int kBrushInterpolationSizeCoeff = 0.8;
// We divide the radius by this to determine the stepping size for the
// interval over which we draw interpolations.
const int kBrushInterpolationStepCoeff = 4;

enum class Brushes {
  PEN,
  TRIANGLE_BRUSH,
  BUBBLE_BRUSH,
  ERASER
};

//============================= Brushes. ===============================
void DrawWithPen(int thickness, ofColor color);
void DrawWithTriangles(int thickness, ofColor color);
void DrawWithBubbleBrush(int thickness, ofColor color);
void Eraser(int thickness, ofColor color);
void PreviewBrush(int thickness, ofColor color, Brushes active_brush,
  ofColor background_color);
