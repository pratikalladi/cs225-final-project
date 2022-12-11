/**
 * @file main.cpp
 * Contains code to run main
 */

#include <unistd.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

#include "graph.h"
#include "algo.h"
#include "ScanGraph.h"
#include "BFS.h"

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
        cout << "try again: please enter a valid option" << endl;
        getline(cin, input); //update input

        if(input == "EXIT") {
            break;
        }
    }
}

//handles the subprogram that allows airports to be searched and their destinations to be found. This is essentially a mini program of a similar format as the main
void airports_subprogram(Graph* data) {
    vector<string> options = {"code", "city", "exit", };

    bool program_finished = false; //sets if the program is finished or not
    while(!program_finished) {
        cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
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
            //get other information
            Node* info = data->getNodeMap()[id];
            cout << "-------------------------------["<< info->name <<"(" << id << ")"<< " info" <<"]---------------------------------------------------" <<endl;
            cout << endl << "This airport with code, " << id << ", has the full name: " << info->name << endl;
            cout << "It is located in: " << info->location_city <<", "<< info->location_country <<endl << endl;

            cout << "It has direct flights (with distance in km) to these ";
            auto n1 = data->getEdgeNeighbors(id);
            unordered_map<string, Edge*> filteredMap1; //this is needed so no new duplicate destination is inserted
            for(Edge* x : n1) { //remove duplicate destinations which correspond to different airlines.
                filteredMap1.insert({x->dest->id, x});
            } 
            cout << filteredMap1.size() << " airports: " << endl;
            for(auto pair : filteredMap1) {
                Edge* x = pair.second;
                Node* direct = x->dest;
                cout << direct->id <<"["<< direct->name<<"] "<<"("<< x->weight<<") " << ", ";
            } cout << endl; 
            cout << endl << "airport information for " << id << " printed above ^" << endl;
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
            Node* info = data->getNodeMap()[id];
            cout << "-------------------------------["<< info->name <<"(" << id << ")"<< " info" <<"]---------------------------------------------------" <<endl;
            cout << endl << "This airport with code: " << id << " has the full name: " << info->name << endl;
            cout << "It is located in: " << info->location_city <<", "<< info->location_country <<endl << endl;

            cout << "It has direct flights (with distance in km) to these ";
            auto n1 = data->getEdgeNeighbors(id);
            unordered_map<string, Edge*> filteredMap1; //this is needed so no new duplicate destination is inserted
            for(Edge* x : n1) { //remove duplicate destinations which correspond to different airlines.
                filteredMap1.insert({x->dest->id, x});
            } 
            cout << filteredMap1.size() << " airports: " << endl;
            for(auto pair : filteredMap1) {
                Edge* x = pair.second;
                Node* direct = x->dest;
                cout << direct->id <<"["<< direct->name<<"] "<<"("<< x->weight<<") " << ", ";
            } cout << endl; 
            cout << endl << "airport information for " << id << " printed above ^" << endl;
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
        cout << "Find possible flights between two airports: " << endl << endl;
        cout << "To exit to menu, type exit" << endl;
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
    }
}

void data_subprogram(Graph* data) {

    vector<string> options = {"city", "most important", "exit", };
    vector<pair<string, double>> pr = data->PageRank();
    

    bool program_finished = false; //sets if the program is finished or not
    while(!program_finished) {
        cout <<"_______________________________________________________________________________________________________________________________________________________" << endl;
        cout << "Find the importance rank of different airports: " << endl;
        cout << "Type a listed option to begin:\n" << endl;
        print_options(options); 
        cout << "\nHere, it is possible to search by either IATA code, view the 50 most important airports by PageRank, or exit to menu" << endl;

        string input;
        getline(cin, input); //update input
        validate_option(options, input); //exit sequence after input is validated

        if(input == "code") {
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

        cout << "Your selected airport, " << id << " , has a PageRank score of: " << finder.second << endl;
        cout << "\n" << endl;
        cout << "This ranks it " << count << " out of " << pr.size() << " total airports." << endl;
        }

        else if(input =="city") {
            string city;
            cout << "Enter an airport's city location fully, (for example, JFK is in New York)" << endl;
            getline(cin, city);
            while(data->getCityToNodes().count(city) == 0) {
                cout << "Spelling is incorrect or this city is not in our database, please try entering an airport's city again, using proper capitalization: " <<endl;
                getline(cin, city);
            }

            for (unsigned i = 0; i < 51; i++) {
                std::cout << pr[i].first << " -> " << pr[i].second <<std::endl;
            }

        }
        else if(input == "exit") {
            program_finished = true; //end the program if exit is typed
        }
    }

    /* std::cout << "JFK -> " << data->PageRankofNode("JFK") << std::endl;
    std::cout << "LAX -> " << data->PageRankofNode("LAX") << std::endl;
    std::cout << "CMI -> " << data->PageRankofNode("CMI") << std::endl;
    std::cout << "BOS -> " << data->PageRankofNode("BOS") << std::endl; */
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
        cout << "Welcome to FastPairFinders:" << endl;
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