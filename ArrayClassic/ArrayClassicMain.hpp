// File: ArrayClassic/ArrayClassicMain.hpp
// Another merge test from Stan

#ifndef ARRAYCLASSICMAIN_HPP_
#define ARRAYCLASSICMAIN_HPP_

#include <iostream> // istream, ostream.
using namespace std;

void readStream(istream &is, double d[], int cap, int &len);
// Pre: d is allocated with capacity cap.
// Post: num values are input from is to d[0..num - 1], where
// num == min(number of elements in is, cap).
// len == num.

void writeStream(ostream &os, double const d[], int cap, int len);
// Pre: d is allocated with capacity cap.
// Post: num values are output from d[0..num - 1] to os, where
// num == min(len, cap).

#endif
