#pragma once
#include <vector>
#include "container.h"
#include "maths_library.h"

//forward declaration
class Application2D;

//forward declaration of connection
struct Connection;

/*
* class Node
*
* symbolic location that a pathfinding agent can move
* towards, links back to other nodes, automatically generated by BSPGenerator
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct Node
{
	Vector2 position; //position of the node
	std::vector<Connection> conns; //array of outgoing connections

	bool transversed = false;
	float carriedScore = 0.0f; //used by the pathfinder to represent the cost to move to the node given a starting point
};

/*
* class Connection
*
* demonstrates how nodes are connected by applying a cost to moving
* from one node to the other
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct Connection
{
	Node* destination; //ending node of the connection
	float cost = 0.0f; //distance between the two nodes (NOTE: this doesn't have to be the literal distance)
};

/*
* class Path
*
* holds an array of nodes that are linked together
* with distances, uses the array for pathfinding
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Path
{
public:

	std::vector<Node*> nodes; //list of nodes in the list

	/*
	* Path()
	* default constructor
	*/
	Path() {};

	/*
	* ~Path()
	* destructor, deletes all of the nodes
	*/
	~Path();

	/*
	* generateNodesRecursive
	*
	* recursively finds new pathfinding nodes and their connections
	* by examining all the subcontainers of a container
	*
	* @param Container* container - the container to examine
	* @param bool subLevel - indicates the current pass of the function is a subLevel
	* @param Node* prevNode - the previous node from iterations (subLevel tells the function if this needs to be used)
	* @returns void
	*/
	void generateNodesRecursive(Container * container, bool subLevel = false, Node* prevNode = {});

	/*
	* addOffset
	*
	* adds an offset to all node positions
	*
	* @param Vector2 offset - the vector to add
	* @returns void
	*/
	void addOffset(Vector2 offset);

	/*
	* scale
	*
	* multiplies all of the node's positions and distances
	* (multiplying two vectors also multiplys their distance by the same amount)
	*
	* @param float scalar - the amount to muliply everything by
	* @returns void
	*/
	void scale(float scalar);

	/*
	* resetNodes
	*
	* sets all the nodes as not transversed
	*
	* @returns void
	*/
	void resetNodes();

	/*
	* calculatePath
	*
	* uses dijkstra's algorithm to find the shortest path
	* between two nodes, returns nothing if there was no path
	* https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
	*
	* @param Node* begin - the node to start the search at
	* @param Node* end - the node to end the search on
	* @returns std::vector<Node*> - an ordered list of nodes that make up the path
	*/
	std::vector<Node*> calculatePath(Node* begin, Node* end);

	void render(Application2D* appPtr);
};