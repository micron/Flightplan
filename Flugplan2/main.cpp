#include "main.h"

int main (void)
{
	system("cls");
	cout << "Dies ist eine Flugplanverwaltung!\n\n";

	TFlightplan * flightplan = new TFlightplan;
	TFlightdata * tempFlightdata = NULL;

	bool ende = false;

	mainMenue ();
	

	do
	{
		if (_kbhit())
		{
			int flightnumber = 0;
			// flightnumbers to be switched
			int firstFlightNumber = 0;
			int secondFlightNumber = 0;
			// sortby Option
			int sortBy;

			char str = _getch();
			switch (str)
			{
			case '1':
				system("cls");
				outputFlightPlan(flightplan);
				backToMenue(true);
				break;
			case '2': 
				system("cls");
				tempFlightdata = new TFlightdata;
				inputFlightdata (tempFlightdata);
				flightplan->newFlight(tempFlightdata);
				backToMenue(false);
				break;
			case '3':
				system("cls");
				outputFlightPlan(flightplan);
				cout << "\nBitte die zu aendernde Flugnummer eingeben: ";
				cin >> flightnumber;
				cin.ignore();
				flightplan->searchFlight(flightnumber);
				if (flightplan->getCurrent())
					inputFlightdata(flightplan->getCurrent()->getFlightdata());
				backToMenue(0);
				break;
			case '4':
				system("cls");
				cout << "Bitte die zu loeschende Flugnummer eingeben: ";
				cin >> flightnumber;
				flightplan->searchFlight(flightnumber);
				if (flightplan->getCurrent())
				{
					flightplan->removeFlight();
					backToMenue(false);
				}
				else
					backToMenue(true);
				break;
			case 'a':
				system("cls");
				outputFlightPlan(flightplan);
				cout << "Bitte die erste Flugnummer eingeben: ";
				cin >> firstFlightNumber;
				cout << "Bitte die zweite Flugnummer eingeben: ";
				cin >> secondFlightNumber;
				flightplan->switchFlights(firstFlightNumber, secondFlightNumber);
				
				backToMenue(true);
				break;
			case 'b':
				system("cls");
				sortingMenu();
				cin >> sortBy;
				flightplan->sortFlightplan(sortBy);
				backToMenue(true);
				break;
			case '5': 
				system("cls");
				cout << "Fluege wurden exportiert";
				exportFlightPlan(flightplan);
				backToMenue(true);
				break;
			case '6':
				system("cls");
				importFlightplan(flightplan);
				cout << "Fluege wurden importiert";
				backToMenue(true);
				break;
			case '7': 
				system("cls");
				flightplan->clear();
				cout << "Flugplan wurde geloescht" << endl;
				backToMenue(true);
				break;
			case '8': break;
			case '9': ende = true; break;
			}
		}
		Sleep(50);
	}while (!ende);

	//pause();

	delete flightplan;
	return 0;
}

void pause (void)
{
	
	while(!_kbhit())
	{
		Sleep(50);
	};
	_getch();
}

