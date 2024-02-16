/**
 * @file RequestHandler.h
 * @brief Fichier d'en-tête pour la gestion des requêtes du serveur.
 *
 * Ce fichier contient la fonction `handleServerRequest` qui traite les requêtes du serveur.
 * Il inclut les en-têtes nécessaires, définit les constantes pour les types de commandes, et fournit la fonction
 * pour analyser la requête, exécuter la commande correspondante et mettre à jour la réponse.
 */


#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <sstream>
#include "DataBase.h"

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
inline void handleServerRequest(const std::string& request, std::string& response, DataBase& db) {
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

#endif // REQUESTHANDLER_H