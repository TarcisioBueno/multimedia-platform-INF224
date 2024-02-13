//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "Base.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Groupe.h"
#include "DataBase.h"
#include <memory>
#include <string>
#include <sstream>
#include "server/tcpserver.h"




const int PORT = 3331;

int main(int argc, const char *argv[])
{

    // cree le TCPServer
  auto* server =
  new TCPServer( [&](std::string const& request, std::string& response) {


    // the request sent by the client to the server
    std::cout << "request: " << request << std::endl;

    // Parse the command, the type, and the name from the request
    std::istringstream iss(request);
    std::string command, type, name;
    iss >> command >> type >> name;
    if (command == "SEARCH") {
        if (type == "multimedia") {
            // Search for the multimedia with the given name
            // and get its attributes
            std::string message = "Search multimedia";
            
            // The response that the server sends back to the client
            response = "MULTIMEDIA ATTRIBUTES: " + message;
        } else if (type == "group") {
            // Search for the group with the given name
            // and get its attributes
            std::string message = "Search groupe";

            // The response that the server sends back to the client
            response = "GROUP ATTRIBUTES: " + message;
        } else {
            // Unknown type
            response = "UNKNOWN TYPE";
        }
    } else if (command == "PLAY") {
        // Play the multimedia with the given name
        std::string message = "Play";

        // The response that the server sends back to the client
        response = "PLAYING: " + message;
    } else {
        // Unknown command
        response = "UNKNOWN COMMAND";
    }

    // return false would close the connecytion with the client
    return true;
  });


  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;

}
