/**
 * @file DataBase.h
 * @brief Ce fichier contient la classe DataBase, qui représente une base de données multimédia.
 */

#ifndef DATABASE_H
#define DATABASE_H

#include "Base.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Groupe.h"
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>

/**
 * @class DataBase
 * @brief Classe pour gérer une base de données multimédia.
 */
class DataBase
{
private:
    std::map<std::string, BasePointer> Multimedia;
    std::map<std::string, std::shared_ptr<Groupe>> Groupes;

public:
    /**
     * @brief Crée une nouvelle photo.
     * @param nom Le nom de la photo.
     * @param nomDuFichier Le nom du fichier de la photo.
     * @param latitude La latitude où la photo a été prise.
     * @param longitude La longitude où la photo a été prise.
     * @return Un pointeur vers la photo créée.
     */
    BasePointer creerPhoto(std::string nom, std::string nomDuFichier, double latitude, double longitude)
    {
        // Check if a multimedia object with the same name already exists
        if (Multimedia.find(nom) != Multimedia.end())
        {
            // Return a null BasePointer
            return BasePointer();
        }

        // Create the new Photo
        BasePointer photo(new Photo(nom, nomDuFichier, latitude, longitude));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, photo));
        return photo;
    }

    /**
     * @brief Crée une nouvelle vidéo.
     * @param nom Le nom de la vidéo.
     * @param nomDuFichier Le nom du fichier de la vidéo.
     * @param duree La durée de la vidéo.
     * @return Un pointeur vers la vidéo créée.
     */
    BasePointer creerVideo(std::string nom, std::string nomDuFichier, int duree)
    {
        // Check if a multimedia object with the same name already exists
        if (Multimedia.find(nom) != Multimedia.end())
        {
            // Return a null BasePointer
            return BasePointer();
        }

        // Create the new Video
        BasePointer video(new Video(nom, nomDuFichier, duree));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, video));
        return video;
    }

    /**
     * @brief Crée un nouveau film.
     * @param nom Le nom du film.
     * @param nomDuFichier Le nom du fichier du film.
     * @param duree La durée du film.
     * @param chapitres Un tableau contenant la durée de chaque chapitre.
     * @param taille La taille du tableau des chapitres.
     * @return Un pointeur vers le film créé.
     */
    BasePointer creerFilm(std::string nom, std::string nomDuFichier, int duree, int *chapitres, int taille)
    {
        
        if (Multimedia.find(nom) != Multimedia.end())
        {
            std::cout << "Un objet multimédia avec le nom " << nom << " existe déjà.\n";
         
            return BasePointer();
        }
        else if (taille <= 0)
        {
            std::cout << "Le paramètre taille doit être supérieur à 0.\n";
           
            return BasePointer();
        }


        BasePointer film(new Film(nom, nomDuFichier, duree, chapitres, taille));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, film));
        return film;
    }

    /**
     * @brief Crée un nouveau groupe.
     * @param nom Le nom du groupe.
     * @return Un pointeur partagé vers le groupe créé.
     */
    std::shared_ptr<Groupe> creerGroupe(const std::string &nom)
    {
        // Check if a group with the same name already exists
        if (Groupes.find(nom) != Groupes.end())
        {
            // Return a null shared_ptr<Groupe>
            return std::shared_ptr<Groupe>();
        }

        // Create the new group
        std::shared_ptr<Groupe> groupe(new Groupe(nom));
        Groupes.insert(std::pair<std::string, std::shared_ptr<Groupe>>(nom, groupe));
        return groupe;
    }

    /**
     * @brief Recherche un objet multimédia par son nom.
     * @param nom Le nom de l'objet multimédia à rechercher.
     * @return Une chaîne de caractères contenant les détails de l'objet multimédia si trouvé, sinon un message d'erreur.
     */
    std::string rechercherMultimedia(const std::string &nom)
    {
        std::stringstream ss;
        auto it = Multimedia.find(nom);
        if (it != Multimedia.end())
        {
            it->second->afficher(ss);
        }
        else
        {
            ss << "Objet multimédia non trouvé: " << nom;
        }
        return ss.str();
    }

    /**
     * @brief Recherche un groupe par son nom.
     * @param nom Le nom du groupe à rechercher.
     * @return Une chaîne de caractères contenant les détails du groupe si trouvé, sinon un message d'erreur.
     */
    std::string rechercherGroupe(const std::string &nom)
    {
        std::stringstream ss;
        auto it = Groupes.find(nom);
        if (it != Groupes.end())
        {
            it->second->afficher(ss);
        }
        else
        {
            ss << "Groupe non trouvé: " << nom;
        }
        return ss.str();
    }

    /**
     * @brief Joue un objet multimédia par son nom.
     * @param nom Le nom de l'objet multimédia à jouer.
     * @return Une chaîne de caractères indiquant que l'objet multimédia est en cours de lecture si trouvé, sinon un message d'erreur.
     */
    std::string jouer(const std::string &nom)
    {
        std::stringstream ss;
        auto it = Multimedia.find(nom);
        if (it != Multimedia.end())
        {
            it->second->jouer();
            ss << "Jouant: " << nom << " ";
        }
        else
        {
            ss << "Objet multimédia non trouvé: " << nom << " ";
        }

        return ss.str();
    }

    /**
     * @brief Supprime un objet multimédia ou un groupe par son nom.
     * @param nom Le nom de l'objet multimédia ou du groupe à supprimer.
     */
    void supprimer(const std::string &nom)
    {
        auto multimedia_it = Multimedia.find(nom);
        if (multimedia_it != Multimedia.end())
        {
           
            for (auto &pair : Groupes)
            {
                pair.second->enleverMultimedia(multimedia_it->second);
            }

           
            Multimedia.erase(multimedia_it);
        }
        else
        {
            auto group_it = Groupes.find(nom);
            if (group_it != Groupes.end())
            {
               
                Groupes.erase(group_it);
            }
            else
            {
                std::cout << "Objet non trouvé: " << nom << " ";
            }
        }
    }

    /**
     * @brief Crée un nouvel objet multimédia de la classe spécifiée.
     * @param classname Le nom de la classe de l'objet multimédia à créer.
     * @return Un pointeur vers le nouvel objet multimédia créé, ou nullptr si la classe est inconnue.
     */

    BasePointer creerMultimedia(std::string classname)
    {

        if (classname == "Photo")
        {
            return BasePointer(new Photo());
        }
        else if (classname == "Video")
        {
            return BasePointer(new Video());
        }
        else if (classname == "Film")
        {
            return BasePointer(new Film());
        }
        else
        {
            std::cerr << "Unknown class name: " << classname << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Sauvegarde tous les objets multimédia dans un fichier.
     * @param filename Le nom du fichier dans lequel sauvegarder les objets multimédia.
     * @return true si la sauvegarde a réussi, false sinon.
     */
    bool saveAll(const std::string &filename)
    {
        std::ofstream f(filename);
        if (!f)
        {
            std::cerr << "Can't open file " << filename << std::endl;
            return false;
        }

        // Save all multimedia objects
        for (const auto &pair : Multimedia)
        {
            f << pair.second->className() << '\n';
            pair.second->write(f);
            if (f.fail())
            {
                std::cerr << "Write error in " << filename << std::endl;
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Lit tous les objets multimédia à partir d'un fichier.
     * @param filename Le nom du fichier à partir duquel lire les objets multimédia.
     * @return true si la lecture a réussi, false sinon.
     */
    bool readAll(const std::string &filename)
    {
        std::ifstream f(filename);
        if (!f)
        {
            std::cerr << "Can't open file " << filename << std::endl;
            return false;
        }

        std::string classname;
        while (std::getline(f, classname))
        {
            // Skip lines that are empty or only contain whitespace
            if (classname.empty() || std::all_of(classname.begin(), classname.end(), ::isspace))
            {
                continue;
            }

            BasePointer obj = creerMultimedia(classname); // Assuming you have a createMultimedia method
            if (obj)
            {
                obj->read(f); // Assuming you have a read method in your base class
                if (f.fail())
                {
                    std::cerr << "Read error in " << filename << std::endl;
                    return false;
                }
                else
                {
                    Multimedia.insert(std::pair<std::string, BasePointer>(obj->getNom(), obj));
                    std::cout << "Successfully created and added " << obj->getNom() << std::endl;
                }
            }
        }

        return true;
    }

    /**
     * @brief Liste tous les objets multimédia.
     * @return Une chaîne de caractères contenant les noms de tous les objets multimédia.
     */
    std::string listerMultimedia()
    {
        std::stringstream ss;
        for (const auto &pair : Multimedia)
        {
            ss << pair.first << " ";
        }
        return ss.str();
    }
};

#endif