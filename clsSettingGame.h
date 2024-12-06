#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValdate.h"
#include "clsScreen.h"
class clsSettingGame
{
private:
	static char ReadInputLeft(char& input1) {
		std::cout << "Enter a left input(A-Z) : ";
		input1 = clsInputValidate::Readchar();
		if (input1 < 'A' || input1 > 'Z') {
			std::cout << "invliad charcter please enter from A to Z: ";
			input1 = clsInputValidate::Readchar();
		}
		return input1;
	}
	static char ReadInputRigth(char& input2) {
		std::cout << "Enter a Rigth input(A-Z): ";
		input2 = clsInputValidate::Readchar();
		if (input2 < 'A' || input2 > 'Z') {
			std::cout << "invalid charcter please enter from A to Z: ";
			input2 = clsInputValidate::Readchar();
		}
		return input2;
	}
	static char ReadInputTop(char& input3) {
		std::cout << "Enter a Top input(A-Z) : ";
		input3 = clsInputValidate::Readchar();
		if (input3 < 'A' || input3 > 'Z') {
			std::cout << "invliad charcter please enter from A to Z: ";
			input3 = clsInputValidate::Readchar();
		}
		return input3;
	}
	static char ReadInputDown(char& input4) {
		std::cout << "Enter a down input(A-Z) : ";
		input4 = clsInputValidate::Readchar();
		if (input4 < 'A' || input4 > 'Z') {
			std::cout << "invliad charcter please enter from A to Z: ";
			input4 = clsInputValidate::Readchar();
		}
		return input4;
	}
public:
	static void settingGame(char& inputleft, char& inputRigth,char& inputTop,char& inputdown) {
		ReadInputLeft(inputleft);
		ReadInputRigth(inputRigth);
		ReadInputTop(inputTop);
		ReadInputDown(inputdown);
	}
};

