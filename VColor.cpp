/*    (c) 2011-2012 Jan Dlabal <dlabaljan gmail>                              */
/*                                                                            */
/*     This file is part of Genome Visualizer.                                */
/*                                                                            */
/*     Genome Visualizer is free software: you can redistribute it and/or     */
/*     modify it under the terms of the GNU General Public License as         */
/*     published by the Free Software Foundation, either version 3 of the     */
/*     License, or any later version.                                         */
/*                                                                            */
/*     Genome Visualizer is distributed in the hope that it will be useful,   */
/*     but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/*     GNU General Public License for more details.                           */
/*                                                                            */
/*     You should have received a copy of the GNU General Public License      */
/*     along with Genome Visualizer. If not, see                              */
/*     <http://www.gnu.org/licenses/>.                                        */


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "VColor.hpp"


VColor& VColor::operator*=(float ratio) {
    this->r *= ratio;
    this->g *= ratio;
    this->b *= ratio;
    return *this;
}


VColor VColor::operator*(float right) {
  VColor result(this->r * right, this->g * right, this->b * right);
  return result;
}


void VColor::setRGB(float r1, float g1, float b1) {
  this->r = r1;
  this->g = g1;
  this->b = b1;
}


char *VColor::html() {
  char *res = (char*)malloc(8);
  sprintf(res, "#%02X%02X%02X", int(floor(r * 255 + 0.5)), int(floor(g * 255 + 0.5)), int(floor(b * 255 + 0.5)));
  return res;
}


// sets the VColor from the HSV given. Hue/angle has to be in [0;360], saturation in [0,1], value in [0,1]
// The function converts the HSV representation to RGB (the internal VColor format).
// Algorithm written using the formula at http://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
void VColor::setHSV(float hue, float saturation, float value) {
  float hp = hue / 60.0;
  float c = value * saturation;
  float x = c * (1 - fabs(fmod(hp, 2) - 1));

  if (0 <= hp && hp < 1) {
    this->r = c; this->g = x; this->b = 0;
  } else if (1 <= hp && hp < 2) {
    this->r = x; this->g = c; this->b = 0;
  } else if (2 <= hp && hp < 3) {
    this->r = 0; this->g = c; this->b = x;
  } else if (3 <= hp && hp < 4) {
    this->r = 0; this->g = x; this->b = c;
  } else if (4 <= hp && hp < 5) {
    this->r = x; this->g = 0; this->b = c;
  } else if (5 <= hp && hp <= 6) {
    this->r = c; this->g = 0; this->b = x;
  } else {
    this->r = 0; this->g = 0; this->b = 0; // this should not be reached
  }

  float m = value - c;
  this->r += m;
  this->g += m;
  this->b += m;
}


VColor::VColor(float r1, float g1, float b1) {
  setRGB(r1, g1, b1);
}
