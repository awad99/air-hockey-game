#include <iostream>
#include <string>
#include "Globa.h"


class gameStats {
private:
    int _totalGamesPlayed = 0;
    int _totalTimePlayed = 0;
    int _totalGoalsScored = 0;

    int _PlayGame = 0, _Golasadd = 0,_Wingames = 0;
public:
    // Add game data
    void addGameData(int difficulty, int time, int goals,bool WinGame) {
        switch (difficulty)
        {
        case 1:
            easyGame(time, goals, WinGame);
            break;
        case 2:
            MidumeGame(time, goals, WinGame);
            break;
        case 3:
            HardGame(time, goals, WinGame);
            break;
        default:
            easyGame(time, goals, WinGame);
        }
    }
    void easyGame(int time,int golas,bool WinGame) {
        if (WinGame == true) {
            _Wingames++;
            _PlayGame++;
            _Wingame = true;
            _Golasadd = golas;
        }
        else {
            _PlayGame++;
            _Wingame = false;
            _Golasadd = golas;
        }
    }

    void MidumeGame(int time, int golas, bool WinGame) {
        if (WinGame == true) {
            _Wingames++;
            _PlayGame++;
            _Wingame = true;
            _Golasadd = golas;
        }
        else {
            _PlayGame++;
            _Wingame = false;
            _Golasadd = golas;
        }
    }
    void HardGame(int time, int golas, bool WinGame) {
        if (WinGame == true) {
            _Wingames++;
            _PlayGame++;
            _Wingame = true;
            _Golasadd = golas;
        }
        else {
            _PlayGame++;
            _Wingame = false;
            _Golasadd = golas;
        }
    }

    int TotalTime() {
       return _totalTimePlayed += Timer;
    }
    int totalGamePlay() {
        return _totalGamesPlayed += _PlayGame;
    }

    int totalGoalsScored() {
       return _totalGoalsScored += _Golasadd;
    }
    // Calculate average goals
    int averageGoals()  {
        return _totalGamesPlayed == 0 ? 0.0 : totalGoalsScored() / _totalGamesPlayed;
    }

    // Print statistics for a specific difficulty
    void printDifficultyStats(int dfficult,int Time)  {
        std::string level = "";
        switch (dfficult) {
        case 1:
            level = "Easy";
            break;
        case 2:
            level = "Midume";
            break;
        case 3:
            level = "Hard";
            break;
        default:
            level = "Easy";
            break;
        }
        std::cout << level << "\n";
        std::cout << "-----------------------\n";
        std::cout << "Games played : " << _PlayGame << "\n";
        std::cout << "Time played  : " << Time << " minutes\n";
        std::cout << "Goals scored : " << _Golasadd << "\n";
        std::cout << "-----------------------\n";
    }

    // Print overall statistics
    void printGameStatistics(int dfficult,int Time)  {
        std::cout << "\nGame Statistics\n";
        std::cout << "-----------------------\n";
        std::cout << "Total games played : " << totalGamePlay() << "\n";
        std::cout << "Total time played  : " << TotalTime() << " minutes\n";
        std::cout << "Average goals      : " << averageGoals() << "\n";
        std::cout << "-----------------------\n";
    }
    void printallGame(int dfficult, int Time) {
        for (int i = 0; i < _PlayGame; i++) {
            printDifficultyStats(dfficult, Time);
        }
    }
};
