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
		//neuen Flug ans ende anhängen
		flightplan->last->next = createFlight(flightdata);
		//current-Zeiger auf das (alte) ende setzen
		flightplan->current = flightplan->last;
		//last-zeiger weiter schieben
		flightplan->last = flightplan->last->next; //besser dokumentieren
		
		
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
	TFlight * tempNext = flightplan->current->next;
	TFlight * tempPrev = flightplan->current->prev;
	
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

void searchFlight (TFlightplan * flugplan, int flightnumber)//sollte
{
	flugplan->current = flugplan->first;
	bool ende = false;
	while (!ende && flugplan->current)
	{
		if (flugplan->current->data->number == flightnumber)
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

void outputFlightPlan (TFlightplan * flightplan)//geht fliegen (endlosschleife) /not testet
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
		flightplan->current = flightplan->current->next;
		result = true;
	}
	else
		result = false;

	return result;
}

bool prevFlight (TFlightplan * flightplan)//muss überarbeitet werden /not testet
{
	if (flightplan->current->prev != NULL)
	{
		flightplan->current = flightplan->current->prev;
	}
	return 0;
}



