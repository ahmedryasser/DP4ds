// File: Shape/ShapeMain.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1

#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.
#include "Utilities.hpp" // promptIntBetween, promptDoubleGE.
#include "AShape.hpp"
#include "Line.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "RightTriangle.hpp"
#include "NullShape.hpp"
#include "ShapeMain.hpp"
#include "MysteryShape.hpp"


int main() {
    const int NUM_SHAPES = 5;
    AShape *shapes[NUM_SHAPES];
    initialize(shapes, NUM_SHAPES);
    promptLoop(shapes, NUM_SHAPES);
    cleanUp(shapes, NUM_SHAPES);
    return EXIT_SUCCESS;
}

void initialize(AShape *shapes[], int cap) {
    for (int i = 0; i < cap; i++) {
        shapes[i] = new NullShape;
    }
}

void cleanUp(AShape *shapes[], int cap) {
    for (int i = 0; i < cap; i++) {
        delete shapes[i];
        shapes[i] = nullptr;
    };
}

void promptLoop(AShape *shapes[], int cap) {
    char response = '\0';
    do {
        cout << "\nThere are [0.." << cap - 1 << "] shapes." << endl;
        cout << "(m)ake  (c)lear  (a)rea  (p)erimeter  (s)cale  (d)isplay  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'M':
            makeShape(shapes[promptIntBetween("Which shape?", 0, cap - 1)]);
            break;
        case 'C':
            clearShape(shapes[promptIntBetween("Which shape?", 0, cap - 1)]);
            break;
        case 'A':
            printArea(shapes[promptIntBetween("Which shape?", 0, cap - 1)]);
            break;
        case 'P':
            printPerimeter(shapes[promptIntBetween("Which shape?", 0, cap - 1)]);
            break;
        case 'S':
            scaleShape(shapes[promptIntBetween("Which shape?", 0, cap - 1)]);
            break;
        case 'D':
            displayShape(shapes[promptIntBetween("Which shape?", 0, cap - 1)]);
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
}

void makeShape(AShape *&sh) {
    switch (shapeType()) {
    case 'L':
        delete sh;
        sh = new Line;
        break;
    case 'R':
        delete sh;
        sh = new Rectangle;
        break;
    case 'C':
        delete sh;
        sh = new Circle;
        break;
    case 'T':
        delete sh;
        sh = new RightTriangle;
        break;
    case 'M':
        sh = new MysteryShape;
        break;
    default:
        break;
    }
    sh->promptAndSetDimensions();
}

char shapeType() {
    char ch;
    cout << "(l)ine  (r)ectangle  (c)ircle  right(t)riangle  (m)ystery: ";
    cin >> ch;
    ch = toupper(ch);
    while (ch != 'L' && ch != 'R' && ch != 'C' && ch != 'T' && ch != 'M') {
        cout << "Must be l, r, c, t, or m.  Which type? ";
        cin >> ch;
        ch = toupper(ch);
    }
    return ch;
}

void clearShape(AShape *&sh) {
    delete sh;
    sh = new NullShape;
}

void printArea(AShape *sh) {
    cout << "\nArea: " << sh->area() << endl;
}

void printPerimeter(AShape *sh) {
    cout << "\nPerimeter: " << sh->perimeter() << endl;
}

void scaleShape(AShape *sh) {
    sh->scale(promptDoubleGE("Scale factor?", 0.0));
}

void displayShape(AShape *sh) {
    cout << endl;
    sh->display(cout);
}

