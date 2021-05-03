// File: ListCSV/AListCSVVis.cpp

#ifndef ALISTCSSVVIS_HPP_
#define ALISTCSSVVIS_HPP_

template<class T> class ListCSV; // Forward declaration.

template<class T>
class AListCSVVis {
public:
    virtual ~AListCSVVis() {
    };
    virtual void emptyCase(ListCSV<T> &host) = 0;
    virtual void nonEmptyCase(ListCSV<T> &host) = 0;
    virtual void emptyCase(ListCSV<T> const &host) = 0; // For const host.
    virtual void nonEmptyCase(ListCSV<T> const &host) = 0; // For const host.
};

#endif
