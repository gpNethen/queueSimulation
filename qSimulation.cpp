// \author Nathan Reichert
// \date Last Modified: Thursday January 17, 2019
// \brief The purpose of this program is to utilize a Queue class in a general representation simulating checkout lanes of a retail store

#include "Queue.h"
#include "Queue.cpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int shortest(int num, int serve[], Queue q[]);   ///<Prototype for function returning index of shortest line
int totalLeft(int num, Queue q[]); ///<Prototype for function returning total customers still waiting in all lines

int main()
{
	int largestWaitTime=0;      // Variable to hold the longest recorded wait time ('transaction time')
	int lineServeNum;           // Variable to hold the number of lines / servers ('checkout lanes')
	int DURATION;               // Variable to hold the desired duration (analogous to 'store hours')
	int ArrivProb;              // Variable to hold the % probability a customer will arrive per tick ('minute')
	int MaxTransTime;           // Variable to hold the maximum number of ticks ('minutes') a transaction will take
	int custCount=0;            // Variable to hold the total number of customers counted during the duration
	int entryTime;              // Variable to hold the time that a customer enters a queue
	int waitSum=0;              // Sum of the number of ticks customers spent waiting in line
	int seed;                   // Seed number for the pseudo-random number generating function
	
	// The following block of cout/cin statements gather input from the user for each of the respective variables as defined above
	cout << "Enter these parameters of the simulation:" << endl;
	cout << "\tThe number of lines/servers: ";
	cin >> lineServeNum;
	cout << "\tThe probability that a customer arrives in one tick(%): ";
	cin >> ArrivProb;
	cout << "\tThe maximum duration of a transaction in ticks: ";
	cin >> MaxTransTime;
	cout << "\tThe duration of the simulation in ticks: ";
	cin >> DURATION;
	cout << "Enter a random number seed: ";
	cin >> seed;
	
	int transTime[lineServeNum];                                            // Array of transaction times for each server's queue
	Queue line[lineServeNum];                                               // Array of queues (people waiting in line), number of queues based on number of servers
	
	for (int i=0; i<lineServeNum; ++i)                                      // Initialize all transaction times to zero
		transTime[i] = 0;
	
	for (int time=0; time<DURATION; ++time)                                 // For each tick ('minute') from 0 to the duration (end)
	{
		if(rand()%100<ArrivProb)                                            // If arrival probability is satisfied by pseudo-random number generated
			line[shortest(lineServeNum, transTime, line)].enqueue(time);    // Enqueue a customer at current corresponding time
		for (int i=0; i<lineServeNum; ++i)	                                // For each server / queue
		{
			if(transTime[i]==0)                                             // If the transaction time is up
			{
				if(!line[i].isEmpty())                                      // If the line is not yet empty
				{
					entryTime=line[i].dequeue();                            // Gets the time that the current customer began waiting in line
					waitSum+=time-entryTime;                                // Calculates the amount of time the customer waited in line, and adds it to the sum of wait time
					if (time-entryTime > largestWaitTime)                   // If the current customer waited longer than any other customer
						largestWaitTime = time-entryTime;                   // That customer's wait time becomes the new record for longest wait time
					++custCount;                                            // Incrememnt the total number of customers served
					transTime[i]=rand()%MaxTransTime+1;                     // Generates next pseudo-random transaction time
				}
			}
			else
				--transTime[i];                                             // If transaction time is not yet up, decrement transaction time by one tick (minute)
			cout << setw(3) << time << setw(3) << transTime[i] << "    " << line[i] << endl;     // Displays the current time (in ticks) and contents of respective queue
		}
		cout << endl;
	}
	
	// The following block of cout statements display statistics from the entire simulation
	cout << "Average ticks spent waiting: " << waitSum/custCount << endl;
	cout << "Total customers served: " << custCount << endl;
	cout << "Largest number of ticks a single customer waited: " << largestWaitTime << endl;
	cout << "Customers remaining in line at simulation end: " << totalLeft(lineServeNum, line) << endl;
}

// \pre Takes in an int, int array, and array of Queues
// \post Function that returns the index associated with the server with the shortest line
int shortest(int num, int serve[], Queue q[])
{
	if (num == 1)                                          // if only one line/server pair
		return 0;					                       // returns first index
	int smoll = serve[0]+q[0].size();                      // saves first wait time and line length
	int index = 0;                                         // and first index as default smallest
	for(int i=1; i<num; ++i)                               // For each of the servers
	{
		if ( smoll > serve[i]+q[i].size() )                // if not smallest line
		{
			smoll = serve[i]+q[i].size();                  // indicates size of the new smallest line
			index = i;                                     // saves that index (server) as the one with the smallest line
		}
	}
	return index;										   // Returns the index associated with the server with the smallest line
}

// \pre Takes in an int and an array of queues
// \post Function that returns the number of customers still in line at the end of the simulation
int totalLeft(int num, Queue q[])
{
	int customers = 0;                                     // Initialize variable for counting customers to zero
	for (int i=0; i<num; ++i)                              // For each index associated with a server's queue
		customers+=q[i].size();                            //adds length of every queue in array
	return customers;                                      //returns the total number of queue elements counted
}
