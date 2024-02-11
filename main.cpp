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

// Only to test the copy constructor
#include <assert.h>

int main(int argc, const char *argv[])
{

/*     // test question 5
    int count = 0;
    Base *tableau[6];

    tableau[count++] = new Photo("picture 1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/picture1.jpg", 640, 640);
    tableau[count++] = new Photo("picture 2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/pitcure2.jpeg", 640, 640);
    tableau[count++] = new Photo("picture 3", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/picture3.jpg", 640, 640);
    tableau[count++] = new Video("video 1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video1.mp4", 4);
    tableau[count++] = new Video("video 2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video2.mp4", 4);
    tableau[count++] = new Video("video 2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video3.mp4", 4);
    for (int i = 0; i < 6; i++)
    {
        tableau[i]->afficher(std::cout);
    }

    for (int i = 0; i < count; i++)
    {
        delete tableau[i];
    }

    // test quesiton 6

    // Create an array of chapters
    int chapters[] = {5, 10, 15, 20, 25};
    int size = sizeof(chapters) / sizeof(chapters[0]);

    // Create a Film object with the chapters
    Film film("Test Film", "test.mp4", 120, chapters, size);

    // Modify the original array
    chapters[0] = 100;

    // Get and display the chapters from the Film object
    int *filmChapters = film.getChapitres();
    int filmSize = film.getNombreDeChapitres();

    for (int i = 0; i < filmSize; i++)
    {
        std::cout << filmChapters[i] << " ";
    }

    std::cout << std::endl;

    // Clean up
    delete[] filmChapters;

    // Copy constructor test

    // Create an array of chapter lengths
    int Chapters1[] = {5, 10, 15};

    // Create a Film object
    Film original("Film 1", "film1.mp4", 30, Chapters1, 3);

    // Create a copy of the Film object
    Film copy = original;

    // Check that the copy has the same data as the original
    assert(copy.getNom() == original.getNom());
    assert(copy.getNomDuFichier() == original.getNomDuFichier());
    assert(copy.getDuree() == original.getDuree());
    assert(copy.getNombreDeChapitres() == original.getNombreDeChapitres());

    // Check that the Chapters1 in the copy are the same as in the original
    int *originalChapters1 = original.getChapitres();
    int *copyChapters1 = copy.getChapitres();
    for (int i = 0; i < original.getNombreDeChapitres(); i++)
    {
        assert(copyChapters1[i] == originalChapters1[i]);
    }

    // Check that the copy and the original are at different memory locations
    assert(&copy != &original);

    // Don't forget to delete the arrays returned by getChapitres()
    delete[] originalChapters1;
    delete[] copyChapters1;

    std::cout << "All tests passed.\n"; */

    // Testing question 9

    int count = 0;
    Base *tableau[7];

    tableau[count++] = new Photo("picture 1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/picture1.jpg", 640, 640);
    tableau[count++] = new Photo("picture 2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/pitcure2.jpeg", 640, 640);
    tableau[count++] = new Photo("picture 3", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/picture3.jpg", 640, 640);
    tableau[count++] = new Video("video 1", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video1.mp4", 4);
    tableau[count++] = new Video("video 2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video2.mp4", 4);
    tableau[count++] = new Video("video 2", "/mnt/c/Users/Usuario/Desktop/P2/INF224/multimedia/video3.mp4", 4); 
    
    int chapters[] = {5, 10, 15, 20, 25};
    int size = sizeof(chapters) / sizeof(chapters[0]);

    // Create a Film object with the chapters
    tableau[count++] = new Film("Test Film", "test.mp4", 120, chapters, size);

    // Création des groupes
    Groupe groupe1("Groupe1");
    Groupe groupe2("Groupe2");

    // Ajout des objets aux groupes
    groupe1.push_back(tableau[0]); 
    groupe1.push_back(tableau[1]); 
    groupe1.push_back(tableau[2]); 
    groupe1.push_back(tableau[3]);
    groupe1.push_back(tableau[4]);
    groupe1.push_back(tableau[5]);
    groupe1.push_back(tableau[6]);

    groupe2.push_back(tableau[0]); 
    groupe2.push_back(tableau[1]); 
    groupe2.push_back(tableau[2]); 
    groupe2.push_back(tableau[3]);
    groupe2.push_back(tableau[4]);
    groupe2.push_back(tableau[5]);
    groupe2.push_back(tableau[6]);

    // Affichage des groupes
    std::cout << "Groupe1:\n";
    groupe1.afficher(std::cout);
    std::cout << "\nGroupe2:\n";
    groupe2.afficher(std::cout);

       for (int i = 0; i < count; i++)
    {
        delete tableau[i];
    }

    return 0;
}
