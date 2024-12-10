#include <stdexcept>
#include "sampleset.hpp"
#include "csv.hpp"

using namespace std;

//parses the csv file and initaties objects of samples for each sample
void SampleSet::loadData(const string& filename)
{
    csv::CSVReader reader(filename);
    deter_data.clear();
    sample_data.clear();

    for (const auto& row:reader) {
        //values to go into a sample array
        string loc = row["sample.samplingPoint.label"].get<string>();
        string det = row["determinand.label"].get<string>();
        double lev = row["result"].get<double>();
        string qual = row["resultQualifier.notation"].get<string>();
        string time = row["sample.sampleDateTime"].get<>();
        string full_name = row["determinand.definition"].get<string>();
        
        Sample temp(loc, lev, det, qual, time, full_name);
        sample_data.push_back(temp);

        //values to go into a determinand array
        string units = row["determinand.unit.label"].get<string>();
        Determinand temp2(det, units);

        //uncomment to only track groups
        //if (group_id != -1) {
        //if not in the array already adds new entry
        //else increments count
        int array_pos = deterSearch(det);
        if (array_pos == -1) {
            int group_id = temp2.calcGroup(det, full_name);
            temp2.setGroup(group_id);
            temp2.setSafeLevel(temp2.calcSafe(group_id));
            deter_data.push_back(temp2);
        } else {
            deter_data[array_pos].incrementCount();
        }
        //}
    }
}

//searches through the determinand array to find out if the determinand already there
int SampleSet::deterSearch(const string& name) {
    int found_flag = -1;
    for (int i=0; i<deterSize(); i++) {
        if (deter_data[i].getName().find(name) != string::npos){
            found_flag = i;
        }
    }
    return found_flag;
}

//return all samples of a certain name
SampleSet SampleSet::filterName(const string& name) {
    SampleSet result_vector;
    for (int i=0; i<sampleSize(); i++) {
        if(sampleAt(i).getDeterminand().find(name) != string::npos) {
            result_vector.addSample(sampleAt(i));
        }
    }
    for (int i=0; i<deterSize(); i++) {
        if(determinandAt(i).getName().find(name) != string::npos) {
            result_vector.addDeterminand(determinandAt(i));
        }
    }
    return result_vector;
}

//return all samples at a certain location
SampleSet SampleSet::filterLocation(const string& location) {
    SampleSet result_vector;
    for (int i=0; i<sampleSize(); i++) {
        if(sampleAt(i).getLocation().find(location) != string::npos) {
            result_vector.addSample(sampleAt(i));
            int found = deterSearch(sampleAt(i).getDeterminand());
            result_vector.addDeterminand(determinandAt(found));
        }
    }
    return result_vector;
}

//return all samples at a certain time
SampleSet SampleSet::filterTime(const string& time) {
    SampleSet result_vector;
    for (int i=0; i<sampleSize(); i++) {
        if(sampleAt(i).getTime() == time) {
            result_vector.addSample(sampleAt(i));
            int found = deterSearch(sampleAt(i).getDeterminand());
            result_vector.addDeterminand(determinandAt(found));
        }
    }
    return result_vector;
}

//finds the average of a vector
double SampleSet::getAvg() {
    double result;
    for (int i=0; i<sampleSize(); i++) {
        result = result + sampleAt(i).getLevel();
    }
    result = result/sampleSize();
    return result;
}

// return all samples in a certain group
SampleSet SampleSet::filterGroup(int ID) {
    SampleSet result_vector;
    for (int i=0; i<deterSize(); i++) {
        if (determinandAt(i).getID() == ID) {
            result_vector.addDeterminand(determinandAt(i));
        }
    }
    for (int i=0; i<sampleSize(); i++) {
        for (int j=0; j<result_vector.deterSize(); j++) {
            if (sampleAt(i).getDeterminand() == result_vector.determinandAt(j).getName()) {
                result_vector.addSample(sampleAt(i));
            }
        }
    }
    return result_vector;
}
    
// return all samples in a certain datetime
SampleSet SampleSet::filterDate(const string& time) {
    SampleSet result_vector;
    for (int i=0; i<sampleSize(); i++) {
        if (sampleAt(i).getTime() == time) {
            result_vector.addSample(sampleAt(i));
        }
    }
    return result_vector;
}