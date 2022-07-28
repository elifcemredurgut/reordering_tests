#include <iostream>
#include <string>
#include "zmq_server.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <list>


std::map<int, std::list<int>> mapOfIndices;
std::map<int, std::list<double>> movieRatings;
std::map<int, double> movieRatingAvg;

void printDoubleMap(std::map<int,std::list<double>>& mapOfList)
{
  
    std::cout << "   Key         Value"
         << "\n\n";
    for (auto p : mapOfList) {
        // Key is an integer
        int key = p.first;
  
        // Value is a list of integers
        std::list<double> ourList = p.second;
  
        std::cout << "   ";
        std::cout << key << "          ";
  
        // Printing list elements
        std::cout << "[ ";
        for (auto it = ourList.begin();
             it != ourList.end(); it++) {
            // Dereferencing value pointed by
            // iterator
            std::cout << (*it) << ' ';
        }
  
        std::cout << ']';
        std::cout << '\n';
    }
}

void printIntMap(std::map<int, std::list<int>>& mapOfList)
{
  
    std::cout << "   Key         Value"
         << "\n\n";
    for (auto p : mapOfList) {
        // Key is an integer
        int key = p.first;
  
        // Value is a list of integers
        std::list<int> ourList = p.second;
  
        std::cout << "   ";
        std::cout << key << "          ";
  
        // Printing list elements
        std::cout << "[ ";
        for (auto it = ourList.begin();
             it != ourList.end(); it++) {
            // Dereferencing value pointed by
            // iterator
            std::cout << (*it) << ' ';
        }
  
        std::cout << ']';
        std::cout << '\n';
    }
}


int main(){
    //after getting all data from clients

    std::ifstream ifs("knn_top10.txt");
    if(ifs){
        std::string content( (std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));
        //std::string c = content.substr(0, 10);
        std::stringstream ss(content);
        std::string line;
        //std::map<int, std::list<int> > mapOfIndices;

        while (std::getline(ss, line, '\n')) {
            std::string index;
            std::list<int> listOfIndices;

            std::size_t pos = line.find(","); //index of the first comma
            std::string indicesStr = line.substr(pos+1);  //rest of the line after the first element(userId)
            std::stringstream indicesStream(indicesStr);

            int userId = std::stoi(line.substr(0, pos));  //part of the line until the first comma
            

            while(std::getline(indicesStream, index, ',')){ 
                listOfIndices.push_back(std::stoi(index));
            }
            mapOfIndices[userId] = listOfIndices;
        }
        printIntMap(mapOfIndices);
    }
    else{
        std::cout << "Cannot open knn_top10.txt file!\n";
    }

    int port = 5555;
    ZmqServer zmq = ZmqServer();
    zmq.bind("tcp", port);
    std::cout << "Listening on " << port << std::endl;

    while(true){
        std::string socketID = zmq.receive().substr(4); //message format is client<ID>
        int userID = std::stoi(socketID);
        std::string msg = zmq.receive();
        
        //request for movie recommendations
        if(msg.substr(0,5) == "recom"){

            //iterate over the neighbors list
            for (auto n = mapOfIndices.at(userID).begin();
                n != mapOfIndices.at(userID).end(); n++) {
				zmq.sendmore("client"+std::to_string(*n));
                zmq.send("send"); //requesting user profiles
            }
        }
        //incoming user profiles replies
        else{
            //msg format: <movie1>:<rating1>,<movie2>:<rating2>,...
            std::stringstream msgStream(msg);
            std::string pair;

            //split the message by comma ","
            while(std::getline(msgStream, pair, ',')){ 
                std::size_t commaPos = pair.find(":");
                int movieID = std::stod(pair.substr(0, commaPos));
                double rating = std::stod(pair.substr(commaPos+1));

                if (movieRatings.count(movieID) == 0) { //if movie is not in the map
                    std::list<double> l;
                    l.push_back(rating);
                    movieRatings[movieID] = l; 
                } else {
                    movieRatings[movieID].push_back(rating);
                }
            }
            printDoubleMap(movieRatings);
        } 
    }

    //int userID; //user to be recommended movies

    return 0;
}