/**
 * @file Base.cpp
 * @brief Implémentation de la classe Base
 */

#include "Base.h"
#include <iostream>

/**
 * @brief Constructeur par défaut de la classe Base
 */
Base::Base() : nom(""), nomDuFichier("")
{
}

/**
 * @brief Constructeur de la classe Base
 * @param nom Le nom de la base
 * @param nomDuFichier Le nom du fichier de la base
 */
Base::Base(std::string nom, std::string nomDuFichier) : nom(nom), nomDuFichier(nomDuFichier) {}

/**
 * @brief Destructeur de la classe Base
 */
Base::~Base(){};

/**
 * @brief Obtient le nom de la base
 * @return Le nom de la base
 */
std::string Base::getNom() const
{
    return nom;
}

/**
 * @brief Obtient le nom du fichier de la base
 * @return Le nom du fichier de la base
 */
std::string Base::getNomDuFichier() const
{
    return nomDuFichier;
}

/**
 * @brief Définit le nom de la base
 * @param nom Le nom de la base
 */
void Base::setNom(std::string nom)
{
    this->nom = nom;
}

/**
 * @brief Définit le nom du fichier de la base
 * @param nomDuFichier Le nom du fichier de la base
 */
void Base::setNomDuFichier(std::string nomDuFichier)
{
    this->nomDuFichier = nomDuFichier;
}

/**
 * @brief Affiche les informations de la base
 * @param os Le flux de sortie
 */
void Base::afficher(std::ostream &os) const
{
    os << "Nom: " << nom << "::" << "Nom du fichier: " << nomDuFichier << "::";
}

/**
 * @brief Obtient le nom de la classe
 * @return Le nom de la classe
 */
std::string Base::className() const {
    return "Base";
}

/**
 * @brief Écrit les informations de la base dans un flux
 * @param f Le flux de sortie
 */
void Base::write(std::ostream & f) {
    f << nom << '\n' << nomDuFichier << '\n';
}

/**
 * @brief Lit les informations de la base à partir d'un flux
 * @param f Le flux d'entrée
 */
void Base::read(std::istream & f){
    f >> nom >> nomDuFichier;
}