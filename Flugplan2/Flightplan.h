#pragma once

#include <iostream>
#include <fstream>
#include "Flight.h"


using namespace std;

class TFlightplan
{
private:
	int			count;
	TFlight *	first; 
	TFlight *	current;
	TFlight *	last;
public:
	//enum sortby {number, destination, time, rollway, pilot, numberplate};

				TFlightplan		(void);						//Constructor
				~TFlightplan	(void);			//Destructor, clears only the flighplan list if hardDelete is false
	void		clear			(void);
	void		newFlight		(TFlightdata *	flightdata);
	void		removeFlight	();
	bool		searchFlight	(int			flightnumber);
	void		switchFlights	(int			firstFlight,
								 int			secondFlight);
	void		sortFlightplan	(int			sortBy);
	void		sortFlight		(TFlight *		flug,
								 TFlight *		&tempFlug,
								 int			sortBy);
	bool		nextFlight		(void);
	bool		prevFlight		(void);
	TFlight	*	getCurrent		(void);
	void		setCurrent		(TFlight *		current);
	TFlight	*	getFirst		(void);
	TFlight	*	getLast			(void);
	int			getCount		(void);
};



