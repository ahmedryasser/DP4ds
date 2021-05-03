// File: ASeq/ASeq.hpp
// Abstract Sequence Template Class.

#ifndef ASEQ_HPP_
#define ASEQ_HPP_

template <class S>
class ASeq {
public:
    ASeq(int cap = 0);
    virtual ~ASeq() = 0;
    virtual S &operator[](int i) = 0; // For read/write.
    virtual S const &operator[](int i) const = 0; // For read-only.
    virtual int cap() const = 0;

private:
    ASeq(ASeq const &rhs); // Disabled.
    ASeq &operator=(ASeq const &rhs); // Disabled.
};

template <class S>
ASeq<S>::ASeq(int cap) { }

template <class S>
ASeq<S>::~ASeq() { }

#endif
