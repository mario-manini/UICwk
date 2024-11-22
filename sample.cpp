//implementation of samples class
#include <stdexcept>
#include <sstream>
#include "sample.hpp"

using namespace std;

Sample::Sample(const string& loc, double lev, const string& det, const string& qual):
    location(loc), level(lev), determinand_name(det), qualifier(qual)
{
    ostringstream error;
    if (level < 0.0) {
        error << "Invalid level: " << level;
        throw out_of_range(error.str());
    }
}