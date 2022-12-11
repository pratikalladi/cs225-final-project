/**
 * @file main.cpp
 * Contains code to run main
 */

#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

#include "graph.h"
#include "ScanGraph.h"

using namespace std;

//prints possible options in a options vector
void print_options(vector<string> input) {
    
    cout << " | ";
    for(string s : input) {
        cout << s << " | ";
    }
    cout << endl;
}

//searches possible options vector to see if is valid, and to push for a validated option if one is not found. It modifies the original option until it is valid
void validate_option(vector<string> options, string& input) {

    bool option_found = false;

    while(option_found == false) {
        for(string s : options) {
            if(s == input) {
                option_found = true;
                return;
            }
        }
        //if a valid option is not found
        cout << "try again: please enter a valid option or type exit to exit the program" << endl;
        getline(cin, input); //update input

        if(input == "exit") {
            break;
        }
    }
}

//function to print the list of destinations of an airport such as printing direct destinations.
void print_destinations(unordered_map<string, Edge*> direct_destinations, unordered_map<string, Edge*> international_destinations) {
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout <<"domestic destinations: " << endl;
    for(auto pair : direct_destinations) {
        //only print if the destination is not international
        Edge* x = pair.second;
        Node* direct = x->dest;
        if(international_destinations.count(direct->id) == 0) {
            cout << direct->id <<"["<< direct->name<<"] "<<"("<< x->weight<<") " << ", ";
        }
    } cout << endl << endl;
    
    //print international destinations if there are any
    if(international_destinations.size() != 0) {
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout <<"international destinations: " << endl;
        for(auto pair : international_destinations) {
            //only print if the destination is not international
            Edge* x = pair.second;
            Node* direct = x->dest;
            cout << direct->id <<"["<< direct->name<<"] "<<"("<< x->weight<<") " << ", ";

        } cout << endl << endl;
    }

}

//function to print all indirect destinations from the vector generated by a BFS search.
void print_indirect(vector<pair<int, string>> indirect_destinations, Graph* data) {
    for(auto pair : indirect_destinations) {
        string id = pair.second;
        Node* curr = data->getNodeMap()[id];
        cout << id <<"["<< curr->name<<"]" << ", ";
    } cout << endl; 
}

//function to handle displaying airport details after a valid IATA code has been entered by the user
void airports_subprogram_handle_details(Graph *data, string id) {
    //get other information
    Node* info = data->getNodeMap()[id];
    cout << "-------------------------------["<< info->name <<"(" << id << ")"<< " info" <<"]---------------------------------------------------" <<endl;
    cout << endl << "This airport with code, " << id << ", has the full name: " << info->name << endl;
    cout << "It is located in: " << info->location_city <<", "<< info->location_country <<endl << endl;

    //find direct destinations

    auto all_connections = data->getEdgeNeighbors(id);
    unordered_map<string, Edge*> direct_destinations; //this is needed so no new duplicate destination is inserted
    unordered_map<string, Edge*> international_destinations; //vector storing unique international destination this is needed so no new duplicate destination is inserted
    for(Edge* x : all_connections) { //remove duplicate destinations which correspond to different airlines.
        direct_destinations.insert({x->dest->id, x});
        if(x->dest->location_country != info->location_country) { //if the destination and source airport
            international_destinations.insert({x->dest->id, x});
        }
    } 
    cout << "It has direct flights to " << direct_destinations.size() << " airports." << endl;
    if(international_destinations.size() != 0) { //if there are international destinations
        cout << "This airport has " << international_destinations.size() << " international flights." << endl;
    } else {
        cout << "This airport has no international flights." << endl;
    }
    

    //run BFS on current airport find the number of airports connected to this airport in some way and to find the number of connections available to this airport and the number of airports that are connected by only one connection or two flights. 
    vector<pair<int, string>> all_BFS_connections = data->BFS(id); //since all commerical airports are regarded as being connected, these airports are essentially all commerical airports in the world. It is found that the size of this does not depend on which airport is the origin, but the number of hops in a graph of course changes.
    vector<pair<int, string>> all_BFS_2_connections; 
    for(auto p : all_BFS_connections) {
        //add to it only if the number of hops is two
        if(p.first == 2) {
            all_BFS_2_connections.push_back({p.first, p.second});
        }
    }
    cout << "It has an indirect route with only one stopover to " << all_BFS_2_connections.size() << " additional airports." << endl;
    cout << "This airport can be used eventually to eventually reach all the " << all_BFS_connections.size() << " commerical airports around the world." << endl << endl;


    //print details if the user chooses
    string command;
    cout << "type y to see the list of direct destinations or type n to not see more." << endl;
    cin >> command;
    do {
        if(command == "n") { //no option
            break;
        } else if (command == "y") { //yes option
            print_destinations(direct_destinations, international_destinations);
            cout << endl;
            break;
        } else {
            cout << "invalid input: type y to see a list of destinations or type n to not see more." << endl;
            cin >> command;
        }
    } while(command != "y" || command != "n");

    cout << "type y to see the list of indirect routes with only one stopover or type n to not see more." << endl;
    cin >> command;
    do {
        if(command == "n") { //no option
            break;
        } else if (command == "y") { //yes option
            print_indirect(all_BFS_2_connections, data);
            cout << endl;
            break;
        } else {
            cout << "invalid input: type y to see a list of destinations or type n to not see more." << endl;
            cin >> command;
        }
    } while(command != "y" || command != "n");

    cout << endl << "airport information for " << id << " printed above ^" << endl << endl;
    cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
}

