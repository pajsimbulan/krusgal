
*********************************
About:\
-Program finds a minimum spanning tree.  Kruskal Algorithm is used to find minimum spanning tree\
-Sorts edges from min weight -> max weight\
-Keeps adding edge starting from min weight to a graph as long as graph is acyclic\
-Uses DFS algorithm to check if graph is acyclic
*********************************

*********************************
HOW TO RUN:
- type make to build program which creates binary file MWST
- run ./MWST **inputfile** **outpufile**, of which input file should consist of the following format:\
(integer num of vertices)\
(integer num of edges)\
(int u) (int v) (int weight), where u and v are edges and weight is weight of edge\
i.e\
4\
4\
1 2 5\
2 3 4\
3 4 6\
4 1 10\
make clean removes all ".o" files and "MWST" file created from building program
**********************************

************************************
FILES INCLUDED:
1. README.md
2. Makefile
3. Graph.c
4. Graph.h
5. List.c
6. List.h
7. MWST.c
**************************************

