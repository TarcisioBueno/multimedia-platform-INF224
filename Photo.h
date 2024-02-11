#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include "Base.h"

class Photo : public Base
{
private:
    double latitude;
    double longitude;

public:
    Photo() : Base("", ""), latitude(0), longitude(0) {}
    Photo(std::string nom, std::string nomDuFichier, double latitude, double longitude) : Base(nom, nomDuFichier), latitude(latitude), longitude(longitude) {}
    double getLatitude() const
    {
        return latitude;
    }
    double getLongitude() const
    {
        return longitude;
    }
    void setLatitude(double latitude)
    {
        this->latitude = latitude;
    }
    void setLongitude(double longitude)
    {
        this->longitude = longitude;
    }
    void afficher(std::ostream &os) const override
    {
        Base::afficher(os);
        os << "Latitude: " << latitude << " Longitude: " << longitude << std::endl;
    }

    // Linux

    void jouer() const override
    {
        std::string argument = "imagej " + getNomDuFichier() + "&";
        system(argument.data());
    }
};

#endif