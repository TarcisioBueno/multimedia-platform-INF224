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

int main(int argc, const char *argv[])
{

// Create an instance of DataBase
    DataBase db;

    // Create multimedia objects and add them to the database
    db.creerPhoto("photo1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/picture1.jpg", 40.748817, -73.985428);
    db.creerVideo("video1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video1.mp4", 120);
    int chapters[] = {30, 30, 40};
    db.creerFilm("film1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video2.mp4", 100, chapters, 3);

    // Create a group and add it to the database
    db.creerGroupe("group1");

    // Search and display a multimedia object
    std::cout << "Searching for photo1:\n";
    db.rechercherMultimedia("photo1");

    // Search and display a group
    std::cout << "Searching for group1:\n";
    db.rechercherGroupe("group1");

    std::cout << "Searching for inexistent photo:\n";
    db.rechercherMultimedia("ddasf");
    /* // Play a multimedia object
    std::cout << "Playing video1:\n";
    db.jouer("video1"); */

    // Delete a multimedia object
    std::cout << "Deleting film1:\n";
    db.supprimer("film1");

    // Delete a group
    std::cout << "Deleting group1:\n";
    db.supprimer("group1");

    std::cout << "Deleting group1:\n";

    return 0;
}
