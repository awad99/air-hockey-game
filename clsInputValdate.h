#pragma once
#include <iostream>
#include <string>
//#include "clsDate.h"
using namespace std;
class clsInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}
	static int ReadIntNumber(string ErrorMassge = "Invalid Number,try again") {
		int Number = 0;
		cout << "Enter a number\n";
		cin >> Number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max, '\n'));
			cout << ErrorMassge;
			cin >> Number;
		}
		return Number;
	}
	static short ReadshortNumber(string ErrorMassge = "Invalid Number,try again") {
		short Number = 0;
		//	cout << "Enter a number";
		cin >> Number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max, '\n'));
			cout << ErrorMassge;
			cin >> Number;
		}
		return Number;
	}
	static double ReadDblNumber(string ErrorMassge = "Invalid Number,try again") {
		double Number = 0;
		while (true) {
			//cout << "Enter a number: ";
			cin >> Number;

			if (cin.fail()) {
				cin.clear(); // Clear the error state
				cin.ignore((numeric_limits<streamsize>::max, '\n')); // Discard invalid input
				cout << ErrorMassge;
			}
			else {
				break; // Exit the loop if input is valid
			}
		}
		return Number;
	}
	static string ReadString(string ErrorMassage = "Error please try again") {
		string text;
		//cout << "please enter a text\n";
		getline(cin, text);
		return text;
	}
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again : \n") {
		double Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	static char Readchar(string ErrorMassage = "Error please try again") {
		char Input;
		cin >> Input;
		return Input;
	}

	/*
	bool IsdDateBetween(clsDate Date, clsDate From, clsDate To) {
		if (Date.IsDate1BeforeDate2(Date, To) || Date.IsDate1EqualDate2(Date, To) && (Date.IsDate1BeforeDate2(Date, From) || Date.IsDate1EqualDate2(Date, To))) {
			return true;
		}
		return false;
	}
	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}
	*/
};