//handles the subprogram that allows airports to be searched and their destinations to be found. This is essentially a mini program of a similar format as the main
void airports_subprogram(Graph* data) {
    vector<string> options = {"code", "city", "exit", };

    bool program_finished = false; //sets if the program is finished or not
    while(!program_finished) {
        cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
        cout << "_______+++++++++++++++++++<^>+++++++++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "       FastPairFinders: Airport Search and Data" << endl;
        cout << "_______+++++++++++++++++++<*>+++++++++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "Find information about a certain airport: " << endl;
        cout << "Type a listed option to begin:\n" << endl;
        print_options(options); 
        cout << "\nHere, it is possible to search by either IATA code, or the city an airport is in, or exit to menu" << endl;

        string input;
        getline(cin, input); //update input
        validate_option(options, input); //exit sequence after input is validated

        if(input == "code") {
            string id;
            cout << "Enter an airport's IATA code, this should be a three letter code such as BOS (if the airport does not have an IATA code, please enter its 4 digit ICAO code): " <<endl;
            cin >> id;
            while(data->getNodeMap().count(id) == 0) {
                cout << "This airport code is not in our database, please try entering an airport's IATA/ICAO code again: " <<endl;
                cin >> id;
            }

            airports_subprogram_handle_details(data, id); //handle displaying options

            //asks to exit or not
            string command;
            cout << "press e to exit after viewing info" <<endl;
            cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e");
        }
        else if(input =="city") {
            string city;
            cout << "enter an airport's city location fully, (for example, JFK is in New York)" << endl;
            getline(cin, city);
            while(data->getCityToNodes().count(city) == 0) {
                cout << "Spelling is incorrect or this city is not in our database, please try entering an airport's city again, using proper capitalization: " <<endl;
                getline(cin, city);
            }

            auto list = data->getCityToNodes()[city];
            cout << "These cities have these airports. Choose one of the listed airport's IATA codes (3 letters in brackets) to continue: " << endl;
            for(Node* n : list) {
                cout << n->name << "[" << n->id << "]"<<", " << endl;
            }
            
            string id;
            cout << "enter one of the airport's IATA code, (this is the three letter code in brackets) " << endl;
            cin >> id;
            while(data->getNodeMap().count(id) == 0) {
                cout << "This airport code is not in our database, please try entering an airport's IATA/ICAO code again: " << endl;
                cin >> id;
            }
            //get other information
            
            airports_subprogram_handle_details(data, id); //handle displaying options

            //asks to exit or not
            string command;
            cout << "press e to exit after viewing info" <<endl;
            cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e");  
        }
        else if(input == "exit") {
            program_finished = true; //end the program if exit is typed
        }
    }
}

