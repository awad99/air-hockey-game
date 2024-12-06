#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValdate.h"
#include "clsGameplay.h"
#include "clsScreen.h"
#include "Globa.h"
#include "MainMenueScreen.h"
class clsHreaderPlayGame : protected clsScreen
{
private:
	static short _ReadHreaderPositionsNumber() {
		std::cout << setw(37) << " " << "please enter a number from [1-3] :";
		short levelgame = clsInputValidate::ReadshortNumber();
		while (levelgame < 1 || levelgame > 3) {
			std::cout << "\nthis number not from [1-3] : ";
			short levelgame = clsInputValidate::ReadshortNumber();
		}
		return levelgame;
	}
protected:
	static enum enHreaderlevel { easy = 1, midune = 2, hrad = 3 };

	static short _ReadlevelGame(short level) {

		if (level == 1) {
			system("cls");
			clsGameplay::levelGameplay(1);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			return 1;
		}
		else if (level == 2) {
			system("cls");
			clsGameplay::levelGameplay(2);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			return 2;
		}
		else if (level == 3) {
			system("cls");
			clsGameplay::levelGameplay(3);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			return 3;
		}
		else {
			system("cls");
			clsGameplay::levelGameplay(1);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			return 1;
		}
		levelgame = level;
	}
public:
	static void ShowlevelplayGame() {
		_DrawScreenHeader("\t level GamePlay");

		std::cout << setw(37) << left << " " << "\t[1]Easy\n";
		std::cout << setw(37) << left << " " << "\t[2]Midume\n";
		std::cout << setw(37) << left << " " << "\t[3]Hard\n";

		levelgame = _ReadHreaderPositionsNumber();
		_ReadlevelGame(levelgame);
	}
};







/*
	static int _ReadlevelGame(enHreaderlevel HreaderGame) {
		switch (HreaderGame)
		{
		case clsHreaderPlayGame::easy:
			system("cls");
			clsGameplay::levelGameplay(1);
			clsGameplay::PlayGame(input1,input2,input3,input4);
			break;
			return 1;
		case clsHreaderPlayGame::midune:
			system("cls");
			clsGameplay::levelGameplay(2);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			break;
			return 2;
		case clsHreaderPlayGame::hrad:
			system("cls");
			clsGameplay::levelGameplay(3);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			break;
			return 3;
		default:
			system("cls");
			clsGameplay::levelGameplay(1);
			clsGameplay::PlayGame(input1, input2, input3, input4);
			break;
			return 1;
		}
	}
*/