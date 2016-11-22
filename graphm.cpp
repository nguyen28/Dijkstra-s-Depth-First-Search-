//  Created by Nguyen Nguyen on 11/4/16.
//  Copyright © 2016 Nguyen Nguyen. All rights reserved.
//  graphm.cpp
//  Lab3
//Lab 3 is about Implementing Dijskra's shortest path algorithm. It reads in a file given
//in the order of the total destinations, destination's name, numbered respectively,
//it's connected path and the weight. Then the shortest path is fonud for each destination to
//all other destinations. Printing options can be for only one destination or for all options.

#include "graphm.h"
#include "nodedata.h"

//*************************Constructor*****************************//
//Sets Tabletype T to set all, dist to infinity,
//all visited to false and all paths to 0.
//*****************************************************************//

GraphM::GraphM()
{
    size=0;
    for(int i=1; i<MAXNODES; i++)
    {
        for(int j=1; j<MAXNODES; j++)
        {
            C[i][j]=INT_MAX;
            T[i][j].dist=INT_MAX;
            T[i][j].path=0;
            T[i][j].visited=false;
        }
    }
}

//*************************buildGraph*****************************//
//builds up graph node info and adjacenct matrix of edges between each
//node reading from a data file
//*****************************************************************//

void GraphM::buildGraph(istream& inFile)
{
    int from, to, dist;
    string locationN;
    inFile >>size;
    getline(inFile,locationN);
    
    for(int i =1; i<=size; i++){
       
        data[i].setData(inFile);
    }
    
    while(inFile >> from >>to >> dist){
        if(from ==0 || to ==0 ){
            break;
        }else{
            C[from][to]=dist;
        }
    }
}

//*************************insert***********************************//
// insert an edge into graph between 2 given nodes
//******************************************************************//

void GraphM::insertEdge(int insertFrom, int insertTo, int distCost)
{
    if(insertFrom> 0 && insertTo > 0 && distCost > 0) //check if allowed insertion
    {
        C[insertFrom][insertTo]=distCost;   //insert to C data
    }
}

//**************************remove***********************************//
//remove an edge from graph 2 given nodes
//*******************************************************************//

void GraphM::removeEdge(int removeFrom, int removeTo)
{
    //make sure that the removeFrom and removeTo is within the right boundaries
    if(removeFrom >0 && removeTo >0)
    {
        C[removeFrom][removeTo]=INT_MAX; //reset the data to INT_MAX
    }
}

//***********************Shortest Path***********************************//
//Finds the shortest path between every node to every other node in the
//graph, TableType T is updated with shortest path info
//****************************************************************//

void GraphM::findShortestPath()
{
    for(int source= 1; source<=size;source++)
    {
        T[source][source].dist=0;
        T[source][source].visited=true;
        
        for(int to=1; to<=size; to++)
        {
            if(C[source][to] != INT_MAX){
                T[source][to].dist=C[source][to];
                T[source][to].path=source;
            }
        }
        int visited=-1;
        while(visited != 0){
    
            int current=INT_MAX;
            visited=0;
            for(int to=1; to <=size; to++) //looking for closest child
            {
                if((T[source][to].visited==false) && (C[source][to]< current))
                {
                    current=C[source][to];
                    visited=to;
                }
            }
            
            if(visited==0)
            {
                break;
            }
            
            T[source][visited].visited=true;
            
            for(int neighbors=1; neighbors<=size; neighbors++)
            {
                if(visited == neighbors){
                    continue;
                }
                if(C[visited][neighbors]==INT_MAX){
                    continue;
                }
                if(T[source][neighbors].visited ==true){
                    continue;
                }
                    
                if(T[source][neighbors].dist > (T[source][visited].dist + C[visited][neighbors]))
                {
                    T[source][neighbors].dist = T[source][visited].dist + C[visited][neighbors];
                    T[source][neighbors].path = visited;
                }
            }
        }
    }
}


//***********************Display ALL***********************************//
//Displays the cost and path from every node to every other node.
//******************************************************************//

void GraphM::displayAll()
{
    //Prints out the top line
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
    << setw(15) << "Dijkstra's" << setw(5) << "Path" << endl;
    
    for(int fromPath=1; fromPath <=size; fromPath++)
    {
        cout << data[fromPath] << endl <<endl;
        
        for(int toPath=1; toPath <=size; toPath++)
        {
            if (T[fromPath][toPath].dist != 0)
            {
                cout << setw(27) << fromPath;   // print from node
                cout << setw(10) << toPath;     // print to node
                
                if(T[fromPath][toPath].dist == INT_MAX)
                {
                    cout << setw(15) << "---" << endl;
                }
                else
                {
                    cout << setw(15) <<fromPath << setw(5) << toPath;
                    cout << setw(10) << T[fromPath][toPath].dist << setw(5);
                    findPath(fromPath, toPath); //calling helper function to get the path
                    cout << endl;
                }
            }
        }
    }
    cout << endl;
}


//***********************display***********************************//
//displays the shortest distance with path info between the from path
//and the toPath.
//****************************************************************//

void GraphM::display(int fromPath, int toPath)
{

    if (T[fromPath][toPath].dist != INT_MAX)    // adjacent node check
    {
        cout << setw(7) << fromPath << setw(7) << toPath;   // print node from and to data
        cout << setw(12) << T[fromPath][toPath].dist << setw(15); // print distance
        
        findPath(fromPath, toPath); // call helper
        cout << endl;
        
         helpGetData(fromPath, toPath); // call helper
    }
    else    // no adjacent node
    {
        cout << setw(7) << fromPath << setw(7) << toPath;   // print node from and to data
        cout << setw(15) << "----" << endl;
    }
    
    
    cout << endl;
    
}

//***********************helper function***********************************//
//helps recursively call and get the path from one path to another
//****************************************************************//

void GraphM::helpGetPath(int fromPath, int toPath)
{
    if(fromPath != toPath){
        if(T[fromPath][toPath].path!=0){
            helpGetPath(fromPath, T[fromPath][toPath].path);
        }
    }
    cout << toPath << "";
}

//***********************Find the Path***********************************//
//Helper function that will from the path
//****************************************************************//
void GraphM::findPath(int fromPath, int toPath)
{
    if (T[fromPath][toPath].dist == INT_MAX)
    {
        return; // no path
    }
    
    if (fromPath == toPath)
    {
        cout << toPath << " ";  // print data
        
        return;
    }
    
   findPath(fromPath, T[fromPath][toPath].path);
    
    cout  << toPath << " ";   // print path
}

//***********************Find the Path***********************************//
//Helper function that will from the path
//****************************************************************//

void GraphM::helpGetData( int fromPath, int toPath)
{
    if (T[fromPath][toPath].dist == INT_MAX)
    {
        return; // no data
    }
    
    if (fromPath == toPath)
    {
        cout << data[toPath] << endl;   // print data
        
        return;
    }
    
    helpGetData(fromPath, T[fromPath][toPath].path);  // call helper
    
    cout << data[toPath] << endl << endl;    // print data
}

