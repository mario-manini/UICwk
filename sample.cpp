//implementation of samples class
#include <stdexcept>
#include <sstream>
#include "sample.hpp"

using namespace std;

Sample::Sample(const string& loc, double lev, const string& det, const string& qual, const string& time, const string& full):
    location(loc), level(lev), determinand_name(det), qualifier(qual), time(time), full_name(full)
{}