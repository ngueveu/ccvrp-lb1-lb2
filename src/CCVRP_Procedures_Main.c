/* (C) Copyright 2008 Sandra Ulrich NGUEVEU. All rights reserved.
- OSI Certified Open Source Software
- This software is licensed under the Common Public License Version 1.0
- Last Update: 20081007 */


#include "Include_CCVRP_Procedures_Main.h"

//#include "memwatch.h"

////////////////////////////////////
//        Tclock management       //
////////////////////////////////////


void Tclock_ON(clock_t * Start_T)
{
*Start_T = clock();
}


void Tclock_OFF(clock_t Start_T, clock_t * End_T, double *Time_tot/*, double *Time_current*/)
{
*End_T = clock();
*Time_tot = *Time_tot + ((double)(*End_T - Start_T))/CLOCKS_PER_SEC;
//*Time_current = *Time_current + ((double)(*End_T - Start_T))/CLOCKS_PER_SEC;
}


void Alloc_mem_int (int **pPointer, int Size, char text[100])
{
(*pPointer) = (int *) calloc (Size, sizeof(int));
if ((*pPointer) == NULL)
        {
        printf ("Error when allocating memory for %s", text);
        systempause(getchar());
        }
}

void Alloc_mem_float (float **pPointer, int Size, char text[100])
{
(*pPointer) = (float *) calloc (Size, sizeof(float));
if ((*pPointer) == NULL)
        {
        printf ("Error when allocating memory for %s", text);
        systempause(getchar());
        }
}

void Alloc_mem_double (double **pPointer, int Size, char text[100])
{
(*pPointer) = (double *) calloc (Size, sizeof(double));
if ((*pPointer) == NULL)
        {
        printf ("Error when allocating memory for %s", text);
        systempause(getchar());
        }
}

void Alloc_mem_int_star (int ***pPointer, int Size, char text[100])
{
(*pPointer) = (int **) calloc (Size, sizeof(int*));
if ((*pPointer) == NULL)
        {
        printf ("Error when allocating memory for %s", text);
        systempause(getchar());
        }
}

void Alloc_mem_float_star (float ***pPointer, int Size, char text[100])
{
(*pPointer) = (float **) calloc (Size, sizeof(float*));
if ((*pPointer) == NULL)
        {
        printf ("Error when allocating memory for %s", text);
        systempause(getchar());
        }
}

void Alloc_mem_double_star (double ***pPointer, int Size, char text[100])
{
(*pPointer) = (double **) calloc (Size, sizeof(double*));
if ((*pPointer) == NULL)
        {
        printf ("Error when allocating memory for %s", text);
        systempause(getchar());
        }
}

void Check_fscanf_return(long out){
    if(out == EOF) {
        printf("Error, fscan returned EOF");
        systempause(getchar());
    }
}

void fgets_and_check( char * str, int num, FILE * stream ){
    if(fgets (str, num, stream ) == NULL){
        printf("\nError when applying fgets\n");
        systempause(getchar());
    }
}


long FindString (FILE* File, char* String)
{
long n;
char s2[ROW_LENGTH];

rewind(File);
do n = fscanf(File,"%s",s2);
while ((n != EOF) && (strcmp(String,s2) != 0));
return ((n == EOF) ? 0 : 1);
}


void FindParam_int (FILE * file, char * text, int * parameter, char *type_file)
{
    long out;
if (FindString (file, text) == 1)
        {
        out=fscanf (file, "%d", parameter);
            Check_fscanf_return(out);
        }
else
        {
        printf ("\nError, impossible to find key word %s in the %s file\n", text, type_file);
        systempause(getchar());
        }
}


void FindParam_float (FILE * file, char * text, float * parameter, char *type_file)
{
    long out;
if (FindString (file, text) == 1)
        {
        out = fscanf (file, "%f", parameter);
            Check_fscanf_return(out);
        }
else
        {
        printf ("\nError, impossible to find key word %s in the %s file\n", text, type_file);
        systempause(getchar());
        }
}

