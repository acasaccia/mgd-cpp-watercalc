
WaterCalc Homework - Advanced cpp programming
Master in Computer Game Development, Verona, Italy
See problem description @ http://code.google.com/p/mgd-cpp-watercalc/

author Andrea Casaccia
date 14 July 2012

===============================================================================
Usage and input design:

usage: C:\>WaterCalc.exe [inputfile] [-adjacency=4|8]
-adjacency parameter is optional default is 4-way adjacency.

4 way adjacency water flow:
 
   | X |   
-----------
 X | O | x
-----------
   | X |

8 way adjacency water flow:

 X | X | X 
-----------
 X | O | x
-----------
 x | X | X


As a design choice I slightly changed input file format adding the number of
rows and columns on top, so that I don't have to check for endlines while
parsing and error detecting is way easier.

expected input file format:
rows columns
element(0,0)	...		element(0,columns)
...				...		...
element(rows,0)	...		element(rows,columns)

===============================================================================
Vertex data structure description:

File is parsed into a vector of vertexes, the attributes of each are:
* uint height;		parsed from input file
* uint capacity;	initialized to 0
* std::forward_list<Vertex*> neighbours;	pointers to neighbours according to
											adjacency mode chosen
* bool stable;		flag initialized to false, becomes true when the capacity
					value of Vertex is the final one

Having typedef-ed uint as unsigned int, I can treat at most UINT_MAX high cells.

===============================================================================
Graph data structure description:

Graph is a vector of Vertexes.
I keep track of rows and columns to implicitly determine each vertex neighbour.
I can treat at most containers with UINT_MAX rows and columns.
After object creation buildAdjacencyList() has to be called, to explicit
neighbouring informations and create on each Vertex the lists of pointers to
neighbour vertexes.
I modeled the outside of the container as a special node, with 0 capacity and
0 height. All border vertexes in the container are connected to it.
I will refer to it as the "sink".
Graph additionally contains some methods to display its status to std::cout.

===============================================================================
Problem resolution overview:

Parsing phase:
After parsing we get a matrix stored in a Graph structure.

Container heights:
7 6 8 3 1 2 7
8 2 6 1 3 7 0
5 3 5 0 4 1 1
4 6 4 1 1 0 2
3 8 7 2 2 2 3
1 1 0 5 5 2 4
9 8 9 7 8 2 5

Preprocessing phase:
After parsing the only node for which we have stable status is the sink. We
iterate from it, climbing up the borders of the container and moving through
the higher vertexes we find. For each of these vertexes we can state they have
0 capacity and stable status as their content directly goes into the sink.
This way we easily restrict search space for the second part of the algorithm.

After preprocessing:
0 0 0 0 0 0 0
0 ? ? ? 0 0 0
0 ? ? ? 0 0 0
0 0 ? ? ? ? 0
0 0 0 0 0 0 0
0 0 ? 0 0 0 0
0 0 0 0 0 0 0

Processing phase:
At each step of the processing phase I sort the unstable vertexes by height +
capacity.
I select the lowest as current vertex.
I recursively[1] find the cluster of neighbours with the same height and capacity as
current vertex if they exists (I refer to these vertexes as "plateau").
I recursively[1] find all border neighbours for the plateau (I refer to the border
neighbours as "wall").
The shortest vertex of the wall determines if selected plateau's capacity has to
be incremented.
If the shortest wall is stable, I can mark all plateau as stable (there is no way
its capacity can further increase).

[1] I guess recursion is bad because it could overflow the stack for a huge amount of
	cells. Having more time I would investigate a way to do it with iteration.

Container capacities:
0 0 0 0 0 0 0
0 3 0 0 0 0 0
0 2 0 1 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 0 0
