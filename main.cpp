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
const std::string MULTIMEDIA = "multimedia";
const std::string GROUP = "group";
const std::string SEARCH = "search";
const std::string PLAY = "play";
const std::string CREATE = "create";
const std::string DELETE_ = "delete";

void handleServerRequest(const std::string& request, std::string& response, DataBase& db) {
    std::cout << "request: " << request << std::endl;

    std::istringstream iss(request);
    std::string command, type, name;
    iss >> command >> type >> name;
    if (command == SEARCH) {
        if (type == MULTIMEDIA) {
            std::string message = db.rechercherMultimedia(name);
            response = "MULTIMEDIA ATTRIBUTES: " + message;
        } else if (type == GROUP) {
            std::string message = db.rechercherGroupe(name);
            std::cout << message << "######" ;
            response = "GROUP ATTRIBUTES: " + message;
        } else {
            response = "UNKNOWN TYPE";
        }
    } else if (command == PLAY) {
        name =  type;
        db.jouer(name);
        std::cout << name << std::endl;
        response = "PLAYING: " + name;
    } else {
        response = "UNKNOWN COMMAND";
    }
}

int main(int argc, const char *argv[]) {
    DataBase db;

    // Create multimedia objects and add them to the database
    auto photo1 = db.creerPhoto("photo1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/picture1.jpg", 40.748817, -73.985428);
    auto video1 = db.creerVideo("video1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video1.mp4", 120);
    int chapters[] = {30, 30, 40};
    auto film1 = db.creerFilm("film1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video2.mp4", 100, chapters, 3);
    auto film3 = db.creerFilm("film2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video2.mp4", 100, chapters, 3);
    auto group = db.creerGroupe("group1");

    // Save all multimedia objects to a file
    if (!db.saveAll("multimedia.txt")) {
        std::cerr << "Failed to save multimedia objects" << std::endl;
        return 1;
    }

    // Read all multimedia objects from the file
    if (!db.readAll("multimedia.txt")) {
        std::cerr << "Failed to read multimedia objects" << std::endl;
        return 1;
    }

    group->push_back(video1);
    group->push_back(photo1);
    group->push_back(film1);

    auto *server = new TCPServer([&](std::string const &request, std::string &response) {
        handleServerRequest(request, response, db);
        return true;
    });

    std::cout << "Starting Server on port " << PORT << std::endl;
    int status = server->run(PORT);
    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    return 0;
}