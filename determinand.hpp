#pragma once

#include <string>
#include <iostream>

class Determinand
{
    public:
        Determinand(const std::string&, std::string);
        std::string getName() const { return name; }
        int getID() { return group_id; }
        double getSafeLevel() { return safe_level; }
        std::string getUnits() const { return units; }
        int calcGroup(const std::string&) {}
        double calcSafe(int) {}

    private:
        std::string name;
        int group_id;
        double safe_level;
        std::string units;
};