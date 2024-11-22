//creates an array of samples/reads from csv file

#pragma once

#include <vector>
#include "sample.hpp"

class SampleSet
{
    public: 
        //constructor with and without reading from a file
        SampleSet() {}
        SampleSet(const std::string& filename) { loadData(filename); }
        void load_data(const std::string&);
        int sample_size() const { return sample_data.size(); }
        int deter_search(const std::string&) {}
        Sample operator[](int index) const { return data.at(index); }
    
    private:
        std::vector<Sample> sample_data;
        std::vector<Determinand> deter_data;
};