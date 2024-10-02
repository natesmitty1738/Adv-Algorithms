// CSCI 411 - Fall 2024
// Assignment 2 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 2.

#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>
using namespace std;

/******************************************************************************
 * A simple Node struct                                                       *
 * id - int - the id or name of the node                                      *
 * distance - int - the distance from some given node to this node            *
 * inSetI - bool - true if the node is a member of the set I and false otherwise *
 * visited - bool - whether or not this node has been visited                 *
 * ****************************************************************************/
struct Node {
    int id;
    int distance;
    bool inSetI;
    bool visited;
};

/**************************************************************************
 * A simple Edge struct                                                   *
 * source - shared_ptr<Node> - the node where this edge starts            *
 * destination - shared_ptr<Node> - the node where this edge ends         *
 * weight - int - the weight of this edge                                 *
 * ************************************************************************/
struct Edge {
    shared_ptr<Node> source; //to
    shared_ptr<Node> destination; //from
    int weight;
};

/****************************************************************************************************************************
 * Given a graph, find the set of nodes that belong to the set I, that is, the set of vertices v such that there            *
 * is at least one path of length negative infinity ending at v.                                                            *
 * adjacencyList - vector<vector<shared_ptr<Edge>>> - an adjacency list representation of a graph where each element is a weighted edge *
 * return - vector<int> - the integer ids of nodes in the set I                                                             *
 * **************************************************************************************************************************/
vector<int> findSetI(vector<vector<shared_ptr<Edge>>> adjacencyList){
  int numNodes = adjacencyList[0].size() - 1;
  adjacencyList[0][1]->source->distance = 0;
  // this is hurting my brain
  bool relaxedEdge = true;

  for (int i = 1; i < numNodes; i++) {
    for (int j = 0; j < adjacencyList[i].size(); j++) {
      int distFrom = adjacencyList[i][j]->source->distance;
      int distTo = adjacencyList[i][j]->destination->distance;
      int weight = adjacencyList[i][j]->weight;
      cout << "f" << distFrom << "t"<< distTo << "w" << weight << endl;
      if( distFrom + weight < distTo ) {
        distTo = distFrom + weight; //set new best path
        cout << "t" << distTo << endl;
      }
    }
  }
  cout << "done" << endl;
}

int main(){  
    //get the number of nodes and number of edges from cin separated by a space
    int numNodes = -1, numEdges = -1;
    cin >> numNodes >> numEdges;

    //add the nodes to an adjacency list
    //in this case, adjacencyList[i] is a vector of all edges leaving adjacencyList[i]
    //note that adjacencyList[0] is a list of self loops representing all nodes in the graph
    //these are not actual edges in the graph, just a way to keep track of all nodes
    //Furthermore, adjacencyList[0][0] is a dummy edge with a dummy node
    //this means that adjacencyList[0][i] represents the node with id i where ids start at 1
    vector<vector<shared_ptr<Edge>>> adjacencyList(numNodes+1);
    adjacencyList[0].push_back(shared_ptr<Edge>(new Edge()));
    for (int i=1; i<numNodes+1; i++){
        shared_ptr<Node> node = shared_ptr<Node>(new Node());
        node->id = i;
        node->distance = INT_MAX;
        node->inSetI = false;
        node->visited = false;
        shared_ptr<Edge> edge = shared_ptr<Edge>(new Edge());
        edge->source = node;
        edge->destination = node;
        edge->weight = 0;
        adjacencyList[0].push_back(edge);
    }

    //get edges from cin and add them to the adjacency list
    //the start, end, and weight of a single edge are on the same line separated by spaces
    int startNode = -1, endNode = -1, edgeWeight = -1;
    for (int i=0; i<numEdges; i++){
        cin >> startNode >> endNode >> edgeWeight;
        shared_ptr<Edge> edge = shared_ptr<Edge>(new Edge());
        edge->source = adjacencyList[0][startNode]->source;
        edge->destination = adjacencyList[0][endNode]->destination;
        edge->weight = edgeWeight;
        adjacencyList[startNode].push_back(edge);
    }

    //find nodes belonging to the set I and print them out in ascending order
    vector<int> setI = findSetI(adjacencyList);
    sort(setI.begin(), setI.end());
    for (int i=0; i<(int)setI.size()-1; i++){
        cout << setI[i] << " ";
    }
    if (setI.size() > 1){ cout << setI[setI.size()-1] << endl; }

    return 0;
}