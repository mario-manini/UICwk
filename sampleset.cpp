#include <stdexcept>
#include "sampleset.hpp"
#include "csv.hpp"

using namespace std;

void SampleSet::loadData(const string& filename)
{
    csv::CSVReader reader(filename);
    deter_data.clear();
    sample_data.clear();

    for (const auto& row:reader) {
        //values to go into a sample array
        string loc = row["sample.samplingPoint"].get<string>();
        string det = row["determinand.label"].get<string>();
        double lev = row["result"].get<double>();
        string qual = row["resultQualifier.notation"].get<string>();
        
        Sample temp(loc, lev, det, qual);
        sample_data.push_back(temp);

        //values to go into a determinand array
        string units = row["determinand.unit.label"].get<string>();
        Determinand temp2(det, units);
        int group_id = temp2.calcGroup(det);
        temp2.setGroup(group_id);

        //makes sure pollutant is one of the ones we want to track
        if (group_id != -1) {
            temp2.setSafeLevel(temp2.calcSafe(group_id));
            //if not in the array already adds new entry
            int array_pos = deterSearch(det);
            if (array_pos == -1) {
                deter_data.push_back(temp2);
            } else {
                deter_data[array_pos].incrementCount();
            }
        }
    }
}

int SampleSet::deterSearch(const string& name) {
    int found_flag = -1;
    for (int i=0; i<deterSize(); i++) {
        if (deter_data[i].getName() == name){
            found_flag = i;
        }
    }
    return found_flag;
}
