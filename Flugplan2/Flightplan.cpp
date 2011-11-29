#include "Flightplan.h"

TFlightplan::TFlightplan (void) //geht /not tested
{
	count = 0;
	first = NULL;
	current = NULL;
	last = NULL;
}

TFlightplan::~TFlightplan ()//könnte fliegen gehen / not tested
{
	clear();
}

void TFlightplan::clear (void)//könnte fliegen gehen / not tested
{
	bool next = false;
	TFlight * tempFlight;

	if (count != 0)
	{
		current = first;

		do
		{
			tempFlight = current;
			next = nextFlight();			
			delete tempFlight;

		}while (next);
	}
	count = 0;
	first = NULL;
	current = NULL;
	last = NULL;
	
	
}
void TFlightplan::newFlight (TFlightdata * flightdata)//könnte fliegen gehen /not testet
{
	//falls noch kein Flugvorhanden ist
	if (!count)
	{
		//neuen Flug erstellen
		first = new TFlight(flightdata);
		//neuen Flug als aktuellen Flug definieren
		current = first;
		//last-Zeiger setzten
		last = first;
	}
	else
	{
		if(!searchFlight(flightdata->getNumber())){
			//neuen Flug erstellen und ans ende anhängen
			last->setnextFlight(new TFlight(flightdata));
			//current-Zeiger auf das (alte) ende setzen
			current = last;
			//last-zeiger weiter schieben
			last = current->getnextFlight(); //besser dokumentieren


			//aktuellen Flug dem neuen als vorgänger setzten
			last->setprevFlight(current);
			//current-Zeiger auf das (neue) ende setzen
			current = last;
		}else{
			cout << "Flugnummer " << flightdata->getNumber() << " ist bereits vorhanden und konnte deshalb nicht importiert werden" << endl;
			delete flightdata;
		}
	}

	//Fluganzahl erhöhen
	count++;
}

void TFlightplan::removeFlight () //muss überarbeitet werden
{
	TFlight * tempNext = current->getnextFlight();
	TFlight * tempPrev = current->getprevFlight();

	if (tempNext)//prüfen
		tempNext->setprevFlight(tempPrev);
	if (tempPrev)//prüfen
		tempPrev->setnextFlight(tempPrev);
	// wenn es des letzte existierende element in der liste ist, setze Head auf NULL
	else if (!tempNext && !tempPrev)//überarbeiten
		first = NULL;
	// wenn der erste flug in der Liste gelöscht wird, wird Flightplan.next auf das neue erste element gesetzt
	else 
		first = tempNext; // überprüfen.....

	// Flug löschen lassen
	delete current; //prüfen, current zeigt danach ins nirvana

	count--;
};

bool TFlightplan::searchFlight (int flightnumber)
{
	current = first;
	bool ende = false;
	bool foundNextFlight = true;
	while (!ende && current && foundNextFlight)
	{
		if (current->getFlightdata()->getNumber() == flightnumber) //hier wird noch direkt auf daten von unter "classen" zu gegriffen
			ende = true;
		else
			foundNextFlight = nextFlight();

	};

	return ende;
};

void TFlightplan::switchFlights (int firstFlight, int secondFlight){
	TFlightdata * tempFlightData;
	TFlight * tempFlight1;
	TFlight * tempFlight2;

	current = first;

	// search the first flight
	searchFlight(firstFlight);

	tempFlight1 = current;

	// search the second flight
	searchFlight(secondFlight);

	tempFlight2 = current;

	tempFlightData = tempFlight1->getFlightdata();

	tempFlight1->setFlightdata(tempFlight2->getFlightdata());

	tempFlight2->setFlightdata(tempFlightData);
}

void TFlightplan::sortFlightplan (int sortBy)
{
	current = first;

	TFlight * flug = first;
	TFlight * tempFlug;

	while (flug->getnextFlight() != NULL){
		tempFlug = flug;
		sortFlight(flug, tempFlug, sortBy);
		flug = flug->getnextFlight();
	}
}

void TFlightplan::sortFlight(TFlight * flug, TFlight * (&tempFlug), int sortBy)
{
	bool switching = false;
	while(tempFlug->getnextFlight() != NULL){
		tempFlug = tempFlug->getnextFlight();
		switch (sortBy)
		{
		case 1:
			if(flug->getFlightdata()->getNumber() > tempFlug->getFlightdata()->getNumber())
				switching = true;
			break;
		case 2:
			if(flug->getFlightdata()->getDestination().compare(tempFlug->getFlightdata()->getDestination()) == 1)
				switching = true;
			break;
		case 3:
			if(flug->getFlightdata()->getTime().compare(tempFlug->getFlightdata()->getTime()) == 1)
				switching = true;
			break;
		case 4:
			if(flug->getFlightdata()->getRollway() > tempFlug->getFlightdata()->getRollway())
				switching = true;
			break;
		case 5:
			if(flug->getFlightdata()->getPilot().compare(tempFlug->getFlightdata()->getPilot()) == 1)
				switching = true;
			break;
		case 6:
			if(flug->getFlightdata()->getNumberplate().compare(tempFlug->getFlightdata()->getNumberplate()) == 1)
				switching = true;
			break;
		case 7:
			if(flug->getFlightdata()->getNumber() < tempFlug->getFlightdata()->getNumber())
				switching = true;
			break;
		case 8:
			if(flug->getFlightdata()->getDestination().compare(tempFlug->getFlightdata()->getDestination()) == -1)
				switching = true;
			break;
		case 9:
			if(flug->getFlightdata()->getTime().compare(tempFlug->getFlightdata()->getTime()) == -1)
				switching = true;
			break;
		case 10:
			if(flug->getFlightdata()->getRollway() < tempFlug->getFlightdata()->getRollway())
				switching = true;
			break;
		case 11:
			if(flug->getFlightdata()->getPilot().compare(tempFlug->getFlightdata()->getPilot()) == -1)
				switching = true;
			break;
		case 12:
			if(flug->getFlightdata()->getNumberplate().compare(tempFlug->getFlightdata()->getNumberplate()) == -1)
				switching = true;
			break;
		}
		if (switching)
			switchFlights(flug->getFlightdata()->getNumber(), tempFlug->getFlightdata()->getNumber());
		sortFlight(flug, tempFlug, sortBy);
	}
}

bool TFlightplan::nextFlight (void)//sollte gehen /not testet
{
	bool result = false;

	if (current->getnextFlight() != NULL)
	{
		current = current->getnextFlight();
		result = true;
	}
	else
		result = false;

	return result;
}

bool TFlightplan::prevFlight (void)//muss überarbeitet werden /not testet
{
	bool result = false;

	if (current->getprevFlight() != NULL)
	{
		current = current->getprevFlight();
		result = true;
	}
	else
		result = false;

	return result;
}

TFlight	* TFlightplan::getCurrent (void)
{
	return current;
}

void TFlightplan::setCurrent (TFlight * current)
{
	TFlightplan::current = current;
}

TFlight	* TFlightplan::getFirst (void)
{
	return first;
}

TFlight	* TFlightplan::getLast (void)
{
	return last;
}

int TFlightplan::getCount (void)
{
	return count;
}