/**
 * @file Photo.h
 * @brief Ce fichier contient la classe Photo, qui représente une photo avec des coordonnées géographiques.
 */

#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include "Base.h"

/**
 * @brief La classe Photo représente une photo avec des coordonnées géographiques.
 * 
 * Elle hérite de la classe Base et ajoute les attributs latitude et longitude.
 */
class Photo : public Base
{
private:
    double latitude; /**< La latitude de la photo. */
    double longitude; /**< La longitude de la photo. */

    /**
     * @brief Constructeur par défaut de la classe Photo.
     * 
     * Initialise les attributs avec des valeurs par défaut.
     */
    Photo() : Base("", ""), latitude(0), longitude(0) {}

    /**
     * @brief Constructeur de la classe Photo.
     * 
     * @param nom Le nom de la photo.
     * @param nomDuFichier Le nom du fichier de la photo.
     * @param latitude La latitude de la photo.
     * @param longitude La longitude de la photo.
     */
    Photo(std::string nom, std::string nomDuFichier, double latitude, double longitude) : Base(nom, nomDuFichier), latitude(latitude), longitude(longitude) {}

    friend class DataBase;

public:
    /**
     * @brief Destructeur de la classe Photo.
     */
    ~Photo() {}

    /**
     * @brief Obtient la latitude de la photo.
     * 
     * @return La latitude de la photo.
     */
    double getLatitude() const
    {
        return latitude;
    }

    /**
     * @brief Obtient la longitude de la photo.
     * 
     * @return La longitude de la photo.
     */
    double getLongitude() const
    {
        return longitude;
    }

    /**
     * @brief Définit la latitude de la photo.
     * 
     * @param latitude La latitude de la photo.
     */
    void setLatitude(double latitude)
    {
        this->latitude = latitude;
    }

    /**
     * @brief Définit la longitude de la photo.
     * 
     * @param longitude La longitude de la photo.
     */
    void setLongitude(double longitude)
    {
        this->longitude = longitude;
    }

    /**
     * @brief Affiche les informations de la photo.
     * 
     * @param os Le flux de sortie.
     */
    void afficher(std::ostream &os) const override
    {
        Base::afficher(os);
        os << "Latitude: " << latitude << "::" << " Longitude: " << longitude << "::";
    }

    // Linux

    /**
     * @brief Joue la photo en utilisant le logiciel imagej.
     */
    void jouer() const override
    {
        std::string argument = "imagej " + getNomDuFichier() + "&";
        system(argument.data());
    }

    /**
     * @brief Obtient le nom de la classe Photo.
     * 
     * @return Le nom de la classe Photo.
     */
    std::string className() const override
    {
        return "Photo";
    }

    /**
     * @brief Écrit les attributs de la photo dans un flux de sortie.
     * 
     * @param f Le flux de sortie.
     */
    void write(std::ostream &f)
    {
        Base::write(f); // Écrit les attributs de la classe de base
        f << latitude << '\n'
          << longitude << '\n';
    }

    /**
     * @brief Lit les attributs de la photo à partir d'un flux d'entrée.
     * 
     * @param f Le flux d'entrée.
     */
    void read(std::istream &f)
    {
        Base::read(f); // Lit les attributs de la classe de base
        f >> latitude >> longitude;
    }
};

#endif