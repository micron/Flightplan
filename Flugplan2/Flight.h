#pragma once

#include "Flightdata.h"
#include "Flight.h"

using namespace std;

struct TFlight
{
	TFlight * next;
	TFlight * prev;
	TFlightdata * data;
};

TFlight * createFlight		(TFlightdata * flightdata);
void	  deleteFlight		(TFlight	 * flight);
void	  setprevFlight		(TFlight	 * flight,
							 TFlight	 * prevFlight);
TFlight * getprevFlight		(TFlight	 * flight);
void	  setnextFlight		(TFlight	 * flight,
							 TFlight	 * nextFlight);
TFlight * getnextFlight		(TFlight	 * flight);
