// File name: Forest.cpp
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


#include <stdexcept>
#include <cstdlib>
#include "Forest.h"

// Constructor
// Accepts file name as a parameter
// Reads the file and initializes start and end location and Forest Matrix and visited matrix
Forest::Forest (std::string filename)
{

    std::string str;

    std::ifstream file(filename.c_str());
    // Do error checking here
    if (!file) {
        std::cout << "Unable to open file. Press enter to exit program.";
        getline(std::cin, str);  // consume existing line
        std::cin.get();  // get the key press
        exit(1);
    }

    Point doesNotExist(-1,-1);

    // file starts with number of rows & cols; read them in
    file >> numRows;
    file >> numCols;
    getline(file, str);  // consume rest of first line

    if (numRows<0 || numRows>MAX_ROWS || numCols<0 || numCols>MAX_COLS) {
        std::cout << "File contains invalid size specification for the Forest. "
                  << "Press enter to exit program.";
        getline(std::cin, str);  // consume rest of existing line
        std::cin.get();  // get the key press
        exit(1);
    }


    int y=numRows-1;
    while( getline(file, str) )
    {
        if (str.length()!=numCols) {
            std::cout << "File contained a line with incorrect number of characters"
                      << std::endl;
            std::cout << "Ignoring this line: " << str << std::endl;
            std::cout << "Row = " << y << std::endl;
            continue;
        }


        // Initialize the Forest matrix
        for(int x=0;x<numCols;x++)
        {
            char ch = str.at(x);
            int ich = ch - '0';
            set(ich,x,y);
        }
        y--;
        if(y<0)
            break;
    }
    if (y != -1) {
        std::cout << "File did not contain the correct number of rows." << std::endl;
        std::cout << "Unpreditable results may occur." << std::endl;
    }

    file.close();

}

//printForest
//Prints current Forest to console
void Forest::printForest() const
{
    std::cout << toString() << std::endl;
}

// toString
// convert Forest to a string representation
std::string Forest::toString() const
{
    std::string result;
    for(int y=numRows-1;y>=0;y--)
    {
        for(int x=0;x<numCols;x++)
        {
            result += '0' + ForestMatrix[x][y];
        }
        result += '\n';
    }

    return result;
}

// Get the Forest dimensions
int Forest::getNumRows() const
{
    return numRows;
}

int Forest::getNumCols() const
{
    return numCols;
}


// Private helper function to insure row & col are within the Forest
void Forest::checkRange(int x, int y) const
{
    if(y<0 || y>=this->numRows || x<0 || x>=this->numCols)
    {
        throw std::range_error("Forest:: Index is out of range");
    }
}


// Set an item in the Forest matrix at the given coodinates.
// Throws std::range_error if the coordinates are not within the Forest bounds
// Returns false and doesn't change if you set outside range [0 : 4], else true
bool Forest::set (int new_item, int x, int y)
{
    checkRange(x, y);
    if(new_item >= 0 && new_item <= 4){ // tree values can only be between 0 and 4
        ForestMatrix[x][y] = new_item;
        return true;
    }
    return false;
}

bool Forest::set (int new_item, Point location)
{
    return set(new_item, location.x, location.y);
}


// Get an item at the given coodinates from the Forest matrix.
// Throws std::range_error if the coordinates are not within the Forest bounds
int Forest::get (int x, int y) const
{
    checkRange(x, y);
    return ForestMatrix[x][y];

}

int Forest::get (Point location) const
{
    return get(location.x, location.y);
}

// Grow all valid trees in the forest
void Forest::grow ()
{
    for(int y=numRows-1;y>=0;y--) // for all trees in the forest
    {
        for(int x=0;x<numCols;x++)
        {
            int tree = get(x,y);
            if(tree > 0 && tree < 4) // must be at least planted (1) & not grown (4)
            {
                set(tree + 1, x, y); // increment value
            }
        }
    }

}
