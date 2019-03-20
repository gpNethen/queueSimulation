//Author: Nathan Reichert
//Last Updated: Tuesday January 22, 2019
//This is the header file for a queue data structure adapted from Dr. Bryant Julstrom's class notes for CSCI301

#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <iostream>
#include <cstring>

class Queue
{
	public: 
    	typedef int Item;                                 //Indicates data type for queue to hold
    	Queue( ) { front = rear = NULL; count = 0; }      //Default Constructor
    	~Queue( );                                        //Destructor
    	void enqueue ( Item entry );                      //Function to enqueue an item
    	Item dequeue ( );                                 //Function to dequeue an item
    	bool isEmpty( ) { return count == 0; }            //Inline function returning a boolean indicating if a queue is empty
    	int size ( ) { return count; }                    //Inline function returning the number of items currently in a queue
    	friend std::ostream& operator << ( std::ostream& outStr, const Queue& q );     //Operator overloading '<<' sending contents of queue to ostream
    	
	private:
    	struct Node                                       //Data structure Node representing each item in the queue, cointains typedef item and pointer to next node
    	{
    		Item data;                                    //Node struct has data of type Item
        	Node *next;                                   //Node struct has pointer to next node in queue
    	};
    	Node *front;                                      //Pointer to a node indicating the node that is at the front of the queue
    	Node *rear;                                       //Pointer to a node indicating the node that is at the rear of the queue
    	int count;                                        //Integer to indicate the current number of items held within the queue
    	Node* getNode( Item entry, Node* next );          //Function returning a node struct
};
#endif
