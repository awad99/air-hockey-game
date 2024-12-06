#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValdate.h"
#include "clsScreen.h"
#include "clsGameplay.h"
#include "clsSettingGame.h"
#include "clsHreaderPlayGame.h"
#include "Globa.h"
#include "infoplaygame.h"
clsHreaderPlayGame::enHreaderlevel infoplaygame::Hreaderlevel = clsHreaderPlayGame::enHreaderlevel::easy;
class clsmainMuneScreen : protected clsScreen{
private:
	enum enMainOption { playgame = 1,setting = 2, Topscore = 3,infoGame = 4,exit = 5};

	static void GoBackMainMenu() {
		system("pause>0");
		system("cls");
		ShowMainMenuScreen();
	}
	
	static void PlayGame() {
		//std::cout << "play Game will be here\n";
		//clsGameplay::PlayGame(input1,input2,input3,input4);
		clsHreaderPlayGame::ShowlevelplayGame();
	}

	static void Setting() {
	//std::cout << "seting will be here\n";
		clsSettingGame::settingGame(input1,input2,input3,input4);
	}
	static void exit1() {

	}
	static void TopScroe() {
		std::cout << "the Top Wingame without lost is : " << CounterWinGame << std::endl;
	}
	static void infoplayer() {
		infoplaygame::InfoPlay();
	}
	static short ReadOptions() {
		short ReadOptions;
		std::cout << setw(37) << left << "" << "Enter what do you wnat to do[1 - 5]: ";
		ReadOptions = clsInputValidate::ReadshortNumber();
		if (ReadOptions < 1 || ReadOptions > 5) {
			std::cout << "\n the Number not on range please try again:";
			ReadOptions = clsInputValidate::ReadshortNumber();
		}
		return ReadOptions;
	}

	static void ReadOptionsfromMain(enMainOption MainOption) {
		switch (MainOption)
		{
		case clsmainMuneScreen::playgame:
			system("cls");
			PlayGame();
			GoBackMainMenu();
			break;
		case clsmainMuneScreen::setting:
			system("cls");
			Setting();
			GoBackMainMenu();
			break;
		case clsmainMuneScreen::Topscore:
			system("cls");
			TopScroe();
			GoBackMainMenu();
			break;
		case clsmainMuneScreen::infoGame:
			system("cls");
			infoplayer();
			GoBackMainMenu();
			break;
		case clsmainMuneScreen::exit:
			system("cls");
			exit1();
		}
	}
public:
	static void ShowMainMenuScreen() {
		_DrawScreenHeader("\t The best Game");
		std::cout << setw(37) << left  << "" << "____________________________________\n";
		std::cout << setw(37) << left << "" << "\t[1]PlayGame\n";
		std::cout << setw(37) << left << "" << "\t[2]Setting\n";
		std::cout << setw(37) << left << "" << "\t[3]Best Score\n";
		std::cout << setw(37) << left << "" << "\t[4]info Game\n";
		std::cout << setw(37) << left << "" << "\t[5]exit Game\n";
		std::cout << setw(37) << left << "" << "____________________________________\n";

		ReadOptionsfromMain((enMainOption)ReadOptions());
	}
};