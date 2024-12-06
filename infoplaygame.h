#pragma once
#include <iostream>
#include <string>
#include "Fileinfo.h"
#include "clsHreaderPlayGame.h"
#include "clsQueueLine.h"
#include "Globa.h"
bool _WinOrNot = false;

class infoplaygame : protected clsHreaderPlayGame {
private:
     static clsHreaderPlayGame::enHreaderlevel Hreaderlevel;

public:
    static int infoplay() {
        gameStats gameStats1;

        // Determine the game level
        int currentLevel = levelgame;

        // Define the winning score for each level
        int winningScore = 0;
        switch (currentLevel) {
        case 1:
            winningScore = 3;
            break;
        case 2:
            winningScore = 5;
            break;
        case 3:
            winningScore = 7;
            break;
        default:
            std::cerr << "Invalid game level." << std::endl;
            return -1;
        }

        // Check if the player has won
        _WinOrNot = (ScorePlay1 == winningScore);

        // Update game stats
        gameStats1.addGameData(currentLevel, Timer, ScorePlay1, _WinOrNot);

        // Print game info
        Fileinfo::PrintInfo(Timer, ScorePlay1, currentLevel);

        gameStats1.printGameStatistics(currentLevel, Timer);

        std::cout << "\n\n";
        gameStats1.printallGame(currentLevel, Timer);
        return 0;
    }
     static int InfoPlay() {
         return infoplay();
     }
};
