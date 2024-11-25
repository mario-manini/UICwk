//implementation of samples class
#include <stdexcept>
#include <sstream>
#include "sample.hpp"

using namespace std;

Sample::Sample(const string& loc, double lev, const string& det, const string& qual, const string& time):
    location(loc), level(lev), determinand_name(det), qualifier(qual), time(time)
{
    //makes sure level is above 0 (correct value)
    ostringstream error;
    if (level < 0.0) {
        error << "Invalid level: " << level;
        throw out_of_range(error.str());
    }
}