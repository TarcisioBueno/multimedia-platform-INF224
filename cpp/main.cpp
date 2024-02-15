/**
 * @file main.cpp
 * @brief Fichier principal du programme.
 *
 * Ce fichier contient la fonction principale `main` qui lance le serveur et gère les requêtes.
 * Il inclut les en-têtes nécessaires, définit les constantes et les variables globales,
 * et crée les objets multimédias et les ajoute à la base de données.
 * Il contient également la fonction `handleServerRequest` qui traite les requêtes du serveur.
 */


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
#include "tcpserver.h"

const int PORT = 3331; /**< Le numéro de port utilisé par le serveur. */
const std::string MULTIMEDIA = "multimedia"; /**< Le type de recherche pour les objets multimédias. */
const std::string GROUP = "group"; /**< Le type de recherche pour les groupes. */
const std::string SEARCH = "search"; /**< La commande de recherche. */
const std::string PLAY = "play"; /**< La commande de lecture. */
const std::string CREATE = "create"; /**< La commande de création. */
const std::string DELETE_ = "delete"; /**< La commande de suppression. */
const std::string LIST = "list"; /**< La commande de listage. */

/**
 * @brief Traite une requête du serveur.
 *
 * Cette fonction prend en paramètre une requête du serveur, une référence à une chaîne de caractères
 * pour stocker la réponse, et une référence à la base de données.
 * Elle analyse la requête, exécute la commande correspondante et met à jour la réponse.
 *
 * @param request La requête du serveur.
 * @param response La réponse à renvoyer au serveur.
 * @param db La base de données.
 */
void handleServerRequest(const std::string& request, std::string& response, DataBase& db) {
    // Analyse de la requête
    std::istringstream iss(request);
    std::string command, type, name;
    iss >> command >> type >> name;

    // Traitement de la requête
    if (command == SEARCH) {
        if (type == MULTIMEDIA) {
            std::string message = db.rechercherMultimedia(name);
            response = message;
        } else if (type == GROUP) {
            std::string message = db.rechercherGroupe(name);
            response = message;
        } else {
            response = "UNKNOWN TYPE";
        }
    } else if (command == PLAY) {
        name =  type;        
        response = db.jouer(name);;
    } else if (command == LIST) {
        response = db.listerMultimedia();
    } else {
        response = "UNKNOWN COMMAND";
    }
}

/**
 * @brief Fonction principale du programme.
 *
 * Cette fonction crée les objets multimédias, les ajoute à la base de données,
 * sauvegarde les objets multimédias dans un fichier, lit les objets multimédias à partir du fichier,
 * crée les groupes et les associe aux objets multimédias, puis lance le serveur.
 *
 * @param argc Le nombre d'arguments de la ligne de commande.
 * @param argv Les arguments de la ligne de commande.
 * @return Le code de sortie du programme.
 */
int main(int argc, const char *argv[]) {
    DataBase db;
    std::shared_ptr<Groupe> group1;
    std::shared_ptr<Groupe> group2;
    BasePointer photo1;
    BasePointer photo2;
    BasePointer photo3;
    BasePointer video1;
    BasePointer video2;
    BasePointer video3;
    BasePointer film1;
    BasePointer film2;
    BasePointer film3;

    // Création des objets multimédias et ajout à la base de données
    group1 = db.creerGroupe("group1");
    group2 = db.creerGroupe("group2");
    photo1 = db.creerPhoto("photo1", "./media/photo1.jpg", 40.748817, -73.985428);
    photo1 = db.creerPhoto("photo2", "./media/photo2.jpg", 40.748817, -73.985428);
    photo1 = db.creerPhoto("photo3", "./media/photo3.jpg", 40.748817, -73.985428);
    video1 = db.creerVideo("video1", "./media/video1.mp4", 120);
    video2 = db.creerVideo("video2", "./media/video2.mp4", 120);
    video3 = db.creerVideo("video3", "./media/video3.mp4", 120);
    int chapters[] = {30, 30, 40};
    film1 = db.creerFilm("film1", "./media/video1.mp4", 100, chapters, 3);
    film2 = db.creerFilm("film2", "./media/video2.mp4", 100, chapters, 3);
    film3 = db.creerFilm("film3", "./media/video3.mp4", 100, chapters, 3);

    // Sauvegarde des objets multimédias dans un fichier
    if (!db.saveAll("multimedia.txt")) {
        std::cerr << "Failed to save multimedia objects" << std::endl;
        return 1;
    }

    // Lecture des objets multimédias à partir du fichier
    if (!db.readAll("multimedia.txt")) {
        std::cerr << "Failed to read multimedia objects" << std::endl;
        return 1;
    }

    // Association des objets multimédias aux groupes
    group1->push_back(video1);
    group1->push_back(photo1);
    group1->push_back(film1);

    // Lancement du serveur
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