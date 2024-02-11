#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include "Base.h"

class Video : public Base
{
private:
    int duree;

public:
    Video() : Base("", ""), duree(0) {}
    Video(std::string nom, std::string nomDuFichier, int duree) : Base(nom, nomDuFichier), duree(duree) {}
    virtual ~Video(){}
    int getDuree() const
    {
        return duree;
    }
    void setDuree(int duree)
    {
        this->duree = duree;
    }

    virtual void afficher(std::ostream &os) const override
    {
        Base::afficher(os);
        os << "Durée: " << duree << std::endl;
    }

    // linux

    void jouer() const override
    {
        std::string argument = "mpv " + getNomDuFichier() + "&";
        system(argument.data());
    }
};

#endif