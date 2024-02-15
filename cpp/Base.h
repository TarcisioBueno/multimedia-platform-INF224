#ifndef BASE_H
#define BASE_H

#include <iostream>

class Base
{
private:
    std::string nom;
    std::string nomDuFichier;
protected:
    Base();
    Base(std::string nom, std::string nomDuFishier);  
    friend class DataBase;  
public:    
    virtual ~Base();
    std::string getNom() const;
    std::string getNomDuFichier() const;
    void setNom(std::string nom);
    void setNomDuFichier(std::string nomDuFichier);
    virtual void afficher(std::ostream &os) const;
    virtual void jouer() const = 0;

    virtual std::string className() const;
    virtual void write(std::ostream & f);
    virtual void read(std::istream & f);
};

#endif