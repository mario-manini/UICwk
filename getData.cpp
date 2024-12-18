#include "sampleset.hpp"
#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: <filename>" << endl;
  }

  SampleSet test_set(argv[1]);
  SampleSet fluorates = test_set.filterName("Fluoroxypyr");

  cout << test_set.determinandAt(1).getName() << endl;
  cout << test_set.determinandAt(3).getID() << endl;
  cout << test_set.determinandAt(3).getName() << endl;
  cout << test_set.sampleAt(3).getLocation() << endl;
  cout << test_set.sampleAt(2).getLevel() << endl;
  cout << test_set.determinandAt(3).getNumberEntries() << endl;

  cout << fluorates.sampleSize() << endl;
  cout << fluorates.getAvg() << endl;
}