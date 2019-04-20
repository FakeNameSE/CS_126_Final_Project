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
  BUBBLE_BRUSH
};

//============================= Brushes. ===============================
void DrawWithPen(int thickness, ofColor color);
void DrawWithBubbleBrush(int thickness, ofColor color);