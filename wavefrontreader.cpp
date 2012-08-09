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


#include <fstream>
#include <iostream>
#include "wavefrontreader.hpp"


WFReader::WFReader(char *filename) {
    std::fstream objFile;
    objFile.open(filename);
    
    if(objFile.is_open())
    {
        char line[255];
        
        // Parse object file line by line
        while(objFile.good())
        {
            objFile.getline(line, 255);
            parseLine(line);
        }
        
        objFile.close();
    }
    else
    {
        std::cout << "Could not open WFObject file '" << filename << "'\n";
        throw;
    }
}


void WFReader::parseLine(char *line) {
    if(!strlen(line)) {
        return;
    }

    if(line[0] == 'v' && isspace(line[1])) {
        parseVertex(line);
    } else if(line[0] == 'v' && line[1] == 'n' && isspace(line[2])) {
        parseNormal(line);
    } else if(line[0] == 'f' && isspace(line[1])) {
        parseFace(line);
    }
}


void WFReader::parseVertex(char *line) {
    vertices.push_back(WFVector());
    sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);
}


void WFReader::parseNormal(char *line) {
    normals.push_back(WFVector());
    sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z);
}


void WFReader::parseFace(char *line) {
    faces.push_back(WFFace());
    int fill = 0;
    if(sscanf(line, "f %d//%d %d//%d %d//%d", &faces.back().v1,
              &faces.back().vn1,
              &faces.back().v2,
              &faces.back().vn2,
              &faces.back().v3,
              &faces.back().vn3) <= 1) {
        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces.back().v1,
               &fill,
               &faces.back().vn1,
               &faces.back().v2,
               &fill,
               &faces.back().vn2,
               &faces.back().v3,
               &fill,
               &faces.back().vn3);
    }
}
