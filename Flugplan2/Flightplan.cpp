#include "Flightplan.h"

TFlightplan * createFlightplan (void) //geht /not tested
{
	TFlightplan * flightplan = new TFlightplan;
	flightplan->count = 0;
	flightplan->first = NULL;
	flightplan->current = NULL;
	flightplan->last = NULL;
	
	return flightplan;
}

void deleteFlightplan (TFlightplan * flightplan)//könnte fliegen gehen / not tested
{
	bool next = false;
	TFlight * tempFlight;

	if (flightplan->count != 0)
	{
		flightplan->current = flightplan->first;

		do
		{
			tempFlight = flightplan->current;
			next = nextFlight(flightplan);			
			deleteFlight(tempFlight);
			
		}while (next);
	}
	delete flightplan;
}

void newFlight (TFlightplan * flightplan, TFlightdata * flightdata)//könnte fliegen gehen /not testet
{
	//falls noch kein Flugvorhanden ist
	if (!flightplan->count)
	{
		//neuen Flug erstellen
		flightplan->first = createFlight(flightdata);

		//neuen Flug als aktuellen Flug definieren
		flightplan->current = flightplan->first;
		//last-Zeiger setzten
		flightplan->last = flightplan->first;
	}
	else
	{
		//neuen Flug erstellen und ans ende anhängen
		setnextFlight(flightplan->last, createFlight(flightdata));
		//current-Zeiger auf das (alte) ende setzen
		flightplan->current = flightplan->last;
		//last-zeiger weiter schieben
		flightplan->last = getnextFlight(flightplan->current); //besser dokumentieren
		
		
		//aktuellen Flug dem neuen als vorgänger setzten
		flightplan->last->prev = flightplan->current;
		//current-Zeiger auf das (neue) ende setzen
		flightplan->current = flightplan->last;
	}

	//Fluganzahl erhöhen
	flightplan->count++;
}

void removeFlight (TFlightplan * flightplan) //muss überarbeitet werden
{
	TFlight * tempNext = getnextFlight(flightplan->current);
	TFlight * tempPrev = getprevFlight(flightplan->current);
	
	if (tempNext)//prüfen
		tempNext->prev = tempPrev;
	if (tempPrev)//prüfen
		tempPrev->next = tempNext;
	// wenn es des letzte existierende element in der liste ist, setze Head auf NULL
	else if (!tempNext && !tempPrev)//überarbeiten
		flightplan->first = NULL;
	// wenn der erste flug in der Liste gelöscht wird, wird Flightplan.next auf das neue erste element gesetzt
	else 
		flightplan->first = tempNext; // überprüfen.....

	// Flug löschen lassen
	deleteFlight(flightplan->current); //prüfen, current zeigt danach ins nirvana

	flightplan->count--;
};

void searchFlight (TFlightplan * flugplan, int flightnumber)
{
	flugplan->current = flugplan->first;
	bool ende = false;
	while (!ende && flugplan->current)
	{
		if (flugplan->current->data->number == flightnumber) //hier wird noch direkt auf daten von unter "classen" zu gegriffen
			ende = true;
		else
			nextFlight(flugplan);
	};
};

void outputFlight (TFlightplan * flightplan) //sollte gehen / warscheinlich noch in der falschen datei
{
	cout << flightplan->current->data->number << "\t";
	cout << flightplan->current->data->destination.c_str() << "\t";
	cout << flightplan->current->data->time.c_str() << "\t";
	cout << flightplan->current->data->rollway << "\t";
	cout << flightplan->current->data->pilot.c_str() << "\t";
	cout << flightplan->current->data->numberplate.c_str() << "\n";
};

void exportFlightPlan (TFlightplan * flightplan){
	ofstream exportFile, htmlFile, jsonFile;
	int count = 0;
	exportFile.open("export.txt");
	htmlFile.open("export-html.html");
	jsonFile.open("flightdata.json");
	
	exportFile << "Flugnr.\t" << "Flug Ziel\t" << "Zeit\t" << "Rollbahn\t" << "Pilot\t" << "Flugkennung\n";
	
	htmlFile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
	htmlFile << "<html><head><title>Flugdaten HTML Export</title></head><body><table border=\"1\"><tr>";
	htmlFile << "<td>Flugnummer</td><td>Flug Ziel</td><td>Zeit</td><td>Rollbahn</td><td>Pilot</td><td>Flugkennung</td></tr>";

	jsonFile << "{\"flightdata\":{\"count\":" << flightplan->count << "},";
	jsonFile << "{\"flights\":";

	if(flightplan->count != 0){
		flightplan->current = flightplan->first;

		do{
			exportFile << flightplan->current->data->number << "\t";
			exportFile << flightplan->current->data->destination.c_str() << "\t";
			exportFile << flightplan->current->data->time.c_str() << "\t";
			exportFile << flightplan->current->data->rollway << "\t";
			exportFile << flightplan->current->data->pilot.c_str() << "\t";
			exportFile << flightplan->current->data->numberplate.c_str() << "\n";
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

			count = count + 1;

			if(flightplan->count >= count){
				jsonFile << "}";
			}else{
				jsonFile << "},";
			}
			
			if(getnextFlight(flightplan->current)){
				nextFlight(flightplan);
			}
		}while(getnextFlight(flightplan->current) != 0);	
	}
	jsonFile << "}}}}";
	htmlFile << "</table></body></html>";

	htmlFile.close();
	jsonFile.close();
	exportFile.close();

}

void outputFlightPlan (TFlightplan * flightplan)
{
	bool result;
	cout << "Flugnr.\t" << "Flug Ziel\t" << "Zeit\t" << "Rollbahn\t" << "Pilot\t" << "Flugkennung\n";
	
	if (flightplan->count != 0)
	{
		flightplan->current = flightplan->first;
		do
		{
			outputFlight (flightplan);
			if (getnextFlight(flightplan->current))
				nextFlight (flightplan);
		}while (getnextFlight(flightplan->current) != 0);
	}
};

bool nextFlight (TFlightplan * flightplan)//sollte gehen /not testet
{
	bool result = false;

	if (getnextFlight(flightplan->current) != NULL)
	{
		flightplan->current = getnextFlight(flightplan->current);
		result = true;
	}
	else
		result = false;

	return result;
}

bool prevFlight (TFlightplan * flightplan)//muss überarbeitet werden /not testet
{
	bool result = false;

	if (getprevFlight(flightplan->current) != NULL)
	{
		flightplan->current = getprevFlight(flightplan->current);
		result = true;
	}
	else
		result = false;

	return result;
}



