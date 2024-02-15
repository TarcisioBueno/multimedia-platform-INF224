/**
 * @file Film.h
 * @brief Ce fichier contient la classe Film, qui représente un film héritant de la classe Video.
 */

#ifndef FILM_H
#define FILM_H

#include <iostream>
#include "Video.h"

/**
 * @class Film
 * @brief Classe représentant un film héritant de la classe Video.
 *
 * Cette classe représente un film avec des chapitres.
 * Elle hérite des attributs et méthodes de la classe Video.
 */
class Film : public Video
{
private:
    int *chapitres; /**< Tableau des chapitres du film */
    int taille;     /**< Taille du tableau des chapitres */

    /**
     * @brief Constructeur de copie privé.
     * @param original Le film original à copier.
     */
    Film(const Film &original) : Video(original), taille(original.taille)
    {
        chapitres = new int[taille];
        for (int i = 0; i < taille; i++)
        {
            chapitres[i] = original.chapitres[i];
        }
    }

public:
    /**
     * @brief Constructeur de Film.
     * @param nom Le nom du film.
     * @param nomDuFichier Le nom du fichier du film.
     * @param duree La durée du film.
     * @param chapitres Le tableau des chapitres du film.
     * @param taille La taille du tableau des chapitres.
     */
    Film(std::string nom, std::string nomDuFichier, int duree, int *chapitres, int taille) : Video(nom, nomDuFichier, duree), chapitres(new int[taille]), taille(taille)
    {
        for (int i = 0; i < taille; i++)
        {
            this->chapitres[i] = chapitres[i];
        }
    }

    /**
     * @brief Constructeur par défaut de Film.
     */
    Film() : Video()
    {
        chapitres = nullptr;
        taille = 0;
    }

    /**
     * @brief Destructeur de Film.
     */
    ~Film()
    {
        delete[] chapitres;
    }

    /**
     * @brief Définit les chapitres du film.
     * @param chapitres Le tableau des chapitres du film.
     * @param taille La taille du tableau des chapitres.
     */
    void setChapitres(int *chapitres, int taille)
    {
        delete[] this->chapitres;
        this->chapitres = new int[taille];
        for (int i = 0; i < taille; i++)
        {
            this->chapitres[i] = chapitres[i];
        }
        this->taille = taille;
    }

    /**
     * @brief Récupère les chapitres du film.
     * @return Un pointeur vers une copie du tableau des chapitres du film.
     */
    int *getChapitres() const
    {
        if (chapitres == nullptr)
            return nullptr;
        else
        {
            int *copy = new int[taille];
            for (int i = 0; i < taille; i++)
            {
                copy[i] = chapitres[i];
            }
            return copy;
        }
    }

    /**
     * @brief Récupère le nombre de chapitres du film.
     * @return Le nombre de chapitres du film.
     */
    int getNombreDeChapitres() const
    {
        return taille;
    }

    /**
     * @brief Affiche les informations du film.
     * @param os Le flux de sortie.
     */
    void afficher(std::ostream &os) const override
    {
        Video::afficher(os);
        os << "Durée des chapitres: ";
        for (int i = 0; i < taille; i++)
        {
            os << chapitres[i] << " ";
        }
        os << "::";
    }

    /**
     * @brief Récupère le nom de la classe Film.
     * @return Le nom de la classe Film.
     */
    std::string className() const override
    {
        return "Film";
    }

    /**
     * @brief Écrit les attributs du film dans un flux de sortie.
     * @param f Le flux de sortie.
     */
    void write(std::ostream &f)
    {
        Video::write(f); // Écrit les attributs de base
        f << taille << '\n';
        for (int i = 0; i < taille; i++)
        {
            f << chapitres[i] << ' ';
        }
        f << '\n';
    }

    /**
     * @brief Lit les attributs du film à partir d'un flux d'entrée.
     * @param f Le flux d'entrée.
     */
    void read(std::istream &f)
    {
        Video::read(f); // Lit les attributs de base
        f >> taille;
        delete[] chapitres;
        chapitres = new int[taille];
        for (int i = 0; i < taille; i++)
        {
            f >> chapitres[i];
        }
    }
};

#endif
