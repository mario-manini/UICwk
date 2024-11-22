//holds key information on the samples 
#pragma once

#include <string>
#include <iostream>

class Sample
{
    public:
    //construct with location/determinand/level/qualifier
        Sample(const std::string&, const std::string&, double, const std::string&);
        std::string getLocation() const { return location; }
        std::string getDeterminand() const { return determinand_name; }
        double getLevel() const { return level; }
        std::string getQualif() const { return qualifier; }


    private:
        std::string location;
        std::string determinand_name;
        double level;
        std::string qualifier;
};

