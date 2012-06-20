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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include "annotationreader.hpp"


#define check_i() {if (i >= NAME_LENGTH - 1) {printf("Error; an element of the annotation file did not fit into a NAME_LENGTH array.\nPlease increase NAME_LENGTH in annotationreader.hpp to fix this.\n"); exit(1);}}


struct gene *nextGene(FILE *f) {
  if (!f) return NULL;
  char line[ANNO_LENGTH];
  if (!fgets(line, ANNO_LENGTH, f)) return NULL;
  struct gene *g = (struct gene *) malloc(sizeof(struct gene));
  char *lp = line;
  unsigned int i = 0;
  char number_buffer[NAME_LENGTH];

  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->SGID[i++] = lp[0];
    lp++;
  }
  check_i();
  g->SGID[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->feature_type[i++] = lp[0];
    lp++;
  }
  check_i();
  g->feature_type[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->feature_qualifier[i++] = lp[0];
    lp++;
  }
  check_i();
  g->feature_qualifier[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->feature_name[i++] = lp[0];
    lp++;
  }
  check_i();
  g->feature_name[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->std_name[i++] = lp[0];
    lp++;
  }
  check_i();
  g->std_name[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->alias[i++] = lp[0];
    lp++;
  }
  check_i();
  g->alias[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->parent_name[i++] = lp[0];
    lp++;
  }
  check_i();
  g->parent_name[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    g->SGID2[i++] = lp[0];
    lp++;
  }
  check_i();
  g->SGID2[i] = 0;
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    number_buffer[i++] = lp[0];
    lp++;
  }
  check_i();
  number_buffer[i] = 0;
  g->chromosome = atoi(number_buffer);
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    number_buffer[i++] = lp[0];
    lp++;
  }
  check_i();
  number_buffer[i] = 0;
  g->start = atoi(number_buffer);
  i = 0;

  lp++;
  while (lp[0]!='\t' && i < NAME_LENGTH - 1) {
    number_buffer[i++] = lp[0];
    lp++;
  }
  check_i();
  number_buffer[i] = 0;
  g->end = atoi(number_buffer);
  i = 0;

  lp++;
  if (lp[0] != '\t') {
    g->strand = lp[0];
    lp++;
  }

  lp++;
  unsigned int tabcount = 0;
  while (tabcount != 3) {
    if (lp[0] == '\t')
      tabcount++;
    lp++;
  }

  i = 0;
  while (lp[0]!='\n' && lp[0]!='\0' && i < DESC_LENGTH - 1) {
    g->description[i++] = lp[0];
    lp++;
  }
  g->description[i] = 0;

  return g;
}


// True if a is before b
bool annotationSort(struct gene a, struct gene b) {
  if (a.chromosome == 0) {
    return false;
  } else if (b.chromosome == 0) {
    return true;
  } else if (a.chromosome < b.chromosome) {
    return true;
  } else if (a.chromosome > b.chromosome) {
    return false;
  } else {
    if (a.start < b.start) {
      return true;
    } else {
      return false;
    }
  }
}


std::vector<struct gene> *readAnnotationFile(char *fn) {
  FILE *f = fopen(fn, "r");
  if (!f) return NULL;
  struct gene *g = nextGene(f);
  std::vector<struct gene> *data = new std::vector<struct gene>;

  while (g) {
    data->push_back(*g);
    free(g);
    g = nextGene(f);
  }

  fclose(f);

  std::sort(data->begin(), data->end(), annotationSort);

  return data;
}
