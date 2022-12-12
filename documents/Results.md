# Written Report - FastPairFinders
***
## Graph

Our graph consists of a ScanGraph class which reads the incoming dataset of routes, airports, and airline information and creates a graph. We utilize the SplitString function for mp_schedule to split each line of the CSV into readable parts. We have a Node struct object and an Edge struct object which hold each airport and flight routes respectively. The node holds the airport id. The graph is implemented with an adjacency list. Basic information of the graph, such as which nodes connect to which nodes with what edges, is stored in hash tables. This allows implemented helper functions to have a relatively fast run time. For example, the key helper functions that allow all the node neighbors and edge connections of a node to be found all have, on average, constant time access. The algorithms implemented use these helper functions to complete the intended tasks. The data for the airlines is also loaded in so that each flight’s data point, which contains an airline code specific to the OpenFlights database, can be found.

***

## Algorithms

### BFS

BFS was implemented to take in a starting node, which represents an airport, and a number that represents the maximum number of connecting airports wanted, and return a vector of all airports in which someone could fly to within the number of connecting flights. This would be useful if the user wanted to see how many and which airports they could fly to from a certain airport and allows them to expand their search by adjusting the number of connecting flights they are willing to fly. In the main program, BFS is used to find the destinations from an airport that can be reached with one stopover.  Our base BFS function is still available and it takes in the string name of the airport and returns all of the connections. The test cases made sure that cycles in the graphs would not cause infinite loops or other problems and to make sure the levels of the node are correct for a given input.

### Dijkstra’s

Dijkstra’s algorithm was implemented so that users would be able to find the shortest path by distances between any two airports. This allows users to find, what in most cases, should be the best connecting flights to get between two airports if a direct flight cannot be found. There are three implementations of Dijkstra’s algorithm in this program. The implementation of Dijkstra’s algorithm that is the most commonly called in this project outputs a vector of the string IATA codes of the airports traveled, in order to reach the destination airport from the origin. This allows the path to be found between two airports. Another implementation of Dijkstra’s algorithm only finds the shortest distance (as a double value) between two airports. This is used in the program to find  the shortest distance between two airports after the path has been found. For testing purposes, the most common version of Dijkstra’s algorithm is also implemented in the project, which outputs a map of the shortest distance to each node from any given source node. This essentially allows the shortest numerical distance to be found between all nodes and a certain origin node. 

### PageRank
	
PageRank was implemented so that users would be able to see the most important and connected airports in our dataset. This can be useful for traveling purposes, for example picking a vacation destination that is popular. Our PageRank implementation outputs a vector of pairs, with the first item in the pair being the airport, and the second being the calculated PageRank score. Our PageRank algorithm determines importance by the number of incoming routes divided by the number of outgoing flights. This was done to emphasize airports with a large number of incoming flights, as that would suggest a popular destination, rather than one that has many incoming and outgoing flights, which usually correlates to hub airports whose only importance may be geographical location. Additionally, we add a distance factor into our algorithm to emphasize airports with longer routes, as direct flights from far away airports are usually a sign of destination importance. The most important airport based in our dataset turned out to be London Heathrow, followed by Atlantsa Hartsfield-Jackson. This makes sense as Heathrow is often the gateway airport to Europe, and Hartsfield-Jackson is often the busiest airport in the world.

The tests we performed on our PageRank algorithm include a test to make sure the number of PageRank airports in the vector is the same as the amount of airports in the entire graph, ensuring that each airport gets a PageRank score. Additionally, we created a small dataset to test whether the airport with the most flights would be ranked the most important, which it was.
***

## Conclusions

Our original question was what’s the shortest path (by miles) to get from one airport to another? We achieved our goals and much more. Using Dijkstra's, a user can use our program to find the shortest path between airports. Additionally, they can see airports measured by importance using our PageRank algorithms and other metrics. Finally, they can also calculate what places they can fly to nonstop from their current place. Using BFS, they can see what single-layover destinations exist as well.
	
We discovered that BFS allows you to create one-layover flights with ease, and that using PageRank to rank airports leads to the most important ones being gateway airports such as Heathrow and Hartsfield-Jackson, not vacation spots such as JFK or LAX. Although, they are still near the top of the list. Using Djikstra’s, we found that sometimes the shortest flight path requires you to make hops to airports most people have never heard of. We also discovered how to implement the Haversine formula, an easy method of calculating distances from longitude and latitude. This was used for PageRank and Djikstra’s.
	
However, in the end we answered our original question and made a program that travelers can use to make planning their next trip a little easier.
