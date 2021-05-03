// File: ListCSV/LCSVremoveVis.hpp

#ifndef LCSVREMOVEVIS_HPP_
#define LCSVREMOVEVIS_HPP_

#include <iostream>
#include "ListCSV.hpp"
#include "AListCSVVis.hpp"
using namespace std;

// ========= LCSVremoveVis =========
template<class T>
class LCSVremoveVis : public AListCSVVis<T> {
private:
    T const &_data; // Input parameter.

public:
    // ========= Constructor =========
    LCSVremoveVis(T const &data):
        _data(data) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: If data is in the host list, it is removed;
    // otherwise the host list is unchanged.
    void emptyCase(ListCSV<T> &host) override {

    }

    void nonEmptyCase(ListCSV<T> &host) override {
        if(host.first() == _data){
            host.remFirst();
        }
        else{
            LCSVremoveVis<T> removeVis(_data);
            host.rest().accept(removeVis);
        }
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVremoveVis precondition violated: "
             << "Cannot remove from a const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVremoveVis precondition violated: "
             << "Cannot remove from a const list." << endl;
        throw -1;
    }
};

// Global function for convenience.
template<class T>
void remove(ListCSV<T> &list, T const &data) {
    LCSVremoveVis<T> removeVis(data);
    list.accept(removeVis);
}

#endif
