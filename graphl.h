//  Created by Nguyen Nguyen on 11/8/16.
//  graphl.hpp
//  Lab3
//  Copyright © 2016 Nguyen Nguyen. All rights reserved.

//Lab 3: GraphL calculates depth-first algorithm (list is added from the first node and
//it's adjacent is addecent in front of the first connected listed if from same path.).
//Reads data from provided data file, and find the depth-first recovery path.
//Has display all and helper functions.
#ifndef graphl_h
#define graphl_h

#include "nodedata.h"
#include "limits.h"
#include <iomanip>
#include <stdio.h>
using namespace std;

int const MAXNODES_L = 101;  // const size of an array

class GraphL
{
public:
    // Constructor and Destructor
    GraphL();
    ~GraphL();
    
// Functions
    //Builds an adjacency list in the order it was give from the read in file
    void buildGraph(ifstream& inFile);
   //does DFS method
    void depthFirstSearch();
    //prints out the graph in DFS order
    void displayGraph();

private:
    int size; //size of array
    struct EdgeNode;               // struct declaration
    struct GraphNode
    {
        EdgeNode* edgeHead;        // head of the list of edges
        NodeData* data;            // data information about each node
        bool visited;
    };
    
    GraphNode arrayDFS[MAXNODES_L];
    
    struct EdgeNode
    {
        int adjGraphNode;           // subscript of the adjacent graph node
        EdgeNode* nextEdge;         // next node
    };
    
    // helper function
    void helpDFS(int visited);
};
#endif /* graphl_h */
