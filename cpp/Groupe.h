/**
 * @file Groupe.h
 * @brief Ce fichier contient la classe Groupe, qui représente un groupe d'objets de type Base.
 */

#ifndef GROUPE_H
#define GROUPE_H

#include <list>
#include "Base.h"
#include <memory>

using BasePointer = std::shared_ptr<Base>;
typedef std::shared_ptr<Base> BasePointer;

/**
 * @class Groupe
 * @brief Représente un groupe d'objets de type Base.
 *
 * Cette classe hérite de la classe std::list<BasePointer> et permet de stocker
 * un ensemble d'objets de type Base dans une liste.
 */
class Groupe : public std::list<BasePointer>
{
private:
    std::string nom; /**< Le nom du groupe */

    /**
     * @brief Constructeur privé de la classe Groupe.
     * @param nom Le nom du groupe.
     */
    Groupe(const std::string &nom) : std::list<BasePointer>(), nom(nom) {}

    friend class DataBase;

public:
    /**
     * @brief Destructeur de la classe Groupe.
     */
    ~Groupe() {}

    /**
     * @brief Obtient le nom du groupe.
     * @return Le nom du groupe.
     */
    std::string getNom() const
    {
        return nom;
    }

    /**
     * @brief Affiche les objets du groupe.
     * @param os Le flux de sortie sur lequel afficher les objets.
     */
    void afficher(std::ostream &os) const
    {
        os << "Nom : " << nom << "::";
        if (!this->empty())
        {
            os << "membres: " << "::";
            for (const BasePointer &base : *this)
            {
                base->afficher(os);
            }
        }
        else
        {
            os << "Cette groupe n'a pas de membres";
        }
        os << "::";
    }

    /**
     * @brief Enlève un objet multimédia du groupe.
     * @param multimedia L'objet multimédia à enlever.
     */
    void enleverMultimedia(const BasePointer &multimedia)
    {
        this->remove(multimedia);
    }

    /**
     * @brief Obtient le nom de la classe.
     * @return Le nom de la classe.
     */
    std::string className() const
    {
        return "Groupe";
    }
};

#endif