void systempause(char input){
    while(input != '\n'){
        input = getchar();
    }
}

void PRINT_PARAMS_INIT (sP Params, sF Files)
{
printf ("\n Source File : %s", Files.Source);
printf (" - Type_file_format = %d, Print = %d, NbRoutes_morethan_min = %d", Params.TYPE_FORMAT, Params.PRINT, Params.PLUSNBROUTES);
}


void Load_Files_Params (int argc, char *argv[], sP *pParams, sF *pFiles)
{
FILE *file;
if (argc >= 3)
        {
        strcpy(pFiles->Source, argv[1]);
        strcpy(pFiles->Param, argv[2]);
        }
else
        {
        printf ("\nError, not enough input arguments given, need two files names: a data source file name and a parameter file name");
        systempause(getchar());
        }

file = fopen((*pFiles).Param, "r");
if (file == NULL)
        {
        printf ("\n Erreur when opening file %s", (*pFiles).Param);
        systempause(getchar());
        }
else
        {
        FindParam_int (file, "TYPE_FORMAT_SOURCE_FILE", &pParams->TYPE_FORMAT, "parameters");
        FindParam_int (file, "NBER_OF_ROUTES_MORE_THAN_Rbound", &pParams->PLUSNBROUTES, "parameters");
        FindParam_int (file, "IMPRIMER_PROGRES", &pParams->PRINT, "parameters");

         fclose (file);
        }
if (pParams->PRINT > 0)
        {
        PRINT_PARAMS_INIT (*pParams, *pFiles);
        }
}


void Graph_Creation (sG *pGraph)
{
int tmp, i, j;

(*pGraph).Nb_arcs = ((*pGraph).Nb_clients * ((*pGraph).Nb_clients+1)) / 2;
Alloc_mem_float (&((*pGraph).Demand), (*pGraph).Nb_clients * 3, "Graph_Demand");
Alloc_mem_float (&((*pGraph).Coord_X), (*pGraph).Nb_clients * 3, "Graph_Coord_X");
Alloc_mem_float (&((*pGraph).Coord_Y), (*pGraph).Nb_clients * 3, "Graph_Coord_Y");
Alloc_mem_double_star (&((*pGraph).Cost), (*pGraph).Nb_clients * 3, "Graph_Cost");
Alloc_mem_int_star (&((*pGraph).Num_of_Arc), (*pGraph).Nb_clients + 1, "Graph_Num_of_Arc");
for (i = 0; i < (*pGraph).Nb_clients * 3; i ++)
        {
        Alloc_mem_double (&((*pGraph).Cost[i]), (*pGraph).Nb_clients * 3, "Graph_Cost");
        }
for (i = 0; i < (*pGraph).Nb_clients + 1; i ++)
        {
        Alloc_mem_int (&((*pGraph).Num_of_Arc[i]), (*pGraph).Nb_clients + 1, "Graph_Num_of_Arc");
        }
Alloc_mem_int (&((*pGraph).Arc_num_start), (*pGraph).Nb_arcs, "Graph_Arc_num_start");
Alloc_mem_int (&((*pGraph).Arc_num_end), (*pGraph).Nb_arcs, "Graph_Arc_num_end");
Alloc_mem_int (&((*pGraph).Edge_rank_start), (*pGraph).Nb_clients * 3, "Graph_Edge_rank_start");
Alloc_mem_int (&((*pGraph).Edge_rank_end), (*pGraph).Nb_clients * 3, "Graph_Edge_rank_end");
Alloc_mem_int (&((*pGraph).Type_of_node), (*pGraph).Nb_clients * 3, "Graph_Type_of_node");
Alloc_mem_int (&((*pGraph).Node_eq), (*pGraph).Nb_clients * 3, "Graph_Node_equivalent");

for (i = (*pGraph).Nb_clients; i < 2 * (*pGraph).Nb_clients; i ++)
        {
        (*pGraph).Type_of_node[i] = 1;
        (*pGraph).Node_eq[i] = i - (*pGraph).Nb_clients + 1;
        }

tmp = 0; i = 0; j = 1;
while ( tmp < (*pGraph).Nb_arcs )
        {
        j = i + 1;
        while (j < (*pGraph).Nb_clients + 1)
                {
                (*pGraph).Arc_num_start[tmp] = i;
                (*pGraph).Arc_num_end[tmp] = j;
                (*pGraph).Num_of_Arc[i][j] = tmp;
                (*pGraph).Num_of_Arc[j][i] = tmp;
                tmp = tmp + 1;
                j = j + 1;
                }
        i = i+1;
        }
}



