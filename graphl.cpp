
//  graphl.cpp
//  Lab3
// Created by Nguyen Nguyen on 11/8/16.
//  Copyright © 2016 Nguyen Nguyen. All rights reserved.
//Lab 3: GraphL calculates depth-first algorithm (list is added from the first node and
//it's adjacent is addecent in front of the first connected listed if from same path.).
//Reads data from provided data file, and find the depth-first recovery path.
//Has display all and helper functions.

#include "graphl.h"
#include "nodedata.h"

//*************************Constructor*****************************//
//Sets array to set data nad edgehead to Null and all visited to false.
//*****************************************************************//
GraphL::GraphL()
{
    size = 0;
    
    for (int i = 1; i < MAXNODES_L; ++i){
        arrayDFS[i].visited = false;
        arrayDFS[i].edgeHead = NULL;
        arrayDFS[i].data = NULL;
    }
}

//*************************Deconstructor*****************************//
//deletes all pointers and resets data to NULL
//*****************************************************************//

GraphL::~GraphL()
{
    for (int i = 1; i <= size; ++i)
    {
        arrayDFS[i].visited = false;
        delete arrayDFS[i].data;  // delete edge name
        arrayDFS[i].data = NULL;  // set edge name to NULL
        
        if (arrayDFS[i].edgeHead != NULL) // check for linked list in array index
        {
            EdgeNode* del = arrayDFS[i].edgeHead;
            
            while (del != NULL) // traverse linked list
            {
                arrayDFS[i].edgeHead = arrayDFS[i].edgeHead->nextEdge;
                delete del; // delete node
                del = NULL; // set node to NULL
                del = arrayDFS[i].edgeHead;   // move head
            }
        }
    }
}

//*************************buildGraph*****************************//
// Builds up graph node information and adjacency list of edges between each
// node reading from a data file
//*****************************************************************//

void GraphL::buildGraph(ifstream& inFile)
{
    // read from data file
    inFile >> size;            // sets the size
    string nodeName = "";       // name of each node
    getline(inFile, nodeName); // read line
    
    for (int i = 1; i <= size; ++i) // insert edge names
    {
        getline(inFile, nodeName);
        NodeData* tmp = new NodeData(nodeName);
        arrayDFS[i].data = tmp;   // insert into array
    }
    
    int from, to;
    
    while (inFile >> from >> to)   // fill linked list
    {
        if (from == 0)
        {
            break;
        }
        
        if (arrayDFS[from].edgeHead == NULL)  // first node at array index
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            // insert adjacent
            arrayDFS[from].edgeHead = node;   // point to head
            arrayDFS[from].edgeHead->nextEdge  = NULL;
        }
        else    // additional nodes in linked list
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            // insert adjacent
            node->nextEdge = arrayDFS[from].edgeHead;  // move pointer
            arrayDFS[from].edgeHead = node;  // assign as head
        }
    }
}

//**************************DFSearch***************************************//
// Makes a depth-first search and displays each node in depth-first order
//*****************************************************************//

void GraphL::depthFirstSearch()
{
    cout << "Depth-fisrt ordering:";    // typo deliberate to match output
    
    for (int i = 1; i <= size; ++i) // loop through size
    {
        if (!arrayDFS[i].visited)   // check if node has been visited
        {
            helpDFS(i);  // call helper
        }
    }
    
    cout << endl;
}

//********************helpDFS****************************************//
// Helper function for depthFirstSearch()
// Recursively finds the depthFirstSearch
//*****************************************************************//
void GraphL::helpDFS(int i)
{
    cout << setw(2) << i;   // print node
    arrayDFS[i].visited = true;   // mark visited
    EdgeNode* current = arrayDFS[i].edgeHead; // move pointer to head
    
    while (current != NULL) // loop till end of linked list
    {
        if (!arrayDFS[current->adjGraphNode].visited) // check if visited
        {
            helpDFS(current->adjGraphNode);  // call helper
        }
        
        current = current->nextEdge;    // move pointer to next node in linked list
    }
}

//********************Display Graph*********************************************//
// Displays each node information and edge in the graph
//*****************************************************************//
void GraphL::displayGraph()
{
    
    cout << "Graph:" << endl;
    
    for (int i = 1; i <= size; ++i) // print array info
    {
        // print index and name of the node
        cout << "Node" << i << setw(10) << *arrayDFS[i].data << endl << endl;
        
        EdgeNode* current = arrayDFS[i].edgeHead; // assign to current
        
        while (current != NULL) // check for linked list
        {
            // print linked list
            cout << setw(7) << "edge " << i << setw(4) << current->adjGraphNode << endl;
            current = current->nextEdge;  // move pointer to next node in linked list
        }
    }
}

