/* (C) Copyright 2008 Sandra Ulrich NGUEVEU. All rights reserved.
- OSI Certified Open Source Software
- This software is licensed under the Common Public License Version 1.0
- Last Update: 20081007 */

/* Application created by SUN to solve CCVRP problems using the memetic algorithm
described in the article "A memetic Algorithm for the Cumulative Vehicle Routing Problem"
presented at the EUME conference */

/*
HISTORIQUE DES MODIFS

20110412
 - Rappel important, l'instance VRPNC5 a besoin de 1 véhicule de plus que "somme des d_i / Q" !!! En effet il lui faut au min 17 véhicules
 alors que "somme des d_i / Q" donne 16 !!! Cela revient à mettre le paramètre "NBER_OF_ROUTES_MORE_THAN_Rbound" à 1 (au lieu de 0).
*/



#include "Include_CCVRP_Procedures_Main.h"
#include "Include_CCVRP_LowerBounds.h"

//#include "memwatch.h"


int Create_Load_Graph_data (int argc, char *argv[], sG *pGraph, sP *pParams, sF *pFiles)
{
    int Feasibility = -1;
    
    Load_Files_Params (argc, argv, pParams, pFiles);

    Load_Graph (*pFiles, pGraph, *pParams);

    Feasibility = Check_pb_feasibility (pGraph, (*pParams).PLUSNBROUTES);

    if (Feasibility == 1) {
        Rank_Arcs_per_Cost ((*pGraph).Cost, (*pGraph).Arc_num_start, (*pGraph).Arc_num_end, (*pGraph).Num_of_Arc, (*pGraph).Nb_clients, (*pFiles), (*pParams).PRINT);
    }
    return Feasibility;
}



int main (int argc, char *argv[])
{
    sG Graph;
    sF Files;
    sP Params;
    int feasible;

    feasible = Create_Load_Graph_data (argc, argv, &Graph, &Params, &Files);

    if(feasible == 1) {
        LowerBounds (Graph, Files);
    }

    Graph_Destruction (&Graph);
}
