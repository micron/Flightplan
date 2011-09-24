#pragma once

#include <iostream>
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

//void		  changeFlight		(TFlightplan * flightplan);

void		  outputFlight		(TFlightplan * flightplan);
void		  outputFlightPlan	(TFlightplan * flightplan);
bool		  nextFlight		(TFlightplan * flightplan);
bool		  prevFlight		(TFlightplan * flightplan);
//void		  cleanup			(TFlightplan * flightplan);