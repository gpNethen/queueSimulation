// \author: Nathan Reichert
// \date Last Modified: Wednesday January 23, 2019

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Queue.h"                                           //Header file 
using namespace std;

                                                             // Default constructor is inline.

Queue::~Queue( )                                             ///<Implementation of Deconstructor
{
	Node* temp;                                              //Temporary node pointer

    while ( front != NULL )                                  //While the queue's front pointer is not NULL
    {
    	temp = front;                                        //Temp node pointer points to same node as front pointer
    	front = front -> next;                               //Advances front pointer to point to next node in queue
    	delete temp;                                         //Deletes node associated with temp pointer
    }
}

// \pre Takes in item of typedef Item
// \post Enqueues item into Queue object
void Queue::enqueue ( Item entry )                           ///<Implementation of Function to enqueue an item
{
	if ( isEmpty() )                                         //If the queue contains no items
	{
    	rear = front = getNode(entry, NULL);                 //Both the front and rear pointers set to point to new node
    	++count;                                             //Increments the queue node count
	}
    else                                                     //If the queue contains at least one item
    {
    	rear->next = getNode(entry, NULL);                   //Rear node's next pointer set to new node created
    	rear = rear->next;                                   //Rear node set to new node, as it is now the one at the rear of the queue
    	++count;                                             //Increments the queue node count
    }
}

// \pre Queue object
// \post removes item from front of Queue object
Queue::Item Queue::dequeue()                                 ///<Implementation of Function to dequeue an item
{
	Node* temp;                                              //Initialize a temporary node pointer
	Item dequeued;                                           //Initialize item that is to be dequeued
	dequeued = front->data;                                  //Set dequeued item to the data of the front-most node
	temp = front;                                            //Set temp to point to the front node
	front = front->next;                                     //Advances front node pointer to the next node in queue
	delete temp;                                             //Deletes node that temp is pointing to
	if (front == NULL)                                       //If the only item in the queue has now been deleted (front points to NULL now)
		rear = NULL;                                         //Set the rear pointer to NULL as well
	--count;                                                 //Decrement the count of items in the queue
	return dequeued;                                         //Return the data from the node that was dequeued & deleted
}


// \pre Queue object
// \post cout contents of Queue object
ostream& operator << ( ostream& outStr, const Queue& q )     ///<Operator overloading '<<' to append q queue contents to outStr ostream
{
    Queue::Node *cursor;                                     //Initialize a temporary pointer to a node

    for ( cursor=q.front;                                    //FOR            Cursor points to front node, 
          cursor != NULL && cursor->next != NULL;                           //while cursor is not NULL AND pointer to next is also not NULL, advance cursor to next item after operation
          cursor=cursor->next )                                             //advance cursor to next item after operation
    	outStr << " " << cursor->data;                       //Append a space and the data of cursor's node to the ostream
    if ( cursor != NULL )                                    //If only one item in queue (right away or after a series of data already appended to the ostream)
    	outStr << " " << cursor->data;                       //Append a space and the data of cursor's node to the ostream

    return outStr;                                           //Returns entire ostream generated
}

// \pre Queue object
// \post returns pointer to a new node in Queue object
Queue::Node* Queue::getNode ( Item entry, Node* next )       ///<Implementation of function that returns a pointer to a newly created node
{
    Node *temp;                                              //Initializes temp pointer to a node

    temp = new Node;                                         //points temp to a new node
    temp->data = entry;                                      //sets data of temp's node to entry from function parameter
    temp->next = next;                                       //sets next pointer of temp's node to next from function parameter
    return temp;                                             //returns the temp pointer to the newly created node
}

