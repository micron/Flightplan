#include "menue.h"
#include "main.h"

void mainMenue (void)
{
	system("cls");
	cout << "Flugplanverwaltung - Copyright 2011\n";
	cout << "          by Pascal Ott and Miron Ogrodowicz\n\n";
	cout << "============================================\n";
	cout << "(1)\t aktuellen Flugplan ausgeben\n";
	cout << "--------------------------------------------\n";
	cout << "(2)\t neuen Flug anlegen\n";
	cout << "(3)\t einen Flug aendern\n";
	cout << "(4)\t einen Flug loeschen\n";
	cout << "(a)\t Fluege tauschen\n";
	cout << "(b)\t Fluege Sortieren\n";
	cout << "--------------------------------------------\n";
	cout << "(5)\t Flugplan exportieren\n";
	cout << "(6)\t Flugplan importieren\n";
	cout << "(7)\t Flugplan leeren\n";
	cout << "--------------------------------------------\n";
	//cout << "(7)\t neuen Flug anlegen\n";
	cout << "(9)\t Flugplanverwaltung beenden\n";
	cout << "============================================\n";
}

void sortingMenu (void)
{
	cout << "============================================\n";
	cout << "aufsteigend:\n";
	cout << "(1)  Flugnummer\n";
	cout << "(2)  Flugziel\n";
	cout << "(3)  Zeit\n";
	cout << "(4)  Rollbahn\n";
	cout << "(5)  Pilot\n";
	cout << "(6)  Flugkennung\n";
	cout << "--------------------------------------------\n";
	cout << "absteigend:\n";
	cout << "(7)  Flugnummer\n";
	cout << "(8)  Flugziel\n";
	cout << "(9)  Zeit\n";
	cout << "(10) Rollbahn\n";
	cout << "(11) Pilot\n";
	cout << "(12) Flugkennung\n";
	cout << "============================================\n\n";

	cout << "Bitte sortieroption eingeben: ";
}

void inputFlightdata (TFlightdata * tempFlightdata)
{
	int tempInt = 0;
	string tempString = "";

	cout << "Flugnummer (" << tempFlightdata->getNumber() << "): ";
	getline(cin, tempString);
	tempInt = atoi(tempString.c_str());
	if (tempInt != 0)
		tempFlightdata->setNumber(tempInt);

	cout << "Flugziel (" << tempFlightdata->getDestination() << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->setDestination(tempString);

	cout << "Zeit (" << tempFlightdata->getTime() << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->setTime(tempString);

	cout << "Rollbahn (" << tempFlightdata->getRollway() << "): ";
	getline(cin, tempString);
	tempInt = atoi(tempString.c_str());
	if (tempInt != 0)
		tempFlightdata->setRollway(tempInt);

	cout << "Pilot (" << tempFlightdata->getPilot() << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->setPilot(tempString);

	cout << "Flugkennung (" << tempFlightdata->getNumberplate() << "): ";
	getline(cin, tempString);
	if (tempString != "")
		tempFlightdata->setNumberplate(tempString);

};

void importFlightplan(TFlightplan * flightplan)
{
	ifstream tempInput;

	tempInput.open("export.txt");

	TFlightdata * tempFlightdata = 0;


	string temp;
	getline(tempInput, temp);

	while (!tempInput.eof())
		flightplan->newFlight(importFlight(&tempInput));
}

string readSubString (string * readString)
{
	string tempString = "";
	int e = 0;

	e = (*readString).find("\t", 0);
	tempString = (*readString).substr(0, e);
	(*readString).erase(0, e+1);

	return tempString;
}

TFlightdata * importFlight (ifstream  * tempInput)
{
	TFlightdata * tempFlightdata = new TFlightdata;

	string tempString, readString = "";

	getline(*tempInput, readString);

	tempString = readSubString (&readString);
	tempFlightdata->setNumber(atoi(tempString.c_str()));

	tempString = readSubString (&readString);
	tempFlightdata->setDestination (tempString);

	tempString = readSubString (&readString);
	tempFlightdata->setTime (tempString);

	tempString = readSubString (&readString);
	tempFlightdata->setRollway (atoi(tempString.c_str()));

	tempString = readSubString (&readString);
	tempFlightdata->setPilot (tempString);
	
	tempString = readSubString (&readString);
	tempFlightdata->setNumberplate (tempString);

	return tempFlightdata;
};


string outputFlight (TFlightplan * flightplan) //sollte gehen
{
	string out = "";
	ostringstream temp;

	temp << flightplan->getCurrent()->getFlightdata()->getNumber();
	out += temp.str() + '\t';
	out += flightplan->getCurrent()->getFlightdata()->getDestination() + '\t';
	out += flightplan->getCurrent()->getFlightdata()->getTime() + '\t';
	temp.str("");
	temp << flightplan->getCurrent()->getFlightdata()->getRollway();
	out += temp.str() + '\t';
	out += flightplan->getCurrent()->getFlightdata()->getPilot() + '\t';
	out += flightplan->getCurrent()->getFlightdata()->getNumberplate();
	
	if (flightplan->getCurrent() != flightplan->getLast())
		out += '\n';

	return out;
};

