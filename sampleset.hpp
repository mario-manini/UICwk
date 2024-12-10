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
        //getter methods
        int sampleSize() const { return sample_data.size(); }
        int deterSize() const { return deter_data.size(); }
        int deterSearch(const std::string& name);
        double getAvg(); 
        //addition methods
        void addSample(Sample sample) { sample_data.push_back(sample); }
        void addDeterminand(Determinand determinand) { deter_data.push_back(determinand); }
        //outputs from 2 vectors
        Sample sampleAt(int index) { return sample_data.at(index); }
        Determinand determinandAt(int index) { return deter_data.at(index); }
        //constructor with search methods
        SampleSet filterName(const std::string&);
        SampleSet filterLocation(const std::string&);
        SampleSet filterTime(const std::string&);
        SampleSet filterGroup(int);
        SampleSet filterDate(const std::string&);

    
    private:
        //array of sample/determinand objects
        //samples are instances of determinands that are measurable instances
        std::vector<Sample> sample_data;
        std::vector<Determinand> deter_data;
};