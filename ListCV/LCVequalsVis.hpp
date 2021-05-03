// File: ListCV/LCVequalsVis.hpp

#ifndef LCVequalsVis_hpp
#define LCVequalsVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
#include "LCVisEmptyVis.hpp" // Using another plugin.
using namespace std;

template<class T>
class LCVequalsVis : public AListCVVis<T> {

private:
    template<class S>
    class LCVequalsHelpVis : public AListCVVis<S> {

        friend class LCVequalsVis<S>;

        LCVequalsVis<S>* _master;
        NEListCV<S> const * _rhs; // Input parameter.
        bool _result;             // Output result.

    private:
        LCVequalsHelpVis(LCVequalsHelpVis<S> const &rhs); // Disabled.
        LCVequalsHelpVis &operator=(LCVequalsHelpVis<S> const &rhs); // Disabled.

    public:

        LCVequalsHelpVis (LCVequalsVis<S>* master): _master(master) {}

        ~LCVequalsHelpVis() {
            _master = nullptr;
        }

        void visitMTList(MTListCV<S> const &host) override {
            _result = false;  // Because _rhs is not empty.
        }

        void visitNEList(NEListCV<S> const &host) override {
            if (host.first() != _rhs->first()) {
                _result = false;
            }
            else {
                // Check for equality between the host's rest and the _rhs's rest.
                _master->_rhs = _rhs->rest();
                host.rest()->accept(*_master);
                _result = _master->_result;
            }
        }

        bool result() const {
            return _result;
        }
    };

    friend class LCVequalsHelpVis<T>;

private:
    LCVequalsHelpVis<T>* _helper;
    AListCV<T> const *_rhs; // Input parameter.
    bool _result; // Output result.

private:
    LCVequalsVis(LCVequalsVis<T> const &rhs); // Disabled.
    LCVequalsVis &operator=(LCVequalsVis<T> const &rhs); // Disabled.

public:
    LCVequalsVis(AListCV<T> const *rhs);
    ~LCVequalsVis() { delete _helper; }
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
    bool result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if the host list equals list rhs;
    // Otherwise, false is returned.
    // Two lists are equal if they contain the same number of equal elements in the same order.
};

// ========= Constructor =========
template<class T>
LCVequalsVis<T>::LCVequalsVis(AListCV<T> const *rhs): _rhs(rhs) {
    _helper = new LCVequalsHelpVis<T>(this);
}

// ========= visit =========
template<class T>
void LCVequalsVis<T>::visitMTList(MTListCV<T> const &) {
    LCVisEmptyVis<T> isEmptyVis;
    _rhs->accept(isEmptyVis);
    _result = isEmptyVis.result();
}

template<class T>
void LCVequalsVis<T>::visitNEList(NEListCV<T> const &host) {
    _helper->_rhs = &host;
    _rhs->accept(*_helper);
    _result = _helper->_result;

}

// ========= result =========
template<class T>
bool LCVequalsVis<T>::result() const {
    return _result;
}

#endif
