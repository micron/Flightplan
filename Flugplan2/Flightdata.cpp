#include "Flightdata.h"


TFlightdata::TFlightdata	(void)
{
	number = 0;
	destination = "";
	time = "";
	rollway = 0;
	pilot = "";
	numberplate = "";
}

TFlightdata::~TFlightdata ()
{
}

/*void TFlightdata::setFlightdata (int number, string destination, string time, 
								 int rollway, string pilot, string numberplate)
{
	
	setNumber(number);
	setDestination(destination);
	setTime("");
	setRollway(rollway);
	setPilot(pilot);
	setNumberplate(numberplate);
}*/

void TFlightdata::setNumber(int number)
{
	TFlightdata::number = number;
}

void TFlightdata::setDestination(string destination)
{
	TFlightdata::destination = destination;
}

void TFlightdata::setTime(string time)
{
	TFlightdata::time = time;
}

void TFlightdata::setRollway(int rollway)
{
	TFlightdata::rollway = rollway;
}

void TFlightdata::setPilot(string pilot)
{
	TFlightdata::pilot = pilot;
}

void TFlightdata::setNumberplate(string numberplate)
{
	TFlightdata::numberplate = numberplate;
}

int		TFlightdata::getNumber(void)
{
	return number;
}

string	TFlightdata::getDestination(void)
{
	return destination;
}

string	TFlightdata::getTime(void)
{
	return time;
}

int		TFlightdata::getRollway(void)
{
	return rollway;
}

string	TFlightdata::getPilot(void)
{
	return pilot;
}

string	TFlightdata::getNumberplate(void)
{
	return numberplate;
}