void Graph_Destruction (sG *pGraph)
{
int i;

for (i = 0; i < (*pGraph).Nb_clients * 3; i ++)
        {
        free ((*pGraph).Cost[i]);
        }
for (i = 0; i < (*pGraph).Nb_clients + 1; i ++)
        {
        free ((*pGraph).Num_of_Arc[i]);
        }
free ((*pGraph).Arc_num_start);
free ((*pGraph).Arc_num_end);
free ((*pGraph).Edge_rank_start);
free ((*pGraph).Edge_rank_end);
free ((*pGraph).Type_of_node);
free ((*pGraph).Node_eq);
free ((*pGraph).Demand);
free ((*pGraph).Coord_X);
free ((*pGraph).Coord_Y);
free ((*pGraph).Cost);
free ((*pGraph).Num_of_Arc);
}



void Check_error_loading_data (int t, int value, char *data_type)
{
if (t != value)
        {
        printf("\nError when loading %s data of node %d from source file for the graph\n", data_type, t);
        systempause(getchar());
        }
}



void PRINT_DATA_LOADED (sG Graph, sF Files)
{
int i, j;
FILE *filed;
char name[100];

strcpy (name, Files.Source);
strcat (name, ".data_loaded");
filed = fopen (name, "a+");

if (filed == NULL)
        {
        printf ("\nError when opening file %s for writing CW cost data\n", name);
        systempause(getchar());
        }
else
        {
        fprintf (filed, "\n\n Source file : %s", Files.Source);
        fprintf (filed, "\nNode\tCoord_X\tCoord_Y\tDemand");
        for (i = 0; i < Graph.Nb_clients * 3; i ++)
                {
                fprintf (filed, "\n %d : %f - %f (%f)", i, Graph.Coord_X[i], Graph.Coord_Y[i], Graph.Demand[i]);
                }
			
			fprintf(filed, "\n\ndistancier\n");
			for (i = (0+Graph.Nb_clients-1); i <= (Graph.Nb_clients+Graph.Nb_clients-1); i++)
			{
				for (j = (0+Graph.Nb_clients-1); j<= (Graph.Nb_clients+Graph.Nb_clients-1); j++) 
				{
					fprintf(filed, "%.3lf ", Graph.Cost[i][j]);
				}
				fprintf(filed, "\n");
			}
			
        fclose (filed);
        }
}




void PRINT_GRAPH_DIST (sG Graph, sF Files)
{
int i, j;
FILE * file;
char name[100];

strcpy (name, Files.Source);
strcat (name, ".cost");
file = fopen (name, "a+");

if (file == NULL)
        {
        printf ("\nError when opening file %s for writing cost data\n", name);
        systempause(getchar());
        }
else
        {
        fprintf (file,"\n\n %s", Files.Source);
        fprintf (file, "\nNodes of indices < %d and >= %d are depots", Graph.Nb_clients, 2 * Graph.Nb_clients);
        fprintf (file, "\nStart - End : Edge_cost");
        for (i = 0; i < 3 * Graph.Nb_clients; i ++)
                {
                for (j = 0; j < 3 * Graph.Nb_clients; j ++)
                        {
                        fprintf (file, "\n%d - %d : %f", i, j, Graph.Cost[i][j]);
                        }
                }
        fclose (file);
        }
}




