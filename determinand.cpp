#include <stdexcept>
#include "determinand.hpp"

using namespace std;

Determinand::Determinand(const string& name, const string& units):
    name(name), units(units), number_entries(1)
{}

//finds out which of the groups we want to track each element is 
int Determinand::calcGroup(const string& name, const string& fullname) {
    //fluorates group id 1
    //pbas group id 2
    //litter group id 3
    //common pollutatns group id 4
    int group_id = -1;
    string fluoro_list[] = {"Fluoro","fluoro",""};
    string pops_list[] = {"PBA",
    "Endosulphan",
    "PBDE",
    "PFOS",
    "DDT",
    "Chlrdn",
    "Endrin",
    "HBCD",
    "PFHxS"};
    string physical_list[] = {"Litter", "Faeces", "Metals", "Sewage"};
    string common_poll[] = {"Alky pH 4.5",
    "Phosphorus-P",
    "SiO2 Rv",
    "Ammonia(N)",
    "N Oxidised",
    "Chloride Ion",
    "Nitrate-N",
    "Nitrite-N",
    "Orthophospht",
    "Sld Sus@105C",
    "NH3 un-ion",
    "BOD ATU"};
    //checks if a group identifier can be found
    for (const string& pollutant : fluoro_list) {
        if (fullname.find(pollutant) != string::npos) {
            group_id = 1;
        }
    }
    for (const string& pollutant : pops_list) {
        if (name.find(pollutant) != string::npos) {
            group_id = 2;
        }
    }
    for (const string& pollutant : physical_list) {
        if (fullname.find(pollutant) != string::npos) {
            group_id = 3;
        }
    }
    for (const string& pollutant : common_poll) {
        if (name.find(pollutant) != string::npos) {
            group_id = 4;
        }
    }

    return group_id;
}

//use a 2d array for the safety levels - wait for research
double Determinand::calcSafe(int group_id) {
    double safe = 0;
    //placeholder array
    double level_arr[4][2] = {
        {1, 0.01},
        {2, 0.2},
        {3, 1},
        {4, 30}
    };
    //iterates through array to find matching group id + returns the corresponding safe level
    for (int i=0; i<sizeof(level_arr); i++) {
        if (getID() == level_arr[i][0]) {
            safe = level_arr[i][1];
        }
    }
    return safe;
}