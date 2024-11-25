#include <stdexcept>
#include "determinand.hpp"

using namespace std;

Determinand::Determinand(const string& name, const string& units):
    name(name), units(units), number_entries(1)
{}

//finds out which of the groups we want to track each element is 
int Determinand::calcGroup(const string& name) {
    //fluorates group id 1
    //pbas group id 2
    //litter group id 3
    //common pollutatns group id 4
    int group_id = -1;
    string group_list[3] = {"Fluoro", "PBA", "Litter"};
    //placeholder for common pollutants list
    string common_poll[0] = {};
    //checks if a group identifier can be found
    if (name.find(group_list[0]) != std::string::npos) {
        group_id = 1;
    } else if (name.find(group_list[1]) != std::string::npos) {
        group_id = 2;
    } else if (name.find(group_list[2]) != std::string::npos) {
        group_id = 3;
    } else {
        for (int i=0; i<sizeof(common_poll); i++) {
            if (name == common_poll[i]) {
                group_id = 4;
            }
        }
    }
    return group_id;
}

//use a 2d array for the safety levels - wait for research
double Determinand::calcSafe(int group_id) {
    double safe = 0;
    //placeholder array
    double level_arr[4][2] = {
        {1, 4.5},
        {2, 5.2},
        {3, 3.2},
        {4, 5.2}
    };
    //iterates through array to find matching group id + returns the corresponding safe level
    for (int i=0; i<sizeof(level_arr); i++) {
        if (getID() == level_arr[i][0]) {
            safe = level_arr[i][1];
        }
    }
    return safe;
}