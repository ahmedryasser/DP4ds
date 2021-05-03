// File: HashFunctions.hpp

#ifndef HASHFUNCTIONS_HPP
#define HASHFUNCTIONS_HPP

#include "CAMetrics.hpp"
typedef CAMetrics<string> CAMetricsStr;
typedef function<unsigned int(CAMetricsStr const &)> HashFunction;

inline unsigned int bernsteinHash(CAMetricsStr const &x) {
    string str = x.toT();
    unsigned int result = 5381;
    for (int i = 0; i < str.size(); i++) {
        result = (result << 5) + result + str[i];
    }
    return result;
}

inline unsigned int knuthHash(CAMetricsStr const &x) {
    string str = x.toT();
    unsigned int result = static_cast<unsigned int> (str.size());
    for (int i = 0; i < str.size(); i++) {
        result = ((result << 5) | ((result >> 27) & 0x0000001f)) ^ str[i];
    }
    return result;
}

#endif  /* HASHFUNCTIONS_HPP */

