## Leading Question

	The leading question of this project is what's the shortest path (by miles) to get from one airport to another? To answer this we will use the Open Flights dataset. We will also give the option to specify a certain layover airport in between the starting airport and destination airport.

## Dataset Acquisition
	The dataset we plan on using is the Open Flights Dataset. We plan on using the "airpots.dat" dataset that include the name of specific airports as well as their location. We will also use the "routes.dat" dataset which includes the routes from each airport including the airline and plane that was flown. 

## Data Format
	We plan on reading in our dataset(s) as csv or txt files. Each input in the "airports.dat" dataset will be turned into a node on our graph, with its unique identifier, name, city, and location (latitude/longitude) included. Each edge in our graph will be an entry from the "routes.dat" dataset with the airline code, source airport, destination airport, and number of stops included.

## Data Correction
	We will filter out invalid entries and airlines that do not exist anymore. Additionally, we will check to see if all airports from "routes.dat" appear in the "airports.dat" dataset. If not, the program will throw an error.

## Data Storage
	We plan on using one dimensional vectors with space complexity of O(n) and two dimensional vectors with space complexity of O(n^2) to store the graph information and structs with a runtime of O(n) (because we only plan on using primitive data types) to store each product's information.

## Algorithm
	We will use Breadth First Search which has a runtime of O(n) to create the graph. We will create the graph using distance as the weight between nodes. The input to this algorithm will be the airports and routes dataset. Our output from this BFS search will be a graph with airports at its nodes and edges being the different routes. We will be using Dijkstra's algorithm for finding the shortest path between two airports. This has a run time of O((E+V)logV) where E is the number of edges in the graph and V is the number of vertices in the graph. The input for Djikstra's would be two airports. The output from this algorithm would be a vector of flight routes which is the shortest way to travel between the two airports. We plan on using the Landmark Path algorithm to figure out the optimal route from airport A to airport B given one or more layovers in other airports. If the Landmark Path algorithm is deemed too similar to Djikstra', an alternate algorithm we would use is PageRank. We would determine the "importance" of different airports as used by PageRank by the number of flights that visit a particular airport. PageRank has a runtime of O(n + m) where n is the number of nodes and m is the number of edges.
## Timeline
	We have 4 major components to complete for our project. These are creating the air route graph using BFS, implementing Dijkstra's Algorithm to find the shortest route, using the Landmark Path algorithm to find the flight path using one stop for frequent flyers, and creating our test cases. Below is our plan to complete this work.


11/04/22 - 11/11/22 Set up classes and files for project and complete Makefile
11/11/22 - 11/18/22 Use BFS to create our graph and import route data, start Djikstra's algorithm
11/18/22 - 11/25/22 Thanksgiving BREAK - work on Djikstra and finish
11/25/22 - 12/02/22 Work on and complete Landmark
12/02/22 - 12/08/22 Write additional test cases and record final presentation