//handles the subprogram that allows flight connections to be found 
void flights_subprogram(Graph* data) {
    vector<string> options = {"code", "city", "exit", };
    

    bool program_finished = false; //sets if the program is finished or not
    while(!program_finished) {    
        cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
        cout << "_______+++++++++++++<^>+++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "       FastPairFinders: Find Flights" << endl;
        cout << "_______+++++++++++++<*>+++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "Find possible flights between two airports: " << endl;
        cout << "To exit to menu, type exit" << endl << endl;
        string id1;
        cout << "enter the starting airport's IATA code, (this should be a three letter code such as BOS) ";
        cout << "If you do not know an airport's IATA code, go to the search option in menu to get help by exiting to menu anytime" << endl;
        cin >> id1;
        while(data->getNodeMap().count(id1) == 0) {
            if(id1 == "exit") {
                program_finished = true; //end the program if exit is typed
                return;
            }
            cout << endl << "This airport code is not in our database, please try entering an airport's IATA/ICAO code again: " << endl;
            cout << "If you do not know an airport's IATA code, go to the search option in menu to get help by exiting to menu anytime" << endl;
            cin >> id1;
        }
        //get other information
        Node* info1 = data->getNodeMap()[id1];
        cout << "This airport is located in: " << info1->location_city <<", "<< info1->location_country <<endl << endl;


        string id2;
        cout << "enter the destination airport's IATA code, (this should be a three letter code such as JFK: ";
        cout << "If you do not know an airport's IATA code, go to the search option in menu to get help by exiting to menu anytime" << endl;
        cin >> id2;
        while(data->getNodeMap().count(id2) == 0 || id2 == id1) {
            if(id2 == "exit") {
                program_finished = true; //end the program if exit is typed
                return;
            }
            if (id2 == id1) {
                cout <<  "you have entered a the same destination airport as your origin airport." << endl;
                cout <<  "please enter another airport such as SFO" << endl;
                cin >> id2;
            } else {
                cout << endl << "This airport code is not in our database, please try entering an airport's IATA/ICAO code again: " << endl;
                cout << "If you do not know an airport's IATA code, go to the search option in menu to get help by exiting to menu anytime" << endl;
                cin >> id2;
            }
        }
        //get other information
        Node* info2 = data->getNodeMap()[id2];
        cout << "This airport is located in: " << info2->location_city <<", "<< info2->location_country <<endl << endl;

 
        //search for direct flights
        
        bool direct_flight_exists = false;
        //finding direct flights
        vector<Edge*> neighbors = data->getEdgeNeighbors(id1);
        for(Edge* n : neighbors) {
            if(n->dest->id == id2) {
                direct_flight_exists = true;
                //if a direct flight is found
                cout << "a direct flight has been found to your destination airport " << id2 << endl;
                cout << "The airline is : " << data->getAirlinesMap()[n->airline_code] << endl; 
                cout << "The flight distance in km is : " << n->weight << endl << endl; 
            }
        }

        //if no direct flight exists, run Dijkstra's
        if(!direct_flight_exists) {
            auto path = data->dijkstra_A_find_shortest_path(id1, id2);
            

            cout << "Starting at your origin airport, here is the shortest sequence of connecting flights and airline options:" << endl;
            //add the origin airport to the path
            path.insert(path.begin(), id1);

            //print out the shortest route and airline options in pairs
            for(unsigned int i = 0; i < path.size() - 1; i++ ) {
                cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                cout << "connection " << i + 1 << " :" << endl;
                //find the start and end nodes based on current index
                Node* start = data->getNodeMap()[ path[i] ];
                Node* end = data->getNodeMap()[ path[i+1] ];

                
                cout << start->id <<"["<< start->name<<"] "<<"("<< start->location_city <<") " << " -> ";
                cout << end->id <<"["<< end->name<<"] "<<"("<< end->location_city <<") " << endl;
                
                cout << "airlines flying this route: " << endl << endl;
                vector<Edge*> neighbors = data->getEdgeNeighbors(start->id);
                Edge * connecting = nullptr;
                for(Edge* n : neighbors) {
                    if(n->dest->id == end->id) {
                        cout << data->getAirlinesMap()[n->airline_code] << ", "; 
                        connecting = n;
                    }
                }
                cout << "flight distance in km is : " << connecting->weight << endl << endl; 
            }
            cout << endl; 
            cout << "The least amount of connections possible is: " << path.size() - 1 << endl;
        }

        string command;
        cout << "press e to exit after viewing info" <<endl;
        cin >> command;
        do {
            if(command == "e") {
                break;
            } else {
                cout <<"invalid option: type e to exit" << endl;
                cin >> command;
            }
        } while(command != "e");
    }
}

