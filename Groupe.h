#ifndef GROUPE_H
#define GROUPE_H

#include <list>
#include "Base.h"

class Groupe : public std::list<Base*>
{
private:
    std::string nom;

public:
    Groupe(const std::string& nom) : std::list<Base*>() , nom(nom) {}

    std::string getNom() const
    {
        return nom;
    }

    void afficher(std::ostream &os) const
    {
        for (const Base* base : *this)
        {
            base->afficher(os);
        }
    }
};

#endif