void Graph_distance_computing (sG Graph, sP Params, sF Files)
{
int i, j;
float Tmp;

if (Params.TYPE_FORMAT == 1)
        {
        for (i = 0; i < 3 * Graph.Nb_clients; i ++)
                {
                for (j = 0; j < 3 * Graph.Nb_clients; j ++)
                        {
                        Graph.Cost[i][j] = (int) sqrt(pow (Graph.Coord_X[i] - Graph.Coord_X[j], 2) + pow (Graph.Coord_Y[i] - Graph.Coord_Y[j], 2));
                        Tmp = sqrt(pow (Graph.Coord_X[i] - Graph.Coord_X[j], 2) + pow (Graph.Coord_Y[i] - Graph.Coord_Y[j], 2));
                        if (Graph.Cost[i][j] + 0.5 <= Tmp)
                                {
                                Graph.Cost[i][j] = Graph.Cost[i][j] + 1;
                                }
                        }
                }
        }
if (Params.TYPE_FORMAT == 2)
        {
        for (i = 0; i < 3 * Graph.Nb_clients; i ++)
                {
                for (j = 0; j < 3 * Graph.Nb_clients; j ++)
                        {
                        Graph.Cost[i][j] = sqrt(pow (Graph.Coord_X[i] - Graph.Coord_X[j], 2) + pow (Graph.Coord_Y[i] - Graph.Coord_Y[j], 2));
                        }
                }
        }

if (Params.PRINT > 0)
        {
        PRINT_GRAPH_DIST (Graph, Files);
        }
}





void Graph_data_Loading_3 (sG Graph, FILE *Filed)
{
int i, j;
float c;
    long out;
char text[100];
    fgets_and_check(text, 100, Filed);
// should get line 'NODE_COORD_SECTION'
for (i = Graph.Nb_clients - 1; i < 2*Graph.Nb_clients; i ++)
        {
        for (j = Graph.Nb_clients - 1; j <= i; j ++)
                {
                out = fscanf (Filed, "%f", &c);
                    Check_fscanf_return(out);
                Graph.Cost[i][j] = c;
                Graph.Cost[j][i] = c;
                }
        }
for (j = Graph.Nb_clients; j <= 2*Graph.Nb_clients; j ++)
        {
        for (i = 0; i < Graph.Nb_clients; i ++)
                {
                Graph.Cost[i][j] = Graph.Cost[Graph.Nb_clients-1][j];
                Graph.Cost[j][i] = Graph.Cost[Graph.Nb_clients-1][j];
                }
        for (i = 2*Graph.Nb_clients; i < 3*Graph.Nb_clients; i ++)
                {
                Graph.Cost[i][j] = Graph.Cost[Graph.Nb_clients-1][j];
                Graph.Cost[j][i] = Graph.Cost[Graph.Nb_clients-1][j];
                }
        }
}



void Load_Graph_3 (sG *pGraph, FILE * file)
{
    int i; char text[100]; long out;
fgets_and_check(text, 100, file);
fgets_and_check(text, 100, file);
fgets_and_check(text, 100, file);
fgets_and_check(text, 12, file);
out = fscanf(file,"%d\n", &i);
    Check_fscanf_return(out);
(*pGraph).Nb_clients = i - 1;
fgets_and_check(text, 100, file);
fgets_and_check(text, 11, file);
out = fscanf(file,"%d\n", &i);
    Check_fscanf_return(out);
(*pGraph).Cap_max = i;

Graph_Creation (pGraph);
Graph_data_Loading_3 (*pGraph, file);
}




void Graph_data_Loading_2 (sG Graph, FILE *file, sF Files, sP Params)
{
int k;
float i, j, d;
    long out;
char text[100];
fgets_and_check(text, 100, file);
// should get the first line
out = fscanf(file,"%f %f\n",&i, &j);
    Check_fscanf_return(out);
for (k = 0; k < Graph.Nb_clients; k ++)
        {
        Graph.Coord_X[k] = i;
        Graph.Coord_Y[k] = j;
        Graph.Demand[k] = 0;
        }
for (k = Graph.Nb_clients; k < 2 * Graph.Nb_clients; k ++)
        {
        out = fscanf(file,"%f %f %f\n",&i, &j, &d);
            Check_fscanf_return(out);
        Graph.Coord_X[k] = i;
        Graph.Coord_Y[k] = j;
        Graph.Demand[k] = d;
        }
for (k = 2 * Graph.Nb_clients; k < 3 * Graph.Nb_clients; k ++)
        {
        Graph.Coord_X[k] = Graph.Coord_X[0];
        Graph.Coord_Y[k] = Graph.Coord_Y[0];
        Graph.Demand[k] = 0;
        }
if (Params.PRINT > 0)
        {
        PRINT_DATA_LOADED (Graph, Files);
        }
}