void data_subprogram(Graph* data) {
    cout << "loading data: " << endl;
    //loading in needed data
    vector<pair<unsigned int, string>> num_international_destinations; //stores the information as int to a string value id
    vector<pair<unsigned int, string>> num_total_destinations; //stores the information as int to a string value id
    vector<pair<unsigned int, string>> num_one_stop_destinations; //stores the number of destinations from each airport that is only one connection away but not a direct flight
    for(auto pair: data->getNodeMap()) { //interate through all nodes
        string current_id = pair.first;
        if(!data->getEdgeNeighbors(current_id).empty()) {        //only run on nodes that have neighbors
            auto all_connections = data->getEdgeNeighbors(current_id);
            string current_country = pair.second->location_country; //stores current country

            unordered_set<string> international_destinations; //this is needed so no new duplicate destination is inserted
            unordered_set<string> total_destinations; //this is needed so no new duplicate destination is inserted
            for(Edge* e : all_connections) { //remove duplicate destinations which correspond to different airlines.
                //if the the destinations country does not match the current country, add it
                if(e->dest->location_country != current_country) {
                    international_destinations.insert(e->dest->id); //maps by city
                }
                total_destinations.insert(e->dest->id); //add all
            } 
            
            //run BFS on current airport find the number of airports connected to this airport in some way and to find the number of connections available to this airport and the number of airports that are connected by only one connection or two flights. 
            vector<std::pair<int, string>> all_BFS_2_connections = data->BFS(current_id, 2); //since all commerical airports are regarded as being connected, these airports are essentially all commerical airports in the world. It is found that the size of this does not depend on which airport is the origin, but the number of hops in a graph of course changes.

            num_one_stop_destinations.push_back({all_BFS_2_connections.size(), current_id});
            num_international_destinations.push_back({international_destinations.size(), current_id});//append
            num_total_destinations.push_back({total_destinations.size(), current_id});
        }
    }
    sort(num_international_destinations.begin(), num_international_destinations.end(), greater<pair<int, string>>());//sort this output in descending order
    sort(num_total_destinations.begin(), num_total_destinations.end(), greater<pair<int, string>>());//sort this output in descending order
    sort(num_one_stop_destinations.begin(), num_one_stop_destinations.end(), greater<pair<int, string>>());

    vector<string> options = {"1","2","3","4","5","exit"}; //initial options
    vector<pair<string, double>> pr = data->PageRank(); //stores pagerank info

    bool program_finished = false; //sets if the program is finished or not
    while(!program_finished) {
        cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
        cout << "_______++++++++++++++++<^>++++++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "       FastPairFinders: Airport Statistics" << endl;
        cout << "_______++++++++++++++++<*>++++++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "Find information for the rankings of all major airports or a single airport: " << endl;
        cout << "Type the number of a listed option to begin:\n" << endl;
        cout << "|-------------(1)-------------|--------(2)----------|--------------------(3)-----------------|---------------(4)---------------|-------------(5)----------|-----(exit)----|" <<endl;
        cout << "|1: Find an Airport's PageRank|2: top 50 by PageRank|3: top 100 by international destinations|4: top 100 by total destinations |5: top 100 most connected |6: exit to menu|" <<endl << endl;

        cout <<"type exit to exit to menu" << endl;

        string input;
        getline(cin, input); //update input
        validate_option(options, input); //exit sequence after input is validated

        if(input == "1") {
            cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
            string id;
            cout << "enter an airport's IATA code, this should be a three letter code such as BOS (if the airport does not have an IATA code, please enter its 4 digit ICAO code): " <<endl;
            cin >> id;
            while(data->getNodeMap().count(id) == 0) {
                cout << "This airport code is not in our database, please try entering an airport's IATA/ICAO code again: " <<endl;
                cin >> id;
            }
            double pr_selection = data->PageRankofNode(id);
            int count = 0;
             pair<string, double> finder;
            for (unsigned i = 0; i < pr.size(); i++) {
                if (pr[i].first == id) {
                    count = i + 1;
                    finder = pr[i];
                    i = pr.size();
                }
            }

            cout << "Your selected airport, " << id << ", has a PageRank score of: " << finder.second << endl;
            cout << endl;
            cout << "This ranks it " << count << " out of " << pr.size() << " total airports." << endl << endl;

            //asks to exit or not
            string command; cout << "press e to exit after viewing info" <<endl; cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e"); 
        }
        else if(input =="2") {
            cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
            cout << "Listed below are the 50 most important airports in our dataset using our PageRank Algorithm: " << endl;
            cout << endl;

            cout << "Airport code and Name | PageRank" << endl; 
            for (unsigned i = 0; i < 50; i++) {
                Node* curr = data->getNodeMap()[pr[i].first];
                std::cout << "#"<<i+1<< ": "<<pr[i].first << "[" << curr->name << "] |"<< pr[i].second << std::endl;
            }

            //asks to exit or not
            string command; cout << "press e to exit after viewing info" <<endl; cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e"); 

        }
        else if(input == "3") {
            cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
            cout << "Listed below are the 100 top airports by number of direct international flights: " << endl;
            cout << endl;

            cout << "Airport code and Name | Number of international flights" << endl; 
            for (unsigned i = 0; i < 100; i++) {
                auto pair = num_international_destinations[i];
                Node* curr = data->getNodeMap()[pair.second];
                std::cout << "#"<<i+1<< ": "<< curr->id << "[" << curr->name << "] |"<< pair.first << std::endl;
            }

            //asks to exit or not
            string command; cout << "press e to exit after viewing info" <<endl; cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e"); 
        }
        else if(input == "4") {
            cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
            cout << "Listed below are the 100 top airports by number of direct flights: " << endl;
            cout << endl;

            cout << "Airport code and Name | Number of direct flights" << endl; 
            for (unsigned i = 0; i < 100; i++) {
                auto pair = num_total_destinations[i];
                Node* curr = data->getNodeMap()[pair.second];
                std::cout << "#"<<i+1<< ": "<< curr->id << "[" << curr->name << "] |"<< pair.first << std::endl;
            }
                        
            //asks to exit or not
            string command; cout << "press e to exit after viewing info" <<endl; cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e"); 
        }
        else if(input == "5") {
            cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
            cout << "Listed below are the 100 top airports by connectivity: " << endl;
            cout << "For each airport, its connectivity is the sum of the number of direct flights plus the number" << endl;
            cout << "of unique destinations that can reached with just one stopover." << endl;
            cout << endl;

            cout << "Airport code and Name | Connectivity" << endl; 
            for (unsigned i = 0; i < 100; i++) {
                auto pair = num_one_stop_destinations[i];
                Node* curr = data->getNodeMap()[pair.second];

                int connectivity = pair.first + data->getNodeNeighbors(curr->name).size(); 
                std::cout << "#"<<i+1<< ": "<< curr->id << "[" << curr->name << "] |"<< connectivity << std::endl;
            }
                        
            //asks to exit or not
            string command; cout << "press e to exit after viewing info" <<endl; cin >> command;
            do {
                if(command == "e") {
                    break;
                } else {
                    cout <<"invalid option: type e to exit" << endl;
                    cin >> command;
                }
            } while(command != "e"); 
        }
        else if(input == "exit") {
            program_finished = true; //end the program if exit is typed
        }
    }
}

