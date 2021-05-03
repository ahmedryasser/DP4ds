// File: ShapeFactory/ShapeFactoryMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <cctype>  // toupper.
#include "Utilities.hpp"  // promptDoubleGE.
#include "ShapeFactory.hpp"
#include "ShapeFactoryMain.hpp"

int main() {  
    const int NUM_SHAPES = 5;
    ArrayPShape shapes(NUM_SHAPES);
    initialize(shapes);
    promptLoop(shapes);
    cleanUp(shapes);
    return EXIT_SUCCESS;
}

void initialize(ArrayPShape &shapes) {  
    for (int i = 0; i < shapes.cap(); i++) {  
        shapes[i] = ShapeFactory::makeShape();
    }
}

void cleanUp(ArrayPShape &shapes) {  
    for (int i = 0; i < shapes.cap(); i++) {  
        delete shapes[i];
        shapes[i] = nullptr;
    }
}

void promptLoop(ArrayPShape &shapes) {  
    char cResponse = '\0';
    int cap = shapes.cap();
    do {  
        cout << "\nThere are [0.." << cap - 1 << "] shapes." << endl;
        cout << "(m)ake  (c)lear  (a)rea  (p)erimeter  ";
        cout << "(s)cale  (d)isplay  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {  
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
            cout << "\nPlease enter only one of the following characters: ";
            cout << "m, c, a, p, s, n, d, q." << endl;
            break;
        }
    } while (toupper(cResponse) != 'Q');
}

void makeShape(AShape* &sh) {
    delete sh;
    sh = ShapeFactory::makeShape(ShapeFactory::promptShapeType());
    sh->promptAndSetDimensions();
}

void clearShape(AShape* &sh) {
    delete sh;
    sh = ShapeFactory::makeShape();
}

void printArea(AShape* sh) {
    cout << "Area: " << sh->area() << endl;
}

void printPerimeter(AShape* sh) {
    cout << "Perimeter: " << sh->perimeter() << endl;
}

void scaleShape(AShape* sh) {
    sh->scale(promptDoubleGE("Scale factor?", 0.0));
}

void displayShape(AShape* sh) {
    sh->display(cout);
}

