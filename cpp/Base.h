/**
 * @file Base.h
 * @brief Ce fichier contient la classe Base, qui représente une entité de base abstraite.
 */

#ifndef BASE_H
#define BASE_H

#include <iostream>

/**
 * @class Base
 * @brief Classe de base abstraite pour représenter une entité de base.
 * 
 * La classe Base est une classe abstraite qui sert de base pour d'autres classes.
 * Elle contient des méthodes virtuelles pures et des méthodes virtuelles redéfinissables.
 */
class Base
{
private:
    std::string nom; /**< Le nom de l'entité de base. */
    std::string nomDuFichier; /**< Le nom du fichier associé à l'entité de base. */
protected:
    /**
     * @brief Constructeur par défaut de la classe Base.
     */
    Base();

    /**
     * @brief Constructeur de la classe Base.
     * @param nom Le nom de l'entité de base.
     * @param nomDuFichier Le nom du fichier associé à l'entité de base.
     */
    Base(std::string nom, std::string nomDuFishier);  

    friend class DataBase; /**< Déclaration d'amitié avec la classe DataBase. */
public:    
    /**
     * @brief Destructeur virtuel de la classe Base.
     */
    virtual ~Base();

    /**
     * @brief Obtient le nom de l'entité de base.
     * @return Le nom de l'entité de base.
     */
    std::string getNom() const;

    /**
     * @brief Obtient le nom du fichier associé à l'entité de base.
     * @return Le nom du fichier associé à l'entité de base.
     */
    std::string getNomDuFichier() const;

    /**
     * @brief Définit le nom de l'entité de base.
     * @param nom Le nom de l'entité de base.
     */
    void setNom(std::string nom);

    /**
     * @brief Définit le nom du fichier associé à l'entité de base.
     * @param nomDuFichier Le nom du fichier associé à l'entité de base.
     */
    void setNomDuFichier(std::string nomDuFichier);

    /**
     * @brief Affiche les informations de l'entité de base.
     * @param os Le flux de sortie sur lequel afficher les informations.
     */
    virtual void afficher(std::ostream &os) const;

    /**
     * @brief Méthode virtuelle pure pour jouer avec l'entité de base.
     */
    virtual void jouer() const = 0;

    /**
     * @brief Obtient le nom de la classe.
     * @return Le nom de la classe.
     */
    virtual std::string className() const;

    /**
     * @brief Écrit les informations de l'entité de base dans un flux de sortie.
     * @param f Le flux de sortie dans lequel écrire les informations.
     */
    virtual void write(std::ostream & f);

    /**
     * @brief Lit les informations de l'entité de base à partir d'un flux d'entrée.
     * @param f Le flux d'entrée à partir duquel lire les informations.
     */
    virtual void read(std::istream & f);
};

#endif