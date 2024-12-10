#include "sampleset.hpp"
#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: <filename>" << endl;
    exit(1);
  }

  //creates an instance of 
  SampleSet data(argv[1]);

  SampleSet filteredName = data.filterName("Nitrogen");
  cout << filteredName.sampleAt(0).getDeterminand();
  std::vector<SampleSet> groups;
  groups.push_back(data.filterGroup(1));
  groups.push_back(data.filterGroup(2));
  groups.push_back(data.filterGroup(3));
  groups.push_back(data.filterGroup(4));

  cout << "Fluorates eter count " << groups[0].deterSize() << " sample count " << groups[0].sampleSize() << 
  " avg " << groups[0].getAvg() << endl;
  cout << "PBAs deter count " << groups[1].deterSize() << " sample count " << groups[1].sampleSize() << 
  " avg " << groups[1].getAvg() << endl;
  cout << "Physical deter count " << groups[2].deterSize() << " sample count " << groups[2].sampleSize() << 
  " avg " << groups[2].getAvg() << endl;
  cout << "Common deter count " << groups[3].deterSize() << " sample count " << groups[3].sampleSize() << 
  " avg " << groups[3].getAvg() << endl;
}