void exportFlightPlan (TFlightplan * flightplan){
	ofstream exportFile, htmlFile, jsonFile, jsFile;
	int count = 0;
	bool ende = false;
	exportFile.open("export.txt");
	htmlFile.open("export-html.html");
	jsonFile.open("flightdata.json");
	jsFile.open("flightdata.js");
	
	exportFile << "Flugnr.\t" << "Flug Ziel\t" << "Zeit\t" << "Rollbahn\t" << "Pilot\t" << "Flugkennung\n";
	
	htmlFile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
	htmlFile << "<html><head><title>Flugdaten HTML Export</title></head><body><table border=\"1\"><tr>";
	htmlFile << "<td>Flugnummer</td><td>Flug Ziel</td><td>Zeit</td><td>Rollbahn</td><td>Pilot</td><td>Flugkennung</td></tr>";

	jsonFile << "{\"flightdata\":{\"count\":" << flightplan->getCount() << "},";
	jsonFile << "{\"flights\":";

	jsFile << "var flights = [];";

	if(flightplan->getCount() != 0){
		flightplan->setCurrent(flightplan->getFirst());

		do{
			exportFile << outputFlight(flightplan).c_str();


			// html stuff
			htmlFile << "<tr><td>" << flightplan->getCurrent()->getFlightdata()->getNumber() << "</td>";
			htmlFile << "<td>" << flightplan->getCurrent()->getFlightdata()->getDestination().c_str() << "</td>";
			htmlFile << "<td>" << flightplan->getCurrent()->getFlightdata()->getTime().c_str() << "</td>";
			htmlFile << "<td>" << flightplan->getCurrent()->getFlightdata()->getRollway() << "</td>";
			htmlFile << "<td>" << flightplan->getCurrent()->getFlightdata()->getPilot().c_str() << "</td>";
			htmlFile << "<td>" << flightplan->getCurrent()->getFlightdata()->getNumberplate().c_str() << "</td></tr>";
			//json stuff
			jsonFile << "{\"" << count << "\":{";
			jsonFile << "\"number\":" << "\"" << flightplan->getCurrent()->getFlightdata()->getNumber() << "\",";
			jsonFile << "\"destination\":" << "\"" << flightplan->getCurrent()->getFlightdata()->getDestination().c_str() << "\",";
			jsonFile << "\"time\":" << "\"" << flightplan->getCurrent()->getFlightdata()->getTime().c_str() << "\",";
			jsonFile << "\"rollway\":" << "\"" << flightplan->getCurrent()->getFlightdata()->getRollway() << "\",";
			jsonFile << "\"pilot\":" << "\"" << flightplan->getCurrent()->getFlightdata()->getPilot().c_str() << "\",";
			jsonFile << "\"numberplate\":" << "\"" << flightplan->getCurrent()->getFlightdata()->getNumberplate().c_str() << "\"";

			
			jsFile << "flights.push({number:'" << flightplan->getCurrent()->getFlightdata()->getNumber() << "',";
			jsFile << "destination:'" << flightplan->getCurrent()->getFlightdata()->getDestination().c_str() << "',";
			jsFile << "time:'" << flightplan->getCurrent()->getFlightdata()->getTime().c_str() << "',";
			jsFile << "rollway:'" << flightplan->getCurrent()->getFlightdata()->getRollway() << "',";
			jsFile << "pilot:'" << flightplan->getCurrent()->getFlightdata()->getPilot().c_str() << "',";
			jsFile << "numberplate:'" << flightplan->getCurrent()->getFlightdata()->getNumberplate().c_str() << "'});";

			count = count + 1;

			if(flightplan->getCount() >= count){
				jsonFile << "}";
			}else{
				jsonFile << "},";
			}
			
			if(flightplan->getCurrent()->getnextFlight()){
				flightplan->nextFlight();
			}
			else
				ende = true;
			
		}while(!ende);	
	}
	jsonFile << "}}}}";
	htmlFile << "</table></body></html>";

	htmlFile.close();
	jsonFile.close();
	jsFile.close();
	exportFile.close();

};

void outputFlightPlan (TFlightplan * flightplan)
{
	bool ende = false;
	cout << "Flugnr.\t" << "Flug Ziel\t" << "Zeit\t" << "Rollbahn\t" << "Pilot\t" << "Flugkennung\n";
	
	if (flightplan->getCount() != 0)
	{
		flightplan->setCurrent(flightplan->getFirst());
		do
		{
			cout << outputFlight (flightplan).c_str();
			if (flightplan->getCurrent()->getnextFlight())
				flightplan->nextFlight ();
			else
				ende = true;
		}while (!ende);
	}
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