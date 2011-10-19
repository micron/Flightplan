#pragma once

#include <iostream>
#include <fstream>
#include "Flight.h"

using namespace std;

struct TFlightplan
{
	int		count;
	TFlight * first; 
	TFlight * current;
	TFlight * last;
};

TFlightplan	* createFlightplan (void);						//Constructor
void		  deleteFlightplan (TFlightplan * flightplan);	//Destructor

void		  newFlight			(TFlightplan * flightplan, TFlightdata * flightdata);
void		  removeFlight		(TFlightplan * flightplan);
void		  searchFlight		(TFlightplan * flightplan,
								 int		   flightnumber);
void switchFlights (TFlightplan * flugplan, int firstFlight, int secondFlight);
void sortFlightplan(TFlightplan * flugplan);
void sortFlight(TFlightplan * flugplan, TFlight * flug, TFlight  *(&tempFlug));

//void		  changeFlight		(TFlightplan * flightplan);

bool		  nextFlight		(TFlightplan * flightplan);
bool		  prevFlight		(TFlightplan * flightplan);
//void		  cleanup			(TFlightplan * flightplan);