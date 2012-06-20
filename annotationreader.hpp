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


#ifndef ANNOTATIONREADER_HPP
#define ANNOTATIONREADER_HPP

#include <vector>

#define NAME_LENGTH 128
#define DESC_LENGTH 512
#define ANNO_LENGTH 1024

#define disp_gene_info(g) {printf("%s || %s || %s || %s || %s || %s || %s || %s || CHROMOSOME : %i || START : %i || END : %i || %c || %s\n", g->SGID, g->feature_type, g->feature_qualifier, g->feature_name, g->std_name, g->alias, g->parent_name, g->SGID2, g->chromosome, g->start, g->end, g->strand, g->description);}

struct gene {
  char SGID[NAME_LENGTH];
  char feature_type[NAME_LENGTH];
  char feature_qualifier[NAME_LENGTH];
  char feature_name[NAME_LENGTH];
  char std_name[NAME_LENGTH];
  char alias[NAME_LENGTH];
  char parent_name[NAME_LENGTH];
  char SGID2[NAME_LENGTH];
  unsigned int chromosome, start, end;
  char strand;
  char description[DESC_LENGTH];
};


extern std::vector<struct gene> *readAnnotationFile(char *fn);

#endif