void Load_Graph_2 (sG *pGraph, FILE * file, sF Files, sP Params)
{
int i, j;
    long out;

out = fscanf(file,"%d %d\n", &i, &j);
    Check_fscanf_return(out);
(*pGraph).Nb_clients = i;
(*pGraph).Cap_max = j;
Graph_Creation (pGraph);
Graph_data_Loading_2 (*pGraph, file, Files, Params);
}



void Graph_data_Loading_1 (sG Graph, FILE *file, sF Files, sP Params)
{
int t, k;
float i, j;
    long out;
char text[100];

fgets_and_check(text, 100, file);
// should get line 'NODE_COORD_SECTION'
out = fscanf(file,"%d %f %f\n",&t, &i, &j);
    Check_fscanf_return(out);
for (k = 0; k < Graph.Nb_clients; k ++)
        {
        Graph.Coord_X[k] = i;
        Graph.Coord_Y[k] = j;
        Check_error_loading_data (t, 1, "coordinate");
        }
for (k = Graph.Nb_clients; k < 2 * Graph.Nb_clients; k ++)
        {
        out = fscanf(file,"%d %f %f\n",&t, &i, &j);
            Check_fscanf_return(out);
        Graph.Coord_X[k] = i;
        Graph.Coord_Y[k] = j;
        Check_error_loading_data (t, k - Graph.Nb_clients + 2, "coordinate");
        }
for (k = 2 * Graph.Nb_clients; k < 3 * Graph.Nb_clients; k ++)
        {
        Graph.Coord_X[k] = Graph.Coord_X[0];
        Graph.Coord_Y[k] = Graph.Coord_Y[0];
        }

fgets_and_check(text, 100, file);
// should get line 'DEMAND SECTION'
out = fscanf(file,"%d %f\n",&t, &i);
    Check_fscanf_return(out);
for (k = 0; k < Graph.Nb_clients; k ++)
        {
        Graph.Demand[k] = i;
        Check_error_loading_data (t, 1, "demand");
        }
for (k = Graph.Nb_clients; k < 2 * Graph.Nb_clients; k ++)
        {
        out = fscanf(file,"%d %f\n",&t, &i);
            Check_fscanf_return(out);
        Graph.Demand[k] = i;
        Check_error_loading_data (t, k - Graph.Nb_clients + 2, "demand");
        }
for (k = 2 * Graph.Nb_clients; k < 3 * Graph.Nb_clients; k ++)
        {
        Graph.Demand[k] = Graph.Demand[0];
        }

if (Params.PRINT > 0)
        {
        PRINT_DATA_LOADED (Graph, Files);
        }

}



void Load_Graph_1 (sG *pGraph, FILE * file, sF Files, sP Params)
{
    int i; char text[100];long out;
fgets_and_check(text, 100, file);
fgets_and_check(text, 100, file);
fgets_and_check(text, 100, file);
fgets_and_check(text, 12, file);
out = fscanf(file,"%d\n", &i);
    Check_fscanf_return(out);
(*pGraph).Nb_clients = i - 1;
fgets_and_check(text, 100, file);
fgets_and_check(text, 11, file);
out = fscanf(file,"%d\n", &i);
    Check_fscanf_return(out);
(*pGraph).Cap_max = i;

Graph_Creation (pGraph);
Graph_data_Loading_1 (*pGraph, file, Files, Params);
}


void Load_Graph (sF Files, sG *pGraph, sP Params)
{
FILE *file;

file = fopen (Files.Source, "r");
if (file == NULL)
        {
        printf ("\nError when opening file %s for loading data\n", Files.Source);
        systempause(getchar());
        }
else
        {
        if (Params.TYPE_FORMAT == 1)
                {
                Load_Graph_1 (pGraph, file, Files, Params);
                }
        if (Params.TYPE_FORMAT == 2)
                {
                Load_Graph_2 (pGraph, file, Files, Params);
                }
        if (Params.TYPE_FORMAT == 3)
                {
                Load_Graph_3 (pGraph, file);
                }
        fclose (file);
        }
if (Params.TYPE_FORMAT <= 2)
        {
        Graph_distance_computing (*pGraph, Params, Files);
        }
	
	//PRINT_DATA_LOADED (*pGraph,Files);
}


int Check_pb_feasibility (sG *pGraph, int PlusNbRoutes)
{
int i, feasible;
float load;

load = 0;
feasible = 1;

for (i = (*pGraph).Nb_clients; i < 2 * (*pGraph).Nb_clients; i ++)
        {
        load = load + (*pGraph).Demand[i];
        if ((*pGraph).Demand[i] > (*pGraph).Cap_max)
                {
                feasible = 0;
                }
        }

i = load / (*pGraph).Cap_max;
if (i < (float) load / (float) (*pGraph).Cap_max )
        {
        i = i + 1;
        }

(*pGraph).NbRouteMax =  i + PlusNbRoutes;
return feasible;
}



void PRINT_ARCS_RANKED (double **Cost, int * Start, int * End, int ** Num_of_Arc, int Nb_clients, sF Files)
{
int i, j, p;
FILE * file;
char name[100];

strcpy (name, Files.Source);
strcat (name, ".Arcs");
file = fopen (name, "a+");

if (file == NULL)
        {
        printf ("\nError when opening file %s for writing Arc ranked data\n", name);
        systempause(getchar());
        }
else
        {
        fprintf (file,"\n\n %s: ARCS RANKED : Node 0 is the depot", Files.Source);
        fprintf (file, "\n num) Start - End : Cost");
        for (p = 0; p < Nb_clients* (Nb_clients+1)/2; p ++)
                {
                fprintf (file, "\n%d) %d - %d : %f", p, Start[p], End[p], Cost[Start[p]+Nb_clients-1][End[p]+Nb_clients-1]);
                }
        fprintf (file, "\n\n");
        for (i = 0; i < Nb_clients + 1; i ++)
                {
                for (j = i + 1; j < Nb_clients + 1; j ++)
                        {
                        fprintf (file, "\nEdge (%d - %d) = num %d", i, j, Num_of_Arc[i][j]);
                        }
                }
        fclose (file);
        }
}




void Rank_Arcs_per_Cost (double **Cost, int * Start, int * End, int ** Num_of_Arc, int Nb_clients, sF Files, int print)
{
int i, j, p, Tmp_start, Tmp_end;
for (i = 1; i < Nb_clients * (Nb_clients+1)/2; i ++)
        {
        p = 0;
        while ((p <= i) && (Cost[Start[p]+Nb_clients-1][End[p]+Nb_clients-1] <= Cost[Start[i]+Nb_clients-1][End[i]+Nb_clients-1]))
        // because of the conversion, node 0 is the depot, but node 1 is the 1st client, which is in fact Nb_clients
                {
                p = p + 1;
                }
        if (p <= i)
                {
                Tmp_start = Start[i];
                Tmp_end = End[i];
                for (j = i - 1; j >= p; j --)
                        {
                        Start[j+1] = Start[j];
                        End[j+1] = End[j];
                        }
                Start[p] = Tmp_start;
                End[p] = Tmp_end;
                }
        }
p = 0;
for (p = 0; p < Nb_clients * (Nb_clients+1) / 2; p ++)
        {
        Num_of_Arc[Start [p]][End [p]] = p;
        }

if (print > 0)
        {
        PRINT_ARCS_RANKED (Cost, Start, End, Num_of_Arc, Nb_clients, Files);
        }

}


