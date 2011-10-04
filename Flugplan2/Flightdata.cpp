#include "Flightdata.h"


TFlightdata * createFlightdata	(void)
{
	TFlightdata * tempFlightdata = NULL;
	tempFlightdata = new TFlightdata;


	tempFlightdata -> number = 0;
	tempFlightdata -> destination = "";
	tempFlightdata -> time = "";
	tempFlightdata -> rollway = 0;
	tempFlightdata -> pilot = "";
	tempFlightdata -> numberplate = "";

	return tempFlightdata;
}

void deleteFlightdata (TFlightdata * flightdata)
{
	try
	{
		delete flightdata;
	}
	catch (char * str )
	{
		//cout << "Es ist folgender Fehler beim Löschen von Flugdaten aufgetreten: \n" << str << endl;
	}
}

void setFlightdata (TFlightdata * flightdata, int number, string destination, 
					string time, int rollway, string pilot, string numberplate)
{
	flightdata -> number = number;
	flightdata -> destination = destination;
	flightdata -> time = "";
	flightdata -> rollway = rollway;
	flightdata -> pilot = pilot;
	flightdata -> numberplate = numberplate;
}