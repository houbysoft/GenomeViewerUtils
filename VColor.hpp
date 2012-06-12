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


#ifndef VCOLOR_HPP
#define VCOLOR_HPP

class VColor {
public:
  float r, g, b;

  /* Operators */
  VColor& operator*=(float ratio);
  VColor operator*(float right);

  void setRGB(float, float, float);
  void setHSV(float, float, float);
  char *html(); // returns a HTML-like representation of the color, for example #00FF00. The string is malloc()'d, the caller should free() it.

  VColor(float r1=0, float g1=0, float b1=0);

  ~VColor() {};
};

#endif
