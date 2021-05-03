// File: Shape/ShapeMain.hpp

#ifndef ShapeMain_hpp
#define ShapeMain_hpp

#include "AShape.hpp"

void initialize(AShape *shapes[], int cap);
// Pre: shapes[0..cap - 1] is allocated.
// Post: All shapes[0..cap - 1] are initialized to the null shape.

void cleanUp(AShape *shapes[], int cap);
// Pre: shapes[0..cap - 1] is allocated, and all elements are well-defined.
// Post: All shapes[0..cap - 1] are deleted and set to nullptr.

void promptLoop(AShape *shapes[], int cap);
// Loop to prompt the user with the top-level main prompt.
// Post: User has selected the quit option.

void makeShape(AShape *&sh);
// Prompts user for dimensions.
// Post: Original sh is deleted and new sh is created.

char shapeType();
// Prompts user for shape letter, lowercase or uppercase.
// Post: Uppercase character L, R, C, T, or M is returned.

void clearShape(AShape *&sh);
// Post: Original sh is deleted and sh is made the null shape.

void printArea(AShape *sh);
// Post: sh's area is printed to standard output.

void printPerimeter(AShape *sh);
// Post: The perimeter of this sh is printed to standard output.

void scaleShape(AShape *sh);
// Prompts user for scale factor.
// Post: sh's dimensions are multiplied by the factor.

void displayShape(AShape *sh);
// Post: sh's name and dimensions are printed to standard output.

#endif
