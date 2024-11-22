#include <stdexcept>
#include "sampleset.hpp"
#include "csv.hpp"

using namespace std;

void SampleSet::load_data(const string& filename)
{
    csv::CSVReader reader(filename);
    data.clear();

    for (const auto& row:reader) {
        string loc = row["sample.samplingPoint"];
        string det = row["determinand.label"];
        double lev = row["result"];
        string qual = row["resultQualifier.notation"];

        Sample temp(loc, det, lev, qual);
        data.push_back(temp);
    }
}

