#include <iostream>
#include <stdio.h>
#include <list>
#include <algorithm> 
#include <fstream>
#include <limits.h> 
#include <string.h> 
#include <queue> 
using namespace std;

//The maximum is 1023 - I don't think this is a complete random number
#define sao 900

bool DFS(int V, int rGraph[][sao], int x, int t, int parent[], bool visited[]){

  // If the source = sink, I already exit the loop
  if(x == t) return true; 
  visited[x] = true;

  for(int i = 0; i < V; i++){
    if(visited[i]==false && rGraph[x][i]){
      //I start building the structure of parents
      parent[i] = x; 

      if(DFS(V, rGraph, i, t, parent, visited))
        return true;
    }
  }
  return (visited[t] == true);  
}


// Returns the maximum flow from s to t in the given graph 
int fordFulkerson(int V, int graph[][sao], int s, int t) 
{ 
    int u, v; 
  
    // Residual graph where rGraph[i][j] indicates residual capacity of edge 
    // from i to j (if there is an edge. If rGraph[i][j] is 0, then there is not) 
    int rGraph[sao][sao];   
    
    //Filling the rGraph with zero (which is going to be the most common value) 
    for (int i = 0; i < sao; i++){
        for (int j = 0; j < sao; j++) {
            rGraph[i][j] = 0;
        }
    }

    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             // This is a capacity which is initially equal to the one of the original graph
             rGraph[u][v] = graph[u][v];  
  
    
    int parent[sao];    // This array is filled by BFS and to store path --> empty array of V elements                
    bool visited[sao];  // This array contains information about the vertices being visited or not 
    bool crowded[sao];

    for (int i = 0; i < V; i++){
      visited[i] = false;
      crowded[i] = false;
    }

    // There is no flow initially 
    int max_flow = 0;  
  
    // Augment the flow while there is path from source to sink 
    // This "while" loop refers to the fact that bfs finds a path --> visited[t] = True 
    while (DFS(V, rGraph, s, t, parent, visited)) 
    { 
        // Find minimum residual capacity of the edges along the path filled by BFS 
        // (= find the maximum flow through the path found)
        int path_flow = INT_MAX;  //super big number pre-defined 
        
        // Re-built the path that BFS formed, print its vertices and set them as VISITED 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            crowded[u] = true;    
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
    
        // Update the "visited" list with the "crowded" list
        for (v=0; v<V; v++){
          visited[v] = crowded[v];
        }

        // Update residual capacities of the edges and reverse edges along the path 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            // Update direct and reverse edges in the residual graph 
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 

        // Two citizens in one house situation
        for (int i = 0; i < V; i++){
          if (rGraph[0][i] > 0) {
            visited[i] = false;
          }
        }
}
  
    // Return the overall flow 
    return max_flow; 
} 

int position(int x, int y, int M, int N)
{
  // The formula depends on both number of ruas and avenidas, since I can have rectangular configurations
  return N * (M - x) + y; 
}


