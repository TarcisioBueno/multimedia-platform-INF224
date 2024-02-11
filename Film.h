#ifndef FILM_H
#define FILM_H

#include <iostream>
#include "Video.h"

class Film : public Video
{
private:
    int *chapitres;
    int taille;

public:
    Film() : Video()
    {
        chapitres = nullptr;
        taille = 0;
    }
    Film(std::string nom, std::string nomDuFichier, int duree, int *chapitres, int taille) : Video(nom, nomDuFichier, duree), chapitres(new int[taille]), taille(taille)
    {
        for (int i = 0; i < taille; i++)
        {
            this->chapitres[i] = chapitres[i];
        }
    }
    ~Film()
    {
        delete[] chapitres;
    }

    Film(const Film &original) : Video(original), taille(original.taille) {
        chapitres = new int[taille];
        for(int i = 0; i < taille; i++){
            chapitres[i] = original.chapitres[i];
        }
    }

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
    int getNombreDeChapitres() const
    {
        return taille;
    }
};

#endif