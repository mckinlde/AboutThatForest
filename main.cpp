#include <iostream>
#include <algorithm>
#include "Forest.h"
#include "Player.h"
#include <chrono>
#include <random>

int main()
{
    std::string choice;
    std::string filename;

    std::cout << "Forest creation and grow testing!\n" << std::endl;

    do
    {
        std::cout << "Please enter name of file containing the Forest: ";
        std::cin >> filename;
        Forest newForest(filename); // create a Forest object
        std::cout << "Here is the Forest :\n" << newForest.toString()
                  << std::endl;
        do
        {
            std::cout << "\nDo you want to grow the forest? (Y|N)" << std::endl;
            std::cin >> choice;
            newForest.grow();
            std::cout << "Here is the grown Forest :\n" << newForest.toString()
                      << std::endl;
        }while(choice.at(0)=='Y' || choice.at(0)=='y');

        // TODO let's make an array of players

        // TODO rounds of all players cutting trees, followed by flood


        Player player1; // make a player

        do {std::cout << "\nanother round? (Y|N)" << std::endl;
            std::cin >> choice;
            /*
            // try to cut down a tree
            if(player1.cutTree(0,2,newForest)){ // test1.txt top left
                player1.setActions(player1.getActions()-1); // cutting a tree takes 1 action
                player1.setWealth(player1.getWealth()+10); // and gives $10
            }else{
                std::cout<<"Player1 failed to cut tree"<<std::endl;
            }
            // try to harvest a tree
            if(player1.harvest(1,2,newForest)){ // test1.txt top center
                player1.setActions(player1.getActions()-1); // harvesting a tree takes 1 action
                player1.setWealth(player1.getWealth()+1); // and gives $1
            }else{
                std::cout<<"Player1 failed to harvest tree"<<std::endl;
            }
            // try to plant a tree
            if(player1.plant(2,2,newForest)){ // test1.txt top right
                player1.setActions(player1.getActions()-1); // cutting a tree takes 2 actions
            }else{
                std::cout<<"Player1 failed to plant tree"<<std::endl;
            }
             */
            // make a move
            player1.takeTurn(newForest, 0);

            std::cout << "Here is the new Forest :\n" << newForest.toString()
                      << std::endl;

            // now run a flood

            //need dimensions of forest
            size_t numRows = newForest.getNumRows();
            size_t numCols = newForest.getNumCols();

            //and array of flood values
            //int* floods = new int[numRows]; // must allocate memory in the heap using new
            int floods [3] = {};

            for(int i = 0; i<numRows; i++){
                // make a random flood value
                floods[i] = rand() % 40 + 1; // fully-grown row garunteed to not flood
            }
            // display flood before going through forest
            std::cout<<"flood before forest for player1: "<<floods[numRows-1]<<std::endl;

            for(int y=numRows-1;y>=0;y--) // for all rows top to bottom
            {
                for(int x=0;x<numCols;x++) // all columns left to right 
                {
                    floods[y] = floods[y] - newForest.get(x,y); // subtract treevalue from flood
                }
            }
            // print player wealth values and flood value
            std::cout<<"Player1 before flood: "<<player1.getWealth()<<std::endl
                     <<"flood after forest for player1: "<<floods[numRows-1]<<std::endl;
            // subtract floodValue from player wealth, can't add to wealth
            if(floods[numRows-1] > 0) {
                player1.setWealth(player1.getWealth() - floods[numRows-1]);
            }
            std::cout<<"Player1 after flood: "<<player1.getWealth()<<std::endl;


            //delete[] floods; // clean up floods array

            // now grow the forest for the next round
            newForest.grow();



        }while(choice.at(0)=='Y' || choice.at(0)=='y');


        // do-while loop template
        do {}while(choice.at(0)=='Y' || choice.at(0)=='y');


        std::cout << "\nDo you want to look at another forest? (Y|N)" << std::endl;
        std::cin >> choice;
    }while(choice.at(0)=='Y' || choice.at(0)=='y');


    return 0;
}


