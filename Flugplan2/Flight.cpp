#include "Flight.h"

TFlight::TFlight (TFlightdata * flightdata)
{
	data = flightdata;
	next = NULL;
	prev = NULL;
}

TFlight::~TFlight ()
{
	delete data;
	data = NULL;
	next = NULL;
	prev = NULL;
}

void TFlight::setprevFlight (TFlight * prevFlight)
{
	prev = prevFlight;
}

TFlight * TFlight::getprevFlight	(void)
{
	return prev;
}

void TFlight::setnextFlight (TFlight * nextFlight)
{
	next = nextFlight;
}

TFlight * TFlight::getnextFlight (void)
{
	return next;
}

void TFlight::setFlightdata (TFlightdata * flightdata)
{
	data = flightdata;
}

TFlightdata * TFlight::getFlightdata (void)
{
	return data;
}