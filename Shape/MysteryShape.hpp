// File: Shape/MysteryShape.hpp
// Number: 16
// Name: Ahmed Najiub
// Class: CoSc 320
#ifndef MysteryShape_hpp
#define MysteryShape_hpp

#include "AShape.hpp"

class MysteryShape : public AShape {
private:
    double _side;

public:
    MysteryShape(double side = 0.0);

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display(ostream &os) override;
    void promptAndSetDimensions() override;
};

#endif

