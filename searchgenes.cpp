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


#include "searchgenes.h"


std::vector<struct gene> *Visualizer::searchGenes(std::vector<struct gene> *genes, char *q, unsigned int chr, bool sgid, bool ft_name, bool ft_qual, bool std_name, bool alias, bool sgid2, bool desc) {
    if (!genes)
        return NULL;
    
    std::vector<struct gene> *res = new std::vector<struct gene>;
    unsigned int found = 0;
    
    for (std::vector<struct gene>::iterator it = genes->begin(); it != genes->end(); ++it) {
        if ((sgid && strcasestr((*it).SGID, q)) || (ft_name && strcasestr((*it).feature_name, q)) || (ft_qual && strcasestr((*it).feature_qualifier, q)) || (std_name && strcasestr((*it).std_name, q)) || (alias && strcasestr((*it).alias, q)) || (sgid2 && strcasestr((*it).SGID2, q)) || (desc && strcasestr((*it).description, q))) {
            if (chr == 0 || (chr != 0 && chr == it->chromosome)) {
                res->push_back(*it);
                found++;
            }
            if (found >= SEARCH_GENES_LIMIT) {
                return res;
            }
        }
    }
    
    return res;
}
