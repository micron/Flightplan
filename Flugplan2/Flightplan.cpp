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

void deleteFlightplan (TFlightplan * flightplan, bool hardDelete)//könnte fliegen gehen / not tested
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
	if(hardDelete){
		delete flightplan;
	}else{
		flightplan->count = 0;
		flightplan->first = NULL;
		flightplan->current = NULL;
		flightplan->last = NULL;
	}
	
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
		if(!searchFlight(flightplan, flightdata->number)){
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
		}else{
			cout << "Flugnummer " << flightdata->number << " ist bereits vorhanden und konnte deshalb nicht importiert werden" << endl;
			deleteFlightdata(flightdata);
		}
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

bool searchFlight (TFlightplan * flugplan, int flightnumber)
{
	flugplan->current = flugplan->first;
	bool ende = false;
	bool foundNextFlight = true;
	while (!ende && flugplan->current && foundNextFlight)
	{
		if (flugplan->current->data->number == flightnumber) //hier wird noch direkt auf daten von unter "classen" zu gegriffen
			ende = true;
		else
			foundNextFlight = nextFlight(flugplan);

	};

	return ende;
};

void switchFlights (TFlightplan * flugplan, int firstFlight, int secondFlight){
	TFlightdata * tempFlightData;
	TFlight * tempFlight1;
	TFlight * tempFlight2;

	flugplan->current = flugplan->first;

	// search the first flight
	searchFlight(flugplan, firstFlight);

	tempFlight1 = flugplan->current;

	// search the second flight
	searchFlight(flugplan, secondFlight);

	tempFlight2 = flugplan->current;

	tempFlightData = tempFlight1->data;

	tempFlight1->data = tempFlight2->data;

	tempFlight2->data = tempFlightData;
}

void sortFlightplan (TFlightplan * flugplan, int sortBy)
{
	flugplan->current = flugplan->first;

	TFlight * flug = flugplan->first;
	TFlight * tempFlug;

	while (getnextFlight(flug) != NULL){
		tempFlug = flug;
		sortFlight(flugplan, flug, tempFlug, sortBy);
		flug = flug->next;
	}
}

void sortFlight(TFlightplan * flugplan, TFlight * flug, TFlight * (&tempFlug), int sortBy)
{
	bool switching = false;
	while(getnextFlight(tempFlug) != NULL){
		tempFlug = getnextFlight(tempFlug);
		switch (sortBy)
		{
		case 1:
			if(flug->data->number > tempFlug->data->number)
				switching = true;
			break;
		case 2:
			if(flug->data->destination.compare(tempFlug->data->destination) == 1)
				switching = true;
			break;
		case 3:
			if(flug->data->time.compare(tempFlug->data->time) == 1)
				switching = true;
			break;
		case 4:
			if(flug->data->rollway > tempFlug->data->rollway)
				switching = true;
			break;
		case 5:
			if(flug->data->pilot.compare(tempFlug->data->pilot) == 1)
				switching = true;
			break;
		case 6:
			if(flug->data->numberplate.compare(tempFlug->data->numberplate) == 1)
				switching = true;
			break;
		case 7:
			if(flug->data->number < tempFlug->data->number)
				switching = true;
			break;
		case 8:
			if(flug->data->destination.compare(tempFlug->data->destination) == -1)
				switching = true;
			break;
		case 9:
			if(flug->data->time.compare(tempFlug->data->time) == -1)
				switching = true;
			break;
		case 10:
			if(flug->data->rollway < tempFlug->data->rollway)
				switching = true;
			break;
		case 11:
			if(flug->data->pilot.compare(tempFlug->data->pilot) == -1)
				switching = true;
			break;
		case 12:
			if(flug->data->numberplate.compare(tempFlug->data->numberplate) == -1)
				switching = true;
			break;
		}
		if (switching)
			switchFlights(flugplan, flug->data->number, tempFlug->data->number);
		sortFlight(flugplan, flug, tempFlug, sortBy);
	}
}

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



