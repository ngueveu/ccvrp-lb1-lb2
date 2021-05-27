/* (C) Copyright 2008 Sandra Ulrich NGUEVEU. All rights reserved.
- OSI Certified Open Source Software
- This software is licensed under the Common Public License Version 1.0
- Last Update: 20081007 */



#include "Include_CCVRP_Procedures_Main.h"


void Print_LBs (sF Files, int maxNbroutes, double LB1, double LB2)
{
struct tm *newtime;
time_t aclock;

time (&aclock); /* Get time in seconds */
newtime = localtime (&aclock); /* Convert time to struct 'tm form' */
    printf ("\n %s with up to %d routes--> LB1 = %f; LB2 = %f : %s", Files.Source, maxNbroutes, LB1, LB2, asctime (newtime));
}


double LowerBound1 (sG Graph/*, sF Files*/)
{
int arc, done;
double LB1;

arc = 0; done = 0; LB1 = 0;
while ( (arc < Graph.Nb_arcs) && (done < Graph.Nb_clients) )
        {
        if (Graph.Arc_num_start[arc] == 0)
                {
                LB1 = LB1 + Graph.Cost[ Graph.Arc_num_start[arc] + Graph.Nb_clients - 1 ][ Graph.Arc_num_end[arc] + Graph.Nb_clients - 1 ];
                done = done + 1;
                }
        arc = arc + 1;
        }

return LB1;
//Print_LB (Files, LB1, 1);

}



double LowerBound2 (sG Graph/*, sF Files*/)
{
int i, R, minRn, maxRn, nbRmaxRn, level, arc, id, io;
int * CoeftoDepot, *CoeftoOther;
double LB2;

R = Graph.NbRouteMax;
minRn = Graph.Nb_clients / R;
if ( (float) Graph.Nb_clients / (float) R - minRn <= 0.000001)
        {
        maxRn = minRn;
        }
else
        {
        maxRn = minRn + 1;
        }
nbRmaxRn = Graph.Nb_clients - minRn * R;

Alloc_mem_int (&(CoeftoDepot), R, "CoeftoDepot");
Alloc_mem_int (&(CoeftoOther), Graph.Nb_clients - R, "CoeftoOther");

for (i = 0; i < nbRmaxRn; i ++)
        {
        CoeftoDepot[i] = maxRn;
        }
for (i = nbRmaxRn; i < R; i ++)
        {
        CoeftoDepot[i] = minRn;
        }

level = 1;
for (i = 0; i < Graph.Nb_clients - R; i ++)
        {
        if (i%R < nbRmaxRn)
                {
                CoeftoOther[i] = maxRn - level;
                }
        else
                {
                CoeftoOther[i] = minRn - level;
                }
        if (i%R == R-1)
                {
                level = level + 1;
                }
        }

id = 0; io = 0; arc = 0;LB2 = 0;
while ( (arc < Graph.Nb_arcs) && ( (id < R) || (io < Graph.Nb_clients-R) ) )
        {
        if ( (Graph.Arc_num_start[arc] == 0) && (id < R) )
                {
                LB2 = LB2 + CoeftoDepot[id] * Graph.Cost[ Graph.Arc_num_start[arc] + Graph.Nb_clients - 1 ][ Graph.Arc_num_end[arc] + Graph.Nb_clients - 1 ];
                id = id + 1;
                }
        if ( (Graph.Arc_num_start[arc] != 0) && (io < Graph.Nb_clients - R) )
                {
                LB2 = LB2 + CoeftoOther[io] * Graph.Cost[ Graph.Arc_num_start[arc] + Graph.Nb_clients - 1 ][ Graph.Arc_num_end[arc] + Graph.Nb_clients - 1 ];
                io = io + 1;
                }
        arc = arc + 1;
        }

if ( (id != R) || (io != Graph.Nb_clients-R) )
        {
        printf ("Error in computation of LB2!!!");
        systempause(getchar());
        }

    free(CoeftoDepot);
    free(CoeftoOther);
    
    
return LB2;
//Print_LB (Files, LB2, 2);

}





void LowerBounds (sG Graph, sF Files)
{
double LB1, LB2;

LB1 = LowerBound1 (Graph);
LB2 = LowerBound2 (Graph);

Print_LBs (Files, Graph.NbRouteMax, LB1, LB2);
}
