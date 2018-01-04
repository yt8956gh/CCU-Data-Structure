5-1 Dijkstra’s algorithm

    READ FILENAME: 1input.txt
    This program will show adjacency matrix first.
    And ask user "Enter two vertice <start end>:", 
    user can exit program with enter zero to start or end.

    It works like below...

    0 2 5 0 0 
    0 0 6 4 0 
    0 0 0 0 3 
    0 0 9 0 0 
    0 0 0 0 0 
    Enter two vertice <start end>:1 2
    The cost from 1 to 2 is : 2

    Enter two vertice <start end>:1 5
    The cost from 1 to 5 is : 8

    Enter two vertice <start end>:5 4
    The cost from 5 to 4 is : -1

    Enter two vertice <start end>:3 4
    The cost from 3 to 4 is : -1

    Enter two vertice <start end>:0 1
    exit

/##################################################################/

5-2 Kruskal’s algorithm

    READ FILENAME: 2input.txt
    This program uses Union-Find Algorithm to check whether the new edge will form a circuit.

    Union-Find Algorithm:

    It make every vertice save a key ,which is minimum vertice in that subtree.
    That "some vertex have same key" represents that they are in same subtree, vice versa.
    A new edge will form a circuit iff. they are in same subtree.

    It works like below...

    The edges of Minimum Cost Spanning Tree are:

    Edge 1:<1 2> cost:2
    Edge 2:<3 5> cost:3
    Edge 3:<2 4> cost:4
    Edge 4:<1 3> cost:5
    Minimum cost = 14


/##################################################################/

5-3 Breadth First Search

    READ FILENAME: output.txt 
    
    This program will analyze every line whose foramt is "Edge 1:<0 1> cost:2".
    It records relation of node with adjacency matrix.
    Start_node is bigger node linked to most cost edge.
    
    It works like below...

    Level	Name
    0	    3
    1	    2
    1	    4
    2	    1
    2	    5


    
