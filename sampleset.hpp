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
        void loadData(const std::string&);
        int size() const { return data.size(); }
        Sample operator[](int index) const { return data.at(index); }
    
    private:
        std::vector<Sample> data;
}