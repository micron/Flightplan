#include "Flight.h"

TFlight * createFlight (TFlightdata * flightdata)
{
	TFlight * tempFlight = new TFlight;
	tempFlight->data = flightdata;
	tempFlight->next = NULL;
	tempFlight->prev = NULL;

	return tempFlight;
}


void deleteFlight (TFlight * flight)
{
	try
	{
		deleteFlightdata(flight->data);
		delete flight;
	}
	catch (char * str )
	{
		//cout << "Folgender Fehler beim Löschen eines Fluges aufgetreten: \n" << str << endl;
	}
}

void setprevFlight (TFlight * flight, TFlight * prevFlight)
{
	flight->prev = prevFlight;
}

TFlight * getprevFlight	(TFlight * flight)
{
	return flight->prev;
}

void setnextFlight (TFlight * flight, TFlight * nextFlight)
{
	flight->next = nextFlight;
}

TFlight * getnextFlight (TFlight * flight)
{
	return flight->next;
}