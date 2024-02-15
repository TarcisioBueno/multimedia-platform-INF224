/**
 * @file Video.h
 * @brief Ce fichier contient la classe Video, qui représente un objet vidéo avec une durée spécifique.
 */

#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include "Base.h"

/**
 * @brief La classe Video représente un objet vidéo.
 * 
 * Elle hérite de la classe Base et ajoute une durée spécifique à la vidéo.
 */
class Video : public Base
{
private:
    int duree; /**< La durée de la vidéo en secondes. */

protected:
    /**
     * @brief Constructeur par défaut de la classe Video.
     * 
     * Initialise les attributs de la classe avec des valeurs par défaut.
     */
    Video() : Base("", ""), duree(0) {}

    /**
     * @brief Constructeur de la classe Video.
     * 
     * @param nom Le nom de la vidéo.
     * @param nomDuFichier Le nom du fichier de la vidéo.
     * @param duree La durée de la vidéo en secondes.
     */
    Video(std::string nom, std::string nomDuFichier, int duree) : Base(nom, nomDuFichier), duree(duree) {}

    friend class DataBase;

public:
    /**
     * @brief Destructeur virtuel de la classe Video.
     */
    virtual ~Video() {}

    /**
     * @brief Obtient la durée de la vidéo.
     * 
     * @return La durée de la vidéo en secondes.
     */
    int getDuree() const
    {
        return duree;
    }

    /**
     * @brief Définit la durée de la vidéo.
     * 
     * @param duree La durée de la vidéo en secondes.
     */
    void setDuree(int duree)
    {
        this->duree = duree;
    }

    /**
     * @brief Affiche les informations de la vidéo.
     * 
     * @param os Le flux de sortie.
     */
    virtual void afficher(std::ostream &os) const override
    {
        Base::afficher(os);
        os << "Durée: " << duree << "::";
    }

    /**
     * @brief Joue la vidéo en utilisant le lecteur par défaut du système.
     */
    void jouer() const override
    {
        std::string argument = "mpv " + getNomDuFichier() + "&";
        system(argument.data());
    }

    /**
     * @brief Obtient le nom de la classe Video.
     * 
     * @return Le nom de la classe Video.
     */
    std::string className() const override
    {
        return "Video";
    }

    /**
     * @brief Écrit les attributs de la vidéo dans un flux de sortie.
     * 
     * @param f Le flux de sortie.
     */
    void write(std::ostream &f)
    {
        Base::write(f); // Écrit les attributs de la classe de base
        f << duree << '\n';
    }

    /**
     * @brief Lit les attributs de la vidéo à partir d'un flux d'entrée.
     * 
     * @param f Le flux d'entrée.
     */
    void read(std::istream &f)
    {
        Base::read(f); // Lit les attributs de la classe de base
        f >> duree;
    }
};

#endif