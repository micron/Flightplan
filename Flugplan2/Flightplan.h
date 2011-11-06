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

enum sortby {number, destination, time, rollway, pilot, numberplate};

TFlightplan	* createFlightplan (void);						//Constructor
void		  deleteFlightplan  (TFlightplan * flightplan, bool hardDelete);	//Destructor, clears only the flighplan list if hardDelete is false

void		  newFlight			(TFlightplan * flightplan, TFlightdata * flightdata);
void		  removeFlight		(TFlightplan * flightplan);
bool		  searchFlight		(TFlightplan * flightplan,
								 int		   flightnumber);
void		  switchFlights (TFlightplan * flugplan, int firstFlight, int secondFlight);
void		  sortFlightplan (TFlightplan * flugplan, int sortBy);
void		  sortFlight(TFlightplan * flugplan, TFlight * flug, TFlight  *(&tempFlug), int sortBy);

//void		  changeFlight		(TFlightplan * flightplan);

bool		  nextFlight		(TFlightplan * flightplan);
bool		  prevFlight		(TFlightplan * flightplan);
//void		  cleanup			(TFlightplan * flightplan);

