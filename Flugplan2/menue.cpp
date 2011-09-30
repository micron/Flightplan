#include "menue.h"
#include "main.h"

void mainMenue (void)
{
	system("cls");
	cout << "Flugplanverwaltung - Copyright 2011\n";
	cout << "          by Pascal Ott and Miron Ogrodovice\n\n";
	cout << "============================================\n";
	cout << "(1)\t aktuellen Flugplan ausgeben\n";
	cout << "--------------------------------------------\n";
	cout << "(2)\t neuen Flug anlegen\n";
	cout << "(3)\t einen Flug aendern\n";
	cout << "(4)\t einen Flug loeschen\n";
	cout << "--------------------------------------------\n";
	//cout << "(5)\t neuen Flug anlegen\n";
	//cout << "(6)\t neuen Flug anlegen\n";
	//cout << "(7)\t neuen Flug anlegen\n";
	cout << "(9)\t Flugplanverwaltung beenden\n";
	cout << "============================================\n";
}

void inputFlightdata (TFlightdata * tempFlightdata)
{
	int tempInt = 0;
	string tempString = "";

	cout << "Flugnummer (" << tempFlightdata->number << "): ";
	getline(cin, tempString);
	tempInt = atoi(tempString.c_str());
	if (tempInt != 0)
		tempFlightdata->number = tempInt;

	cout << "Flug Ziel (" << tempFlightdata->destination << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->destination = tempString;

	cout << "Zeit (" << tempFlightdata->time << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->time = tempString;

	cout << "Rollbahn (" << tempFlightdata->rollway << "): ";
	getline(cin, tempString);
	tempInt = atoi(tempString.c_str());
	if (tempInt != 0)
		tempFlightdata->rollway = tempInt;

	cout << "Pilot (" << tempFlightdata->pilot << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->pilot = tempString;

	cout << "Flugkennung (" << tempFlightdata->numberplate << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->numberplate = tempString;

};

void backToMenue (bool mitPause)
{
	if (mitPause)
	{
		cout << "\nBitte eine Taste druecken um zum Menue zurueck zukehren...";
		pause();
	}
	mainMenue();
}