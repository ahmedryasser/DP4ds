// File: NTree/ANTreeVis.hpp

#ifndef ANTREEVIS_HPP_
#define ANTREEVIS_HPP_

template<class T>
class NTree; // Forward declaration.

// ========= ANTreeVis =========
template<class T>
class ANTreeVis {
public:
    virtual ~ANTreeVis() {
    }

    virtual void caseAt(int size, NTree<T> &host) = 0;
    virtual void caseAt(int size, NTree<T> const &host) = 0;

};

#endif
