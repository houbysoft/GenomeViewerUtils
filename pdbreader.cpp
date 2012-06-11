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


/* This file contains functions that convert PDB files to struct pdb_elements, which 
   are much easier to use programmatically.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "pdbreader.hpp"


struct pdb_element *nextPDBElement(FILE *f) {
  if (!f) return NULL;
  char line[LINE_LENGTH];
  if (!fgets(line, LINE_LENGTH, f)) return NULL;
  struct pdb_element *r = (struct pdb_element *)malloc(sizeof(struct pdb_element));
  char *lp = line;

  if (strstr(lp, "ATOM  ") != lp) { // invalid element
    free(r);
    return NULL;
  } else {
    lp += 6;
  }

  if (sscanf(lp, "%i", &r->id) != 1) { // atom number not present
    free(r);
    return NULL;
  } else {
    lp += 6;
  }

  r->name = lp[0];
  lp += 9;

  r->chainid = lp[0];
  lp += 1;

  if (sscanf(lp, "%f%f%f", &r->coords[0], &r->coords[1], &r->coords[2]) != 3) { // coordinates not present
    free(r);
    return NULL;
  }

  return r;
}


// fills out the struct pdb_element tdist field
void calculate_lengths(struct pdb_element_list *data) {
  char chain = data->e->chainid;
  float dist = 0;
  data->e->tdist = 0;
  while (data->next) {
    if (chain != data->e->chainid) {
      chain = data->e->chainid;
      data->e->tdist = dist = 0;
    }
    dist += pdb_el_distance(data->e, data->next->e);
    data->next->e->tdist = dist;
    data = data->next;
  }
}


// Compute a bounding cube for the points, and return its diagonal
double cube_diagonal(struct pdb_element_list *data) {
  double high[3] = {
    data->e->coords[0],
    data->e->coords[1],
    data->e->coords[2]
  };
  double low[3] = {
    data->e->coords[0],
    data->e->coords[1],
    data->e->coords[2]
  };

  while (data) {
    if (data->e->coords[0] < low[0])
      low[0] = data->e->coords[0];
    if (data->e->coords[1] < low[1])
      low[1] = data->e->coords[1];
    if (data->e->coords[2] < low[2])
      low[2] = data->e->coords[2];

    if (data->e->coords[0] > high[0])
      high[0] = data->e->coords[0];
    if (data->e->coords[1] > high[1])
      high[1] = data->e->coords[1];
    if (data->e->coords[2] > high[2])
      high[2] = data->e->coords[2];

    data = data->next;
  }

  return sqrt((high[0] - low[0])*(high[0] - low[0])+
	      (high[1] - low[1])*(high[1] - low[1])+
	      (high[2] - low[2])*(high[2] - low[2]));
}


// Rescale the data set to be practical to visualize; fit in a cube with a 100 long diagonal
void rescale(struct pdb_element_list *data, double rescaling_factor, double mx, double my, double mz) {
  printf("Rescaling and centering points... ");
  double factor = 0;
  if (rescaling_factor == 0) {
    double d = cube_diagonal(data);
    factor = 100.0 / d;
  } else {
    factor = rescaling_factor;
  }
  printf("factor : %f, ", factor);
  double move[3];
  if (mx == 0 && my == 0 && mz == 0) {
    move[0] = factor * data->e->coords[0];
    move[1] = factor * data->e->coords[1];
    move[2] = factor * data->e->coords[2];
  } else {
    move[0] = mx;
    move[1] = my;
    move[2] = mz;
  }
  printf("move = {%f, %f, %f}\n", move[0], move[1], move[2]);
  struct pdb_element_list *a = data;
  while (a) {
    a->e->coords[0] *= factor;
    a->e->coords[1] *= factor;
    a->e->coords[2] *= factor;
    a->e->coords[0] -= move[0];
    a->e->coords[1] -= move[1];
    a->e->coords[2] -= move[2];
    a = a->next;
  }
}


struct pdb_element_list *readPDBFile(char *fn, double rescaling_factor, double mx, double my, double mz) {
  FILE *f = fopen(fn, "r");
  if (!f) return NULL;
  struct pdb_element *e = nextPDBElement(f);
  struct pdb_element_list *data = (struct pdb_element_list *) malloc(sizeof(struct pdb_element_list));
  struct pdb_element_list *c = data;
  char lastchain = '*'; // dummy
  double lastcoords[3] = {
    e->coords[0], e->coords[1], e->coords[2]
  };
  c->next = c;

  while (e) {
    c = c->next;
    c->e = e;
    c->next = (struct pdb_element_list *)malloc(sizeof(struct pdb_element_list));
    c->next->next = NULL;
    e = nextPDBElement(f);

    // Drop duplicates
    while (e && lastchain == e->chainid && e->coords[0] == lastcoords[0] && e->coords[1] == lastcoords[1] && e->coords[2] == lastcoords[2]) {
      free(e);
      e = nextPDBElement(f);
    }
    if (e) {
      lastchain = e->chainid;
      lastcoords[0] = e->coords[0]; lastcoords[1] = e->coords[1]; lastcoords[2] = e->coords[2];
    }
  }

  free(c->next);
  c->next = NULL;
  fclose(f);

  rescale(data, rescaling_factor, mx, my, mz);
  calculate_lengths(data);

  return data;
}


// Reads in lengths from the length file (see spec in doc/LengthFormat.txt)
void readLengthFile(char *fn, std::vector<unsigned int> &lengths_bp) {
  FILE *fr = fopen(fn, "r");
  if (!fr) {
    printf("Could not read length file %s.\nExiting...\n", fn);
    exit(1);
  }
  char buf[32];
  unsigned int len;
  while (fgets(buf, 32, fr)) {
    if (sscanf(buf, "%i", &len) != 1) {
      fclose(fr);
      printf("Invalid length file %s (line %s).\nExiting...\n", fn, buf);
      exit(1);
    } else {
      lengths_bp.push_back(len);
    }
  }
  fclose(fr);
}
