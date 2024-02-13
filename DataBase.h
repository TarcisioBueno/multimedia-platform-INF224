#ifndef DATABASE_H
#define DATABASE_H

#include "Base.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Groupe.h"
#include <map>
#include <sstream>

class DataBase
{
private:
    std::map<std::string, BasePointer> Multimedia;
    std::map<std::string, std::shared_ptr<Groupe>> Groupes;

public:
    BasePointer creerPhoto(std::string nom, std::string nomDuFichier, double latitude, double longitude)
    {
        BasePointer photo(new Photo(nom, nomDuFichier, latitude, longitude));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, photo));
        return photo;
    }
    BasePointer creerVideo(std::string nom, std::string nomDuFichier, int duree)
    {
        BasePointer video(new Video(nom, nomDuFichier, duree));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, video));
        return video;
    }

    BasePointer creerFilm(std::string nom, std::string nomDuFichier, int duree, int *chapitres, int taille)
    {
        BasePointer film(new Film(nom, nomDuFichier, duree, chapitres, taille));
        Multimedia.insert(std::pair<std::string, BasePointer>(nom, film));
        return film;
    }
    std::shared_ptr<Groupe> creerGroupe(const std::string &nom)
    {
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
            ss << "Multimedia object not found: " << nom;
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
            ss << "Group not found: " << nom;
        }
        return ss.str();
    }


    void jouer(const std::string &nom)
    {
        auto it = Multimedia.find(nom);
        if (it != Multimedia.end())
        {
            it->second->jouer();
        }
        else
        {
            std::cout << "Multimedia object not found: " << nom << " ";
        }
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
                std::cout << "Object not found: " << nom << " ";
            }
        }
    }
};

#endif