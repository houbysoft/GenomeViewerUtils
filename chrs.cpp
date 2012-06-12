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


#include "chrs.hpp"


unsigned int chrsCount(struct pdb_element_list *data, std::vector<float> &lengths) {
  struct pdb_element_list *cr = data;
  char chain = cr->e->chainid;
  while (cr->next) {
    if (chain != cr->next->e->chainid) {
      lengths.push_back(cr->e->tdist);
      chain = cr->next->e->chainid;
    }
    cr = cr->next;
  }
  lengths.push_back(cr->e->tdist);
  return lengths.size();
}


void createColors(std::vector<VColor> &colors, unsigned int chromosome_count) {
  colors.clear();
  VColor current;
  float hue_step = 360.0 / float(chromosome_count);
  float cur_hue = 0;
  for (unsigned int i=0; i < chromosome_count; i++) {
    current.setHSV(cur_hue, 1.0, 1.0);
    colors.push_back(current);
    cur_hue += hue_step;
  }
}

