//
// Created by Douglas McKinley on 10/26/16.
//

#ifndef ABF_PLAYER_H
#define ABF_PLAYER_H

#include "Forest.h"
#include "Point.h"


class Player {

private:

    // player stats
    int wealth;
    int gains;
    size_t actions;
    // move weighting
    int cWeight;
    int pWeight;


    // cutTree takes a point of location for tree to be cut, uses Forests' set() method
    bool cutTree(int x, int y, Forest& forest);
    bool cutTree(Point location, Forest& forest);

    // harvest takes a point of location for tree to be cut, uses Forests' set() method
    bool harvest(int x, int y, Forest& forest);
    bool harvest(Point location, Forest& forest);

    // plant takes a point of location for tree to be cut, uses Forests' set() method
    bool plant(int x, int y, Forest& forest);
    bool plant(Point location, Forest& forest);

    // learn is private, player looks at any damages and gains and updates wealth and move weighting
    // takes damages as a parameter from a flood, uses gains as tracked during turn
    void learn(int damages);

public:
    // ctor, initializes player with 0 wealth and 10 actions
    Player();

    // get methods
    int getWealth();
    size_t getActions();

    // set methods
    void setWealth(int newWealth);
    void setActions(size_t newActions);

    // takeTurn takes a column # and Forest to act on
    // sets actions to 10, stochastically assigns actions to the three move types
    // steps along given column trying to move until all possible moves are used,
    //  either by legality or running out of actions
    void takeTurn(Forest& forest, size_t col);

};


#endif //ABF_PLAYER_H
