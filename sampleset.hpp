//creates an array of samples/reads from csv file

#pragma once

#include <vector>
#include "sample.hpp"
#include "determinand.hpp"

class SampleSet
{
    public: 
        //constructor with and without reading from a file
        SampleSet() {}
        SampleSet(const std::string& filename) { loadData(filename); }
        void loadData(const std::string&);
        int sampleSize() const { return sample_data.size(); }
        int deterSize() const { return deter_data.size(); }
        int deterSearch(const std::string& name);
        //outputs from 2 vectors
        Sample sampleAt(int index) { return sample_data.at(index); }
        Determinand determinandAt(int index) { return deter_data.at(index); }
    
    private:
        std::vector<Sample> sample_data;
        std::vector<Determinand> deter_data;
};