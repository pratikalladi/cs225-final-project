## Leading Question

    The leading question of this project is what's the shortest path (by miles) to get from one airport to another? To answer this we will use the Open Flights dataset. We will also give the option to filter by specific airlines as to appease frequent flyers who might have a favorite airline.

## Dataset Acquisition
	The dataset we plan on using is the Open Flights Dataset. We plan on using the "airpots.dat" dataset that include the name of specific airports as well as their location. We will also use the "routes.dat" dataset which includes the routes from each airport including the airline and plane that was flown. 

## Data Format
	We plan on reading in our dataset(s) as csv or txt files. Each input in the "airports.dat" dataset will be turned into a node on our graph, with its unique identifier, name, city, and location (latitude/longitude) included. Each edge in our graph will be an entry from the "routes.dat" dataset with the airline code, source airport, destination airport, and number of stops included.

## Data Correction
	We will filter out invalid entries and airlines that do not exist anymore. Additionally, we will check to see if all airports from "routes.dat" appear in the "airports.dat" dataset. If not, the program will throw an error.

## Data Storage
    We plan on using one dimensional vectors with space complexity of O(n) and two dimensional vectors with space complexity of O(n^2) to store the graph information and structs with a runtime of O(n) (because we only plan on using primitive data types) to store each product's information.

## Algorithm
	We will use Breadth First Search which has a runtime of O(n) to create the graph. We will create the graph using distance as the weight between nodes. The input to this algorithm will be the airports and routes dataset. Out output from this BFS search will be a graph with airports at its nodes and edges being the different routes. We will be using Dijkstra's algorithm for finding the shortest path between two airports. This has a run time of O(n^2) where n is the number of vertices in the graph. The input for Djikstra's would be two airports. The output from this algorithm would be a vector of flight routes which is the shortest way to travel between the two airports. For our third algorithm, we will filter the flights by distinct airlines and use A* on the filtered routes.

    A* uses a heuristic to calculate the current node's distance from both the start and end node. Therefore, we would likely need a function to calculate the distance between two nodes based on each airport's longitude and latitude. However, since flights don't often happen consecutively, we should include an extra heuristic that counts to total nodes traveled. The expected inputs would be a filtered vector list of graph nodes and the expected output would be a vector list of airports that we should travel to for the shortest path.

## Timeline
	We have 4 major components to complete for our project. These are creating the air route graph using BFS, implementing Dijkstra's Algorithm to find the shortest route, using A* to filter these routes by specific airlines for frequent flyers, and creating our test cases. Below is our plan to complete this work.

11/04/22 - 11/11/22 Set up classes and files for project and complete Makefile
11/11/22 - 11/18/22 Use BFS to create our graph and import route data, start Djikstra's algorithm
11/18/22 - 11/25/22 Thanksgiving BREAK (Work only if needed)
11/25/22 - 12/02/22 Finish Djikstra's algorithm, work on A* and filtering by airline
12/02/22 - 12/08/22 Finish A*, write test cases and record final presentation