int main()
{   
    string airlines_path ="../data/airlines.dat.txt";
    string airports_path ="../data/airports.dat";
    string flights_path = "../data/routes.dat";

    //scanning in data
    Graph* data = new Graph(airlines_path, airports_path, flights_path); //making new graph object

    //start of main programs
    vector<string> main_options = {"airports", "flights", "stats", "exit"};
    bool program_finished = false; //sets if the program is finished or not
    while(!program_finished) {
        string input;
        cout << "_______+++++++++++<^>++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "       Welcome to FastPairFinders" << endl;
        cout << "_______+++++++++++<*>++++++++++++________________________________________________________________________________________________________________________________" << endl;
        cout << "options:" << endl;
        cout << "type a listed option to begin:\n" << endl;
        print_options(main_options);
        cout << "\nhere, it is possible explore information about airports, find flights, get statistics such as the most important airports, or exit this program." << endl;
        getline(cin, input); //update input
        validate_option(main_options, input); //exit sequence after input is validated

        if(input == "airports") {
            airports_subprogram(data);
        } 
        else if(input == "flights") {
            flights_subprogram(data);
        } 
        else if(input == "stats") {
            //will display interesting statistics using pagerank and BFS algorithms
            data_subprogram(data);
        }

        else if(input == "exit") {
            delete data;
            program_finished = true; //end the program if exit is pushed
        }
    }

    return 0;
}