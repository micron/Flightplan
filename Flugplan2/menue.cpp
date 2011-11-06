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

	cout << "Flugnummer (" << tempFlightdata->number << "): ";
	getline(cin, tempString);
	tempInt = atoi(tempString.c_str());
	if (tempInt != 0)
		tempFlightdata->number = tempInt;

	cout << "Flugziel (" << tempFlightdata->destination << "): ";
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

void importFlightplan(TFlightplan * flightplan)
{
	ifstream tempInput;

	tempInput.open("export.txt");

	TFlightdata * tempFlightdata = 0;


	string temp;
	getline(tempInput, temp);

	while (!tempInput.eof())
		newFlight(flightplan, importFlight(&tempInput));
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
	TFlightdata * tempFlightdata = createFlightdata();

	string tempString, readString = "";

	getline(*tempInput, readString);

	tempString = readSubString (&readString);
	tempFlightdata->number = atoi(tempString.c_str());

	tempString = readSubString (&readString);
	tempFlightdata->destination = tempString;

	tempString = readSubString (&readString);
	tempFlightdata->time = tempString;

	tempString = readSubString (&readString);
	tempFlightdata->rollway = atoi(tempString.c_str());

	tempString = readSubString (&readString);
	tempFlightdata->pilot = tempString;
	
	tempString = readSubString (&readString);
	tempFlightdata->numberplate = tempString;

	return tempFlightdata;
};


string outputFlight (TFlightplan * flightplan) //sollte gehen
{
	string out = "";
	ostringstream temp;

	temp << flightplan->current->data->number;
	out += temp.str() + '\t';
	out += flightplan->current->data->destination + '\t';
	out += flightplan->current->data->time + '\t';
	temp.str("");
	temp << flightplan->current->data->rollway;
	out += temp.str() + '\t';
	out += flightplan->current->data->pilot + '\t';
	out += flightplan->current->data->numberplate;
	
	if (flightplan->current != flightplan->last)
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

	jsonFile << "{\"flightdata\":{\"count\":" << flightplan->count << "},";
	jsonFile << "{\"flights\":";

	jsFile << "var flights = [];";

	if(flightplan->count != 0){
		flightplan->current = flightplan->first;

		do{
			exportFile << outputFlight(flightplan).c_str();
			// html stuff
			htmlFile << "<tr><td>" << flightplan->current->data->number << "</td>";
			htmlFile << "<td>" << flightplan->current->data->destination.c_str() << "</td>";
			htmlFile << "<td>" << flightplan->current->data->time.c_str() << "</td>";
			htmlFile << "<td>" << flightplan->current->data->rollway << "</td>";
			htmlFile << "<td>" << flightplan->current->data->pilot.c_str() << "</td>";
			htmlFile << "<td>" << flightplan->current->data->numberplate.c_str() << "</td></tr>";
			//json stuff
			jsonFile << "{\"" << count << "\":{";
			jsonFile << "\"number\":" << "\"" << flightplan->current->data->number << "\",";
			jsonFile << "\"destination\":" << "\"" << flightplan->current->data->destination.c_str() << "\",";
			jsonFile << "\"time\":" << "\"" << flightplan->current->data->time.c_str() << "\",";
			jsonFile << "\"rollway\":" << "\"" << flightplan->current->data->rollway << "\",";
			jsonFile << "\"pilot\":" << "\"" << flightplan->current->data->pilot.c_str() << "\",";
			jsonFile << "\"numberplate\":" << "\"" << flightplan->current->data->numberplate.c_str() << "\"";

			
			jsFile << "flights.push({number:'" << flightplan->current->data->number << "',";
			jsFile << "destination:'" << flightplan->current->data->destination.c_str() << "',";
			jsFile << "time:'" << flightplan->current->data->time.c_str() << "',";
			jsFile << "rollway:'" << flightplan->current->data->rollway << "',";
			jsFile << "pilot:'" << flightplan->current->data->pilot.c_str() << "',";
			jsFile << "numberplate:'" << flightplan->current->data->numberplate.c_str() << "'});";

			count = count + 1;

			if(flightplan->count >= count){
				jsonFile << "}";
			}else{
				jsonFile << "},";
			}
			
			if(getnextFlight(flightplan->current)){
				nextFlight(flightplan);
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
	
	if (flightplan->count != 0)
	{
		flightplan->current = flightplan->first;
		do
		{
			cout << outputFlight (flightplan).c_str();
			if (getnextFlight(flightplan->current))
				nextFlight (flightplan);
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