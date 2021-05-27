/* (C) Copyright 2008 Sandra Ulrich NGUEVEU. All rights reserved.
- OSI Certified Open Source Software
- This software is licensed under the Common Public License Version 1.0
- Last Update: 20081007 */


#include "Include_General.h"
// #include "memwatch.h" SUN

void Tclock_ON(clock_t * Start_T);

void Tclock_OFF(clock_t Start_T, clock_t * End_T, double *Time_tot/*, double *Time_current*/);

void Alloc_mem_int (int **pPointer, int Size, char text[100]);

void Alloc_mem_float (float **pPointer, int Size, char text[100]);

void Alloc_mem_double (double **pPointer, int Size, char text[100]);

void Alloc_mem_int_star (int ***pPointer, int Size, char text[100]);

void Alloc_mem_float_star (float ***pPointer, int Size, char text[100]);

void Alloc_mem_double_star (double ***pPointer, int Size, char text[100]);

long FindString (FILE* File, char* String);

void FindParam_int (FILE * file, char * text, int * parameter, char *type_file);

void FindParam_float (FILE * file, char * text, float * parameter, char *type_file);

void systempause(char input);

void PRINT_PARAMS_INIT (sP Params, sF Files);

void Load_Files_Params (int argc, char *argv[], sP *pParams, sF *pFiles);

void Graph_Creation (sG *pGraph);

void Graph_Destruction (sG *pGraph);

void Check_error_loading_data (int t, int value, char *data_type);

void PRINT_DATA_LOADED (sG Graph, sF Files);

void PRINT_GRAPH_DIST (sG Graph, sF Files);

void Graph_distance_computing (sG Graph, sP Params, sF Files);

void Graph_data_Loading_3 (sG Graph, FILE *Filed);

void Load_Graph_3 (sG *pGraph, FILE * file);

void Graph_data_Loading_2 (sG Graph, FILE *file, sF Files, sP Params);

void Load_Graph_2 (sG *pGraph, FILE * file, sF Files, sP Params);

void Graph_data_Loading_1 (sG Graph, FILE *file, sF Files, sP Params);

void Load_Graph_1 (sG *pGraph, FILE * file, sF Files, sP Params);

void Load_Graph (sF Files, sG *pGraph, sP Params);

int Check_pb_feasibility (sG *pGraph, int PlusNbRoutes);

void PRINT_ARCS_RANKED (double **Cost, int * Start, int * End, int ** Num_of_Arc, int Nb_clients, sF Files);

void Rank_Arcs_per_Cost (double **Cost, int * Start, int * End, int ** Num_of_Arc, int Nb_clients, sF Files, int print);
