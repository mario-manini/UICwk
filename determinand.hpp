#pragma once

#include <string>
#include <iostream>

class Determinand
{
    public:
        Determinand(const std::string&, const std::string&);
        std::string getName() const { return name; }
        //getter methods
        int getID() { return group_id; }
        double getSafeLevel() { return safe_level; }
        std::string getUnits() const { return units; }
        int getNumberEntries() { return number_entries; }
        //setter methods
        void setSafeLevel(double level) { safe_level = level; }
        void setGroup(int group) { group_id = group; }
        void incrementCount() { number_entries++; }
        //general calculation for additional values
        int calcGroup(const std::string&, const std::string&);
        double calcSafe(int);

    private:
        std::string name;
        int group_id;
        double safe_level;
        std::string units;
        int number_entries;
};