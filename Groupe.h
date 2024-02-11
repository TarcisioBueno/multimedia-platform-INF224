#ifndef GROUPE_H
#define GROUPE_H

#include <list>
#include "Base.h"
#include <memory>

using BasePointer = std::shared_ptr<Base>;
typedef std::shared_ptr<Base> BasePointer;


class Groupe : public std::list<BasePointer>
{
private:
    std::string nom;

public:
    Groupe(const std::string& nom) : std::list<BasePointer>() , nom(nom) {}
    ~Groupe(){std::cout << "Groupe destructor was called!" << std::endl;}

    std::string getNom() const
    {
        return nom;
    }

    void afficher(std::ostream &os) const
    {
        for (const BasePointer& base : *this)
        {
            base->afficher(os);
        }
    }
};

#endif