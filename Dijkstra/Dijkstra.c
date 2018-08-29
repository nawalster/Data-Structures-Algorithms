
/*
Purpose: To create program to help a droid find the shortest direct (no repeats) path from a starting room to an
ending room in a maze. The input will be a maze (adjacency matrix) read from a text file.
*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INFINITY 10000

int numNodes; //global

void printPath(int parent[], int dest){
    if (parent[dest] == -1) //source
        return;
 
    printPath(parent, parent[dest]);
    printf("%d, ", dest);
}


//Dijkstra's shortest path for unweighted graph
void dijkstra(int graph[numNodes][numNodes], int source, int dest)
{
	int i, j, count, u, v;
    int distance[numNodes]; //structure to represent distance from source to all other nodes in the network
    int shortestDist;        
    int visitedSet[numNodes]; // 1 if node is visited and is shortest distance, otherwise 0
 
	for (i = 0; i < numNodes; i++){
        distance[i] = INFINITY; //all distances initially set to INFINITY
        visitedSet[i] = FALSE; //all nodes initially not visited
    }
    
    distance[source] = 0; //always
    
    int parent[numNodes]; //parent array help to backtrack the shortest path to a node from the source node
    parent[source] = -1; //starting with the source node; invalid because source has no parent
 
	for (j = 0; j < numNodes-1; j++){ 
        shortestDist = INFINITY; // assign infinity in order to compare with the distance to each node
    	for (v = 0; v < numNodes; v++){ //find the node with the shortest distance that hasn't been visited yet
        	if (visitedSet[v] == FALSE && distance[v] <= shortestDist){ // compare the newly calculated tentative distance to the current assigned value and assign the smaller one
				shortestDist = distance[v];
				u = v;
			}
		}
        visitedSet[u] = TRUE; //mark as visited
 
		for (v = 0; v < numNodes; v++){ //calculate the distance of the unvisited neighboring nodes of u and update the array accordingly
            if (visitedSet[v] == FALSE && graph[u][v] == 1 && distance[u] != INFINITY && distance[u] + 1 < distance[v]){ 
                parent[v]  = u; //for each node v, assign the previous node u
                distance[v] = distance[u] + 1; //value for the node should be updated only if an edge exists and distance of source->u->v < source->v (infinity)
            }  
		}
	}

    if (distance[dest] >= INFINITY){ //check for infinite loop or no solution
		printf("No Solution."); 
		exit(1);
	}
    //otherwise print path
    printf("%d, ", source);
    printPath(parent, dest);
}
 
   
// main
int main(void){
	
	int numRms;
    int start;
    int destination;
    int i, j;
    char comma;

    FILE * in = fopen("test.txt", "r");
    fscanf(in, "%d %d %d", &numRms, &start, &destination);
    printf("number of rooms:%d\nstarting room:%d\nending room:%d\n\n", numRms, start, destination); //to confirm
    fclose(in);
    
    int cols = numRms;
    int rows = numRms;
    int graph[rows][cols];
    
    in = fopen("test.txt", "r");
	fseek(in, 9, SEEK_SET);

    for(i=0; i<numRms; ++i){
    	for(j=0; j<numRms; ++j){
    		fscanf(in, "%d", &graph[i][j]);
    		//printf("%d", graph[i][j]);
    		fscanf(in, "%c", &comma); //to get rid of comma
    		//printf("%c", comma);
		}
	//	printf("\n");
	}
	fclose(in);
	
	
	//print matrix
	for(i=0; i<rows;i++){
		for(j=0; j<cols; j++){
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	numNodes= numRms; //initialize the global variable
	
	printf("PATH: \n");
    dijkstra(graph, start, destination);
    
    return 0;
}
