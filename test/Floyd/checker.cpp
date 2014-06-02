/**
 * This program checks equality of distance matrices between Boost and GraphLib
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
  string Boost, GraphLib;
  ifstream bin("Boost.txt");
  ifstream gin("GraphLib.txt");
  if (bin.bad() || gin.bad()) {
    fprintf(stderr, "Something bad with input files\n");
    return 1;
  }
  while (true) {
    if (bin >> Boost) {
      if (gin >> GraphLib) {
	if (Boost != GraphLib) {
	  cout << "Incorrect: Boost - " << Boost
	       << ", GraphLib - " << GraphLib << endl;
	  return 0;
	}
      }
      else {
	fprintf(stderr, "Boost output contains more data\n");
	return 0;
      }
    }
    else {
      if (gin >> GraphLib) {
	fprintf(stderr, "GraphLib output contains more data\n");
	return 0;
      }
      else break;
    }
  }
  puts("Correct");
  return 0;
}
