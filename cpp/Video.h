#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include "Base.h"

class Video : public Base
{
private:
    int duree;

protected:
    Video() : Base("", ""), duree(0) {}
    Video(std::string nom, std::string nomDuFichier, int duree) : Base(nom, nomDuFichier), duree(duree) {}
    friend class DataBase;

public:
    virtual ~Video() {}
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
        os << "Durée: " << duree << "::";
    }

    // linux

    void jouer() const override
    {
        std::string argument = "mpv " + getNomDuFichier() + "&";
        system(argument.data());
    }

    std::string className() const override
    {
        return "Video";
    }

    void write(std::ostream &f)
    {
        Base::write(f); // Write the base attributes
        f << duree << '\n';
    }

    void read(std::istream &f)
    {
        Base::read(f); // Read the base attributes
        f >> duree;
    }
};

#endif