int main() 
{ 

    //------------- FIRST BLOCK: total number of avenidas and ruas ----------------//
    int M;       
    int N;             
        
    cin >> M;
    cin >> N;

    // Number of vertices
    int V = (N * M)+2; 
    
    //----------------------------------------------------------------------------//

    //------------ SECOND BLOCK: total number of supermarkets and houses ---------//
    int number_supermarkets;   
    int number_houses;            
    
    cin >> number_supermarkets;
    cin >> number_houses;
    
    //----------------------------------------------------------------------------//

    //------------ THIRD BLOCK: positions of supermarkets and houses ---------//

    //---SUPERMARKETS----//
    list<int> streets_supermercados;
    string avenidas_ruas_supermercados = " ";

    for (int i = 1; i<=(number_supermarkets*2); i++){
        cin >> avenidas_ruas_supermercados;
        int AV_supermercados = stoi(avenidas_ruas_supermercados);
        streets_supermercados.push_back(AV_supermercados);
    }

    // Lists --> arrays
    int array_streets_supermercados[streets_supermercados.size()];
    copy(streets_supermercados.begin(), streets_supermercados.end(), array_streets_supermercados);

    list <int> avenidas_supermercados;
    list <int> ruas_supermercados;

    for (int i = 0; i < (number_supermarkets*2); i+=2) { 
        avenidas_supermercados.push_back(array_streets_supermercados[i]);
    } 
    
    for (int i = 1; i < (number_supermarkets*2); i+=2) { 
        ruas_supermercados.push_back(array_streets_supermercados[i]);
    }

    // Lists --> arrays (AVENIDAS)
    int AV_supermarkets[avenidas_supermercados.size()];
    copy(avenidas_supermercados.begin(), avenidas_supermercados.end(), AV_supermarkets);

    // Lists --> arrays (RUAS)
    int RUAS_supermarkets[ruas_supermercados.size()];
    copy(ruas_supermercados.begin(), ruas_supermercados.end(), RUAS_supermarkets);


    //---HOUSES----//

    list<int> streets_moradas;
    string avenidas_ruas_moradas = " ";

    for (int i = 1; i<=(number_houses*2); i++){
        cin >> avenidas_ruas_moradas;
        int AV_moradas = stoi(avenidas_ruas_moradas);
        streets_moradas.push_back(AV_moradas);
    }
    
    // ALTERNATIVE WAY TO COPY THE LIST INTO THE ARRAY
    int array_streets_moradas[number_houses*2]; 
    copy(streets_moradas.begin(), streets_moradas.end(), array_streets_moradas);

    list <int> avenidas_moradas;
    list <int> ruas_moradas;

    for (int i = 0; i < (number_houses*2); i+=2) { 
        avenidas_moradas.push_back(array_streets_moradas[i]);
    }

    for (int i = 1; i < (number_houses*2); i+=2) { 
        ruas_moradas.push_back(array_streets_moradas[i]);
    }

    // Lists --> arrays (AVENIDAS)
    int AV_houses[avenidas_moradas.size()];
    copy(avenidas_moradas.begin(), avenidas_moradas.end(), AV_houses);

    // Lists --> arrays (RUAS)
    int RUAS_houses[ruas_moradas.size()];
    copy(ruas_moradas.begin(), ruas_moradas.end(), RUAS_houses);

    //----------------------------------------------------------------------------//
    
    // GRAPH CONSTRUCTION
    // I initialize the graph as an empty multi-dimensional array 
    // I use "V+2" because I consider the supersource and the supersink
    int graph[sao][sao];  
    
    // Filling the whole graph with zero (which is going to be the most common value) 
    for (int i = 0; i < sao; i++){
        for (int j = 0; j < sao; j++) {
            graph[i][j] = 0;
        }
    }
    
    // INTERNAL BLOCK OF THE GRAPH
    for (int i = 1+N; i < V-2-N; i++){   //I did a change here
      graph[i][i-1] = 1;
      graph[i][i+1] = 1;
      graph[i][i+N] = 1;
      graph[i][i-N] = 1;
    } 

    // FIRST AVENIDA (= row at the bottom of the graph)
    for (int i = V-N; i < V-2; i++){
      graph[i][i-1] = 1; 
      graph[i][i+1] = 1; 
      graph[i][i-N] = 1; 
      graph[i][i+N] = 0; //is this necessary?
    } 


    // LAST AVENIDA (= row at the top of the graph)
    for (int i = 2; i < N; i++){
      graph[i][i-1] = 1;
      graph[i][i+1] = 1;
      graph[i][i+N] = 1;
    } 


    // FIRST RUA (= column at the left of the graph)
    for (int i = 1+N; i <= V-(2*N+1); i+=N){
      //cout << i << endl;
      graph[i][i-N] = 1; 
      graph[i][i+N] = 1; 
      graph[i][i+1] = 1; 
      graph[i][i-1] = 0;
    } 

    // LAST RUA (= column at the right of the graph)
    for (int i = 2*N; i <= V-2-N; i+=N){
      graph[i][i-N] = 1; 
      graph[i][i+N] = 1; 
      graph[i][i-1] = 1; 
      graph[i][i+1] = 0;
    } 
   
    // EXTREME CORNER UP-LEFT
    graph[1][1+1] = 1; 
    graph[1][1+N] = 1; 
    //graph[1][1-N] = 0;
    graph[1][1-1] = 0;


    // EXTREME CORNER UP-RIGHT
    graph[N][N-1] = 1; 
    graph[N][N+N] = 1;
    graph[N][N+1] = 0;
    graph[N][N-N] = 0;


    // EXTREME CORNER DOWN-LEFT
    graph[N*M-N+1][N*M-N+1-N] = 1; 
    graph[N*M-N+1][N*M-N+1+1] = 1;
    graph[N*M-N+1][N*M-N+1+N] = 0; 
    graph[N*M-N+1][N*M-N+1-1] = 0;

    
    // EXTREME CORNER DOWN-RIGHT
    graph[N*M][N*M-N] = 1; 
    graph[N*M][N*M-1] = 1;
    graph[N*M][N*M+N] = 0; 
    graph[N*M][N*M+1] = 0;

    // SUPERSOURCE 1 - pure initialization to 0
    for (int i = 0; i < V; i++){
      graph[0][i] = 0;
    }

    // SUPERSOURCE 2 (strictly related with number of houses)
    for (int i = 0; i < number_houses; i++){
      int x = AV_houses[i];   //coordinates x of the houses
      int y = RUAS_houses[i]; //coordinates y of the houses

      //I allow more citizens to live in the same crossroad
      graph[0][position(x,y,M,N)] += 1;    
    }

    //SUPERSINK (strictly related with number of supermarkets)
    for (int i = 0; i < number_supermarkets; i++){
      int x = AV_supermarkets[i];    //coordinates x of the supermarkets
      int y = RUAS_supermarkets[i];  //coordinates y of the supermarkets

      //No need to modify this as I did for the supersource, 
      //since only one supermarket per node can be considered in the solution
      graph[position(x,y,M,N)][V-1] = 1;     
    }

    //CANCELLATION OF EDGES BETWEEN SUPERMARKETS
    for (int i = 0; i < number_supermarkets; i++){
      int x = AV_supermarkets[i];  
      int y = RUAS_supermarkets[i];  
      for (int j = 0; j < number_supermarkets; j++){
        int w = AV_supermarkets[j];  
        int z = RUAS_supermarkets[j];  
        graph[position(x,y,M,N)][position(w,z,M,N)] = 0;
       }
    }

    //CANCELLATION OF EDGES BETWEEN HOUSES 
    for (int i = 0; i < number_houses; i++){
      int x = AV_houses[i];  
      int y = RUAS_houses[i];  
      for (int j = 0; j < number_houses; j++){
        int w = AV_houses[j];  
        int z = RUAS_houses[j];  
        graph[position(x,y,M,N)][position(w,z,M,N)] = 0;
      }
    }

    //CANCELLATION OF ALL THE EDGES GOING TO THE HOUSES FROM DISTANCE = 1
    for (int i = 0; i < number_houses; i++){  
      int x = AV_houses[i];  
      int y = RUAS_houses[i]; 
      for (int j = 1; j < V; j++){         
        graph[j][position(x,y,M,N)] = 0;                       
      }
    }
    
    //CANCELLATION OF ALL THE EDGES GOING FROM THE SUPERMARKETS FROM DISTANCE = 1 
    for (int i = 0; i < number_supermarkets; i++){  
      int x = AV_supermarkets[i];  
      int y = RUAS_supermarkets[i]; 
      for (int j = 0; j < V-1; j++){         
        graph[position(x,y,M,N)][j] = 0;                       
      }
    }

    //CHECK TO SEE IF THE GRAPH HAS BEEN BUILT CORRECTLY
    for (int i = 0; i < V; i++){
      for (int j = 0; j < V; j++){
      }
    }    

    //INPUT: total number of vertices, graph, supersource, supersink
    cout << fordFulkerson(V, graph, 0, V-1) << endl;
    return 0;
  }