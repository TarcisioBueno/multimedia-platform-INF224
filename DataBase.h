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

class DataBase
{
private:
    std::map<std::string, BasePointer> Multimedia;
    std::map<std::string, std::shared_ptr<Groupe>> Groupes;

public:
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

    BasePointer creerFilm(std::string nom, std::string nomDuFichier, int duree, int *chapitres, int taille)
    {
        // Check if a multimedia object with the same name already exists
        if (Multimedia.find(nom) != Multimedia.end())
        {
            std::cout << "Un objet multimédia avec le nom " << nom << " existe déjà.\n";
            // Return a null BasePointer
            return BasePointer();
        }
        else if (taille <= 0)
        {
            std::cout << "Le paramètre taille doit être supérieur à 0.\n";
            // Return a null BasePointer
            return BasePointer();
        }

        // Create the new Film
        BasePointer film(new Film(nom, nomDuFichier, duree, chapitres, taille));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, film));
        return film;
    }

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

    void supprimer(const std::string &nom)
    {
        auto multimedia_it = Multimedia.find(nom);
        if (multimedia_it != Multimedia.end())
        {
            // Remove the multimedia object from all groups
            for (auto &pair : Groupes)
            {
                pair.second->enleverMultimedia(multimedia_it->second);
            }

            // Delete the multimedia object
            Multimedia.erase(multimedia_it);
        }
        else
        {
            auto group_it = Groupes.find(nom);
            if (group_it != Groupes.end())
            {
                // Delete the group
                Groupes.erase(group_it);
            }
            else
            {
                std::cout << "Objet non trouvé: " << nom << " ";
            }
        }
    }

    // Serialization and deserialization

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

std::string listerMultimedia()
{
    std::stringstream ss;
    for (const auto& pair : Multimedia)
    {
        ss << pair.first << " ";
    }
    return ss.str();
}
};

#endif