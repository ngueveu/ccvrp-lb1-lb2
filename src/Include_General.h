/* (C) Copyright 2008 Sandra Ulrich NGUEVEU. All rights reserved.
- OSI Certified Open Source Software
- This software is licensed under the Common Public License Version 1.0
- Last Update: 20081007 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
// #include <direct.h> SUN
//# include "glpk.h"


#ifndef MEMWATCH
#endif
#if !defined(MW_STDIO) && !defined(MEMWATCH_STDIO)
#endif
// #include "memwatch.h" SUN

#define infini 99999
//#define EPSILON 0.000001

#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define max(a,b)  (((a) > (b)) ? (a) : (b))

#define ROW_LENGTH 256
// Length of a row in a text file or of a file name

typedef struct
                {float Cap_max;
                    float *Demand, *Coord_X, *Coord_Y;
                double **Cost;
                int Nb_clients, Nb_arcs, Min_Nb_routes, NbRouteMax;
                int *Type_of_node, *Node_eq, *Arc_num_start, *Arc_num_end, *Edge_rank_start, *Edge_rank_end;
                int **Num_of_Arc;
                }
                sG;


typedef struct
                {char Source[256], Param[256];
                }
                sF;


typedef struct
                {
                int TYPE_FORMAT, PLUSNBROUTES, PRINT;
                }
                sP;

