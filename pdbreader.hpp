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


#ifndef PDBREADER_HPP
#define PDBREADER_HPP

#include <math.h> // for sqrt

#define chainid_to_chromosome(cid) ((unsigned int)(cid - 64)) // ASCII value of 'A', which represents the first chromosome, is 65, thus 65-64 = 1 = chromosome number

#define LINE_LENGTH 128
#define pdb_el_distance(a,b) sqrt(pow(a->coords[0] - b->coords[0], 2) + pow(a->coords[1] - b->coords[1], 2) + pow(a->coords[2] - b->coords[2], 2))

struct pdb_element {
  int id;
  char name;
  char chainid;
  float coords[3];
  float tdist; // total distance from beginning of chromosome, calculated from coords across all elements of one chromosome
};

struct pdb_element_list {
  struct pdb_element *e;
  struct pdb_element_list *next;
};

extern struct pdb_element *nextPDBElement(FILE *f);

// reads in the specified PDB file. rescaling_factor, mx, my, mz are optional; if not specified, the model will be scaled automatically
extern struct pdb_element_list *readPDBFile(char *fn, double rescaling_factor, double mx, double my, double mz);

extern void readLengthFile(char *fn, std::vector<unsigned int> &lengths_bp);

#endif
