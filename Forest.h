// File name: Forest.h
// Author: Douglas McKinley
// userid: mckinlde
// Email: douglas.e.mckinley@vanderbilt.edu
// Description:  Class that represents a Forest.
//    A Forest has walls, open locations, a start location, and an end location.
//    The initial Forest is read from a file.
//    The user can get and set the value at any given location from the Forest,
//    Locations are represented by x-y coordinates or Point objects.
//    The origin (0,0) is the lower left corner of the graph; the x-coordinate moves
//    left to right across the x axis; the y-coordinate moves bottom to top up the y axis.
// Last Changed:  11-20-2016


#ifndef ABF_Forest_H
#define ABF_Forest_H

#include <string>
#include <fstream>
#include <iostream>
#include "Point.h"


const int MAX_ROWS = 50;
const int MAX_COLS = 50;

class Forest
{
public:
    // Constructor
    // Accepts file name as a parameter
    // Reads the file and initializes start and end location and Forest Matrix and visited matrix
    Forest (std::string filename);

    // printForest
    // Prints current Forest to console
    void printForest() const;

    // toString
    // convert Forest to a string representation
    std::string toString() const;

    // Get the Forest dimensions
    int getNumRows() const;
    int getNumCols() const;

    // Get an item at the given coodinates from the Forest matrix.
    // Throws std::range_error if the coordinates are not within the Forest bounds
    int get (int x, int y) const;
    int get (Point location) const;

    // Grow all valid trees in the forest (at least planted (1) but not grown (4))
    void grow ();


    // Set an item in the Forest matrix at the given coodinates.
    // Throws std::range_error if the coordinates are not within the Forest bounds
    // Returns false and doesn't change if you set ouside range [0 : 4], else true
    bool set (int new_item, int x, int y);
    bool set (int new_item, Point location);


private:

    // height and width of the Forest
    int numRows;
    int numCols;

    // Forest's matrix storage buffer.  Using static arrays -- Big 3 not required
    char ForestMatrix[MAX_COLS][MAX_ROWS];

    // Private helper function to insure x & y are within the Forest
    void checkRange(int x, int y) const;

};
#endif /* ifndef */
