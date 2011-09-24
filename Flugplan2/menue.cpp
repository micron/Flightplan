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
	cout << "Flugnummer: ";
	cin >> tempFlightdata->number;
	cin.ignore();

	cout << "Flug Ziel: ";
	getline(cin, tempFlightdata->destination);

	cout << "Zeit: ";
	getline(cin, tempFlightdata->time);

	cout << "Rollbahn: ";
	cin >> tempFlightdata->rollway;
	cin.ignore();

	cout << "Pilot: ";
	getline(cin, tempFlightdata->pilot);

	cout << "Flugkennung: ";
	getline(cin, tempFlightdata->numberplate);

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