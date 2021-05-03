// File: BiTreeCSV/ABiTreeCSVVis.cpp

#ifndef ABITREECSVVIS_HPP_
#define ABITREECSVVIS_HPP_

template<class T> class BiTreeCSV; // Forward declaration.

// Represents an abstract visitor to a mutable tree.
template<class T>
class ABiTreeCSVVis {
public:
    virtual ~ABiTreeCSVVis() {
    }

    virtual void emptyCase(BiTreeCSV<T> &host) = 0;
    virtual void nonEmptyCase(BiTreeCSV<T> &host) = 0;
    virtual void emptyCase(BiTreeCSV<T> const &host) = 0; // For const host.
    virtual void nonEmptyCase(BiTreeCSV<T> const &host) = 0; // For const host.
};

#endif
