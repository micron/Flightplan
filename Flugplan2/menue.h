#pragma once

#include <iostream>
#include <string>
#include "Flightdata.h"
#include "Flightplan.h"
#include <sstream>

using namespace std;

void	mainMenue		(void);
void	sortingMenu		(void);
void	inputFlightdata	(TFlightdata * tempFlightdata);
TFlightdata	* importFlight	(ifstream * input);
void	importFlightplan(TFlightplan * flightplan);
string	readSubString (string * readString);
string	outputFlight	(TFlightplan * flightplan);
void	outputFlightPlan(TFlightplan * flightplan);
void	exportFlightPlan(TFlightplan * flightplan);
void	backToMenue		(bool mitPause);