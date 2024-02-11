#include "Base.h"
#include <iostream>

Base::Base() : nom(""), nomDuFichier("")
{
}

Base::Base(std::string nom, std::string nomDuFichier) : nom(nom), nomDuFichier(nomDuFichier) {}

Base::~Base(){};

std::string Base::getNom() const
{
    return nom;
}

std::string Base::getNomDuFichier() const
{
    return nomDuFichier;
}

void Base::setNom(std::string nom)
{
    this->nom = nom;
}

void Base::setNomDuFichier(std::string nomDuFichier)
{
    this->nomDuFichier = nomDuFichier;
}

void Base::afficher(std::ostream &os) const
{
    os << "Nom: " << nom << "\nNom du fichier: " << nomDuFichier << std::endl;
}