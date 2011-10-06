#pragma once

#include <iostream>
#include <string>
#include "Flightdata.h"
#include "Flightplan.h"
#include <sstream>

void	mainMenue		(void);
void	inputFlightdata	(TFlightdata * tempFlightdata);
string	outputFlight	(TFlightplan * flightplan);
void	outputFlightPlan(TFlightplan * flightplan);
void	exportFlightPlan(TFlightplan * flightplan);
void	backToMenue		(bool mitPause);