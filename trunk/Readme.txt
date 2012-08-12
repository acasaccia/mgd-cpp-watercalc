
WaterCalc Homework - Advanced cpp programming
Master in Computer Game Development, Verona, Italy
See problem description @ http://code.google.com/p/mgd-cpp-watercalc/

author Andrea Casaccia
date 14 July 2012

===============================================================================
Usage and input design:

usage: C:\>WaterCalc.exe [inputfile] [-adjacency=4|8]
-adjacency parameter is optional default is 4-way adjacency.

With 4 way adjacency each cell communicates with neighbours like this:
 
   | X |   
-----------
 X | O | x
-----------
   | X |

while in 8 way adjacency:

 X | X | X 
-----------
 X | O | x
-----------
 x | X | X


As a design choice I slightly changed input file format adding the number of
rows and columns on top, so that I don't have to check for endlines while
parsing and error detecting is much easier.

expected input file format:
rows columns
element(0,0)	...		element(0,columns)
...				...		...
element(rows,0)	...		element(rows,columns)

===============================================================================
Vertex data structure description:

File is parsed into a vector of vertexes, the attributes of each are:
* uint_t height;	parsed from input file
* uint_t capacity;	initialized to 0
* bool stable;		flag initialized to false, becomes true when the capacity
					value of Vertex is the final one
* bool isSink;		I modeled the outside of the container as a special node,
					with 0 capacity and	0 height.
					All border vertexes in the container are connected to it.
					I will refer to it as the "sink". This flag is used to
					avoid treating the sink as a normal cell when finding the
					border of a cluster later in the algorithm.
* std::forward_list<Vertex*> neighbours;	pointers to neighbours according to
											adjacency mode chosen
Having typedef-ed uint_t as unsigned int, I can treat at most uint_t_MAX high cells.

===============================================================================
Graph data structure description:

Graph is a vector of Vertexes.
I keep track of rows and columns to implicitly determine each vertex neighbour.
I can treat at most containers with uint_t_MAX rows and columns.
After object creation buildAdjacencyList() has to be called, to explicit
neighbouring informations and create on each Vertex the lists of pointers to
neighbour vertexes.
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
After parsing the only node for which I have stable status is the sink. I
iterate from it, climbing up the borders of the container and moving through
the higher vertexes I find. For each of these vertexes I can state they have
0 capacity and stable status as their content directly goes into the sink.
This way I easily restricted search space for the second part of the algorithm.

After preprocessing:
0 0 0 0 0 0 0
0 ? ? ? 0 0 0
0 ? ? ? 0 0 0
0 0 ? ? ? ? 0
0 0 0 0 0 0 0
0 0 ? 0 0 0 0
0 0 0 0 0 0 0

Processing phase:
1 Sort the unstable vertexes by height plus capacity
2 Select the lowest as current
3 Find the cluster of neighbours with the same height and capacity as current
  if they exists (I refer to these vertexes as "plateau").
4 Find the wall of the plateau (the border vertexes)
5 Shortest vertex of the wall determines if selected plateau's capacity has to
  be incremented.
6 If shortest wall is stable, mark all plateau as stable (there is no way
  its capacity can further increase).

I implemented the whole algorithm without recursion to avoid being
limited by stack size for huge amounts of node.

Container capacities:
0 0 0 0 0 0 0
0 3 0 0 0 0 0
0 2 0 1 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 0 0
