// File: ListCV/AListCVVis.hpp

#ifndef AListCVVis_hpp 
#define AListCVVis_hpp

template<class T> class MTListCV; // Forward declaration.
template<class T> class NEListCV; // Forward declaration.

template<class T>
class AListCVVis {
public:
    virtual ~AListCVVis();
    virtual void visitMTList(MTListCV<T> const &host) = 0;
    virtual void visitNEList(NEListCV<T> const &host) = 0;
};

template<class T>
AListCVVis<T>::~AListCVVis() {
}

#endif
