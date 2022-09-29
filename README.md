# analysis-synthesis-algorithms
A C++ implementation of a maximum-flow problem in times of COVID-19 pandemic.

# Problem Description
The problem takes place in Manhattan, New York, during these times of COVID- 19 pandemic. In fact, an optimal system that prevents citizens to meet each other in the streets of the city is needed in order to contain the spreading of the virus.
In particular, every person in town needs to reach a supermarket from the house where they live. While this could be achieved by following different routes in normal conditions, a special set of paths have to be carefully selected now in order to avoid gatherings at the beginning, at the end, or while traveling the paths themselves. In other words, the goal of the program is to provide the maximum number of citizens that is admissible to safely travel through the city.
The regular quadratic structure of Manhattan allows to build a generic architecture able to be adapted to different configurations of the city, which are given from the input:
• number of avenidas (streets in the NORD-SOUTH direction) and ruas (streets in the EAST-WEAST direction);
• number of supermarkets and citizens in the city;
• coordinates of every supermarket and house in the city (they can take
place just in crossroads between an avenida and a rua, not along one of the two streets).
Different configurations are then possible, including multiple citizens living in the same house and multiple supermarkets being at the same crossroad.
Solution Description
The approach that I followed to tackle this problem was to think of it as a maximum-flow problem with multiple sources (houses) and multiple sinks (supermarkets). The key idea is to picture the city as a graph where the crossroad constitutes the vertices and the streets (always bi-directional) constitutes the edges. Moreover, the presence of a super-source and a super-sink are needed in order to merge the flows of citizens from a single starting point to a single end point.
I used the Ford-Fulkerson algorithm supported by a DFS to find the augmenting paths in the residual network and explore the graph. All the capacities of the graph are typically set to 1 (since not more than one person are allowed to travel the same street); however, I will explain with much detail the construction of the graph in the next section.
