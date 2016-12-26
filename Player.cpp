//
// Created by Douglas McKinley on 10/26/16.
//

#include "Player.h"

// ctor, initializes player with 0 wealth/gains/damages, 10 actions, and default weighting
Player::Player() : wealth(0), gains(0), actions(10), cWeight(3), pWeight(4){}

// get methods
int Player::getWealth(){
    return wealth;
}
size_t Player::getActions(){
    return actions;
}

// set methods
void Player::setWealth(int newWealth){
    wealth = newWealth;
}
void Player::setActions(size_t newActions){
    actions = newActions;
}

// cutTree takes a point of location for tree to be cut, uses Forests' set() method
// returns true if sucessful, else false
bool Player::cutTree(int x, int y, Forest& forest){
    try {
        int treevalue = forest.get(x,y);
        if(treevalue == 4){ // can only cut fully-grown trees
            return forest.set(0, x, y); // 'cut' tree by resetting treevalue to 0, set
            // will return bool true unless something crazy happens
        }
        return false; // if treevalue != 4, can't cut tree
    }catch (std::range_error){ // report error to console if out of range
        std::cout<<"cutTree range_error"<<std::endl;
        return false;
    }
}
bool Player::cutTree(Point location, Forest& forest){
    return cutTree(location.x, location.y, forest);
}

// harvest takes a point of location for tree to be cut, uses Forests' set() method
// returns true if sucessful, else false
bool Player::harvest(int x, int y, Forest& forest) {
    try {
        int treevalue = forest.get(x, y);
        if (treevalue == 4) { // can only harvest fully-grown trees

            return forest.set(3, x, y); // 'harvest' tree by resetting treevalue to 3, set
            // will return bool true unless something crazy happens
        }
        return false; // if treevalue != 4, can't harvest tree
    } catch (std::range_error) { // report error to console if out of range
        std::cout << "harvest range_error" << std::endl;
        return false;
    }
}
bool Player::harvest(Point location, Forest& forest){
    return harvest(location.x, location.y, forest);
}

// plant takes a point of location for tree to be cut, uses Forests' set() method
// returns true if successful, else false
bool Player::plant(int x, int y, Forest& forest){
    try {
        int treevalue = forest.get(x, y);
        if (treevalue == 0) { // can only plant on empty patches

            return forest.set(1, x, y); // 'plant' tree by resetting treevalue to 1, set
            // will return bool true unless something crazy happens
        }
        return false; // if treevalue != 0, can't plant tree
    } catch (std::range_error) { // report error to console if out of range
        std::cout << "plant range_error" << std::endl;
        return false;
    }
}
bool Player::plant(Point location, Forest& forest){
    return plant(location.x, location.y, forest);
}


// takeTurn takes a column # and Forest to act on
// sets actions to 10, stochastically assigns actions to the three move types
// steps along given column trying to move until all possible moves are used,
//  either by legality or running out of actions
void Player::takeTurn(Forest& forest, size_t row) {
    // assign weights
    int cuts = cWeight;
    int plants = pWeight;
    // players are selfish, so we try to cut trees in our row first
    while(actions > 0 && cuts > 0){
        for(int i = 0; i < 10; i++){ // for each patch in my row
            bool trigger = cutTree(i, row, forest);
            if(trigger){
                --actions; // subtract an action if we cut a tree
                --cuts;
                gains+=10; // add 10 to gains
            }
        }
    }
    // now plant
    while(actions > 0 && plants > 0){
        for(int i = 0; i < 10; i++){ // for each patch in my row
            bool trigger = plant(i, row, forest);
            if(trigger){
                actions-=2; // subtract 2 actions if we cut a tree
                --plants;
            }
        }
    }
    // now try to harvest whatever is left
    while(actions > 0){
        for(int i = 0; i < 10; i++){ // for each patch in my row
            bool trigger = harvest(i, row, forest);
            if(trigger){
                --actions; // subtract an action if we cut a tree
                gains+=1; // add 1 to gains
            }
        }
    }
}

void Player::learn(int damages) {
    // did we gain or lose money?
    if(damages > gains){
        // if lost, decrease cuts, increase plants based on weighted damages
        cWeight = cWeight - (damages-gains / damages);
        pWeight = pWeight + (damages-gains / damages);
    }
    if(damages > gains){
        // if gained, increase cuts, decrease plants based on weighted gains
        cWeight = cWeight - (gains-damages / gains);
        pWeight = pWeight + (gains-damages / gains);
    }
    // update wealth and reset gains
    wealth = wealth - damages + gains;
    gains = 0;
}


