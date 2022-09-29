# Analysis and Synthesis of Algorithms
A C++ implementation of a maximum-flow problem in times of COVID-19 pandemic.

##  Problem Description
The problem takes place in Manhattan, New York, during these times of COVID- 19 pandemic. In fact, an optimal system that prevents citizens to meet each other in the streets of the city is needed in order to contain the spreading of the virus.

In particular, every person in town needs to reach a supermarket from the house where they live. While this could be achieved by following different routes in normal conditions, a special set of paths have to be carefully selected now in order to avoid gatherings at the beginning, at the end, or while traveling the paths themselves. In other words, the goal of the program is to provide the maximum number of citizens that is admissible to safely travel through the city.

The regular quadratic structure of Manhattan allows to build a generic architecture able to be adapted to different configurations of the city, which are given from the input:
* number of ***avenidas*** (streets in the NORD-SOUTH direction) and ***ruas*** (streets in the EAST-WEAST direction);
* number of supermarkets and citizens in the city;
* coordinates of every supermarket and house in the city (they can take place just in crossroads between an *avenida* and a *rua*, not along one of the two streets).

Different configurations are then possible, including multiple citizens living in the same house and multiple supermarkets being at the same crossroad.

## Solution Description
The approach that I followed to tackle this problem was to think of it as a ***maximum-flow problem*** with multiple sources (houses) and multiple sinks (supermarkets). The key idea is to picture the city as a graph where the crossroad constitutes the vertices and the streets (always bi-directional) constitutes the edges. Moreover, the presence of a ***super-source*** and a ***super-sink*** are needed in order to merge the flows of citizens from a single starting point to a single end point.

I used the ***Ford-Fulkerson*** algorithm supported by a depth-first search (DFS) to find the augmenting paths in the residual network and explore the graph. All the capacities of the graph are typically set to 1, since not more than one person is allowed to travel in the same street.

## Theoretical Analysis
The proposed algorithm is made of the following parts:
* reading of the input data above mentioned;
* construction of the graph;
* one call of the Ford-Fulkerson method to find the maximum flow of the graph which, in turn, contains multiple calls of the DFS function that recursively explore the graph and find the houses-supermarkets routes.

## Reading input data
The very first part of the program reads the input file and stores its content in the following data structures:
* one integer variable contains the number of avenidas;
* one integer variable contains the number of ruas;
* one integer variable contains the number of supermarkets;
* one integer variable contains the number of citizens;
* one array contains the *rua*-number of all supermarkets;
* one array contains the *avenida*-number of all supermarkets;
* one array contains the *rua*-number of all houses;
* one array contains the *avenida*-number of all houses;

From here, it has been possible to calculate the total number of vertices of the graph (on which I based several loops iterations) and the position of any vertex in the graph (based on a given order I have described in a separate function), as well as derive other essential information.

## Construction of the graph
The construction of the graph can be summarized as a sequence of the following steps:
* Initializing the graph as an empty multidimensional array (i.e., in matrix representation, where edges have capacities instead of weights);
* Setting the capacity of all edges equal to 0, since it is going to be the most common value;
* Assigning capacity = 1 to the edges connecting the i-th internal node of the graph with the (i-1)-th, (i+1)-th, (i-N)-th and (i+N)-th (where N is the horizontal dimension of the network);
* Repeating the same procedure with the external nodes, meaning the ones constituting the first and last avenida/rua, with the consequent adjustments;
* Repeating the same procedure with the four nodes at the corners with the consequent adjustments;
* Connecting the super-source with all the houses and all the supermarkets with the super-sink;
* Canceling (meaning, setting the capacity = 0) the edges outgoing from all the supermarkets;
* Canceling (meaning, setting the capacity = 0) the edges incoming to all the houses.

However, the representation of the graph as a matrix is not optimal; in fact, the program encounters *segmentation fault* when applied to higher- dimensional tests (9 in total). On the other side, I found it an easier implementation, as well as very clear to picture and modify if needed.

## Ford-Fulkerson method
In conclusion, the real implementation of the algorithm. As I have already stated above, I relied on the Ford-Fulkerson method since my objective was to solve a maximum-flow problem. The tricky part was to understand which function to use to find the augmenting path in the residual network; at the end, I opted for a ***Depth-First Search (DFS)*** with some modifications in it.

First, I had to manipulate the well-known *visited* flag at the end of every search as well as set it as input of the function, since I didn’t want to “send” citizens through edges or to vertices where other people have already been.

Secondly, I had to admit that houses can have multiple citizens. Once more, this has to do with the visited flag, which will turn true when there is no residual capacity from the super-source to the considered house.

Lastly, the ***order of exploration***. I believed it could be possible to describe a universal rule based on which the algorithm could always choose the best path for every citizen and for every configuration of the graph. Initially, the DFS was just evaluating vertices in alphanumeric order, but I have quickly realized that it was not enough. A small improvement of it was to give priority to the vertices that, instead, could not be reached from any other side of the network. In this way, I ensured that parts of the graph were not left out for ever. Unfortunately, looking ahead of just one move (i.e., evaluating the edges of the next vertex I would visit) doesn’t provide a unified solution, since the whole hypothetical route should be examined.








