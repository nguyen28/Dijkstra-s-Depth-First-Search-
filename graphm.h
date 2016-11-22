//  Created by Nguyen Nguyen on 11/4/16.
//  graphm.hpp
//  Lab3
//  Copyright © 2016 Nguyen Nguyen. All rights reserved.

//Lab 3 is about Implementing Dijskra's shortest path algorithm. It reads in a file given
//in the order of the total destinations, destination's name, numbered respectively,
//it's connected path and the weight. Then the shortest path is fonud for each destination to
//all other destinations. Printing options can be for only one destination or for all options.

#ifndef graphm_h
#define graphm_h

#include "nodedata.h"
#include "limits.h"
#include <iomanip>
#include <stdio.h>

int const MAXNODES = 101;                 // constant size for T and C table

class GraphM{
private:
    //Struct of table type T that will hold if the spot has been visited, how far from each spot and the path to get there.
    struct TableType {
        bool visited;
        int dist;
        int path;
    };
    
    NodeData data[MAXNODES];           // data for graph nodes
    int C[MAXNODES][MAXNODES];  // Cost array, the adjacency matrix
    int size;    // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];   // stores visited, distance, path
    
    //helper functions
    void helpGetPath(int fromPath, int toPath);
    void findPath(int fromPath, int toPath);
    void helpGetData( int fromPath, int toPath);
    
public:
    //Constructor that sets Tabletype T to set all dist to infinifinity, all visited to false and all paths to 0.
    GraphM();
    ////builds up graph node info and adjacenct matrix of edges between each node reading from a data file
    void buildGraph(istream& inFile);
    // insert an edge into graph between 2 given nodes
    void insertEdge(int insertFrom, int insertTo, int distCost);
    //remove an edge from graph 2 given nodes
    void removeEdge(int removeFrom, int removeTo);
    void findShortestPath();
    //Displays the cost and path from every node to every other node.
    void displayAll();
    //displays the shortest distance with path info between the from path and the toPath.
    void display(int fromPath, int toPath);

};  

#endif /* graphm_h*/
