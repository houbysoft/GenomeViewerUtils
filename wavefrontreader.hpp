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


#ifndef WAVEFRONTREADER_HPP
#define WAVEFRONTREADER_HPP


#include <vector>


typedef struct {
    int v1, v2, v3;
    int vn1, vn2, vn3;
} WFFace;


typedef struct {
    float x, y, z;
} WFVector;


class WFReader {
private:
    std::vector<WFVector> vertices;
    std::vector<WFVector> normals;
    std::vector<WFFace> faces;
    void parseLine(char *line);
    
    void parseVertex(char *line);
    void parseNormal(char *line);
    void parseFace(char *line);

public:
    WFReader(char *filename);
    ~WFReader() {};
    void draw();
};

#endif
