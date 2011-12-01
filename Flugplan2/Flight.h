#pragma once

#include "Flightdata.h"

//using namespace std;

class TFlight
{
private:
	TFlight * next;
	TFlight * prev;
	TFlightdata * data;
public:
				  TFlight			(TFlightdata * flightdata);
				  ~TFlight			(void);
	void		  setprevFlight		(TFlight	 * prevFlight);
	TFlight		* getprevFlight		(void);
	void		  setnextFlight		(TFlight	 * nextFlight);
	TFlight		* getnextFlight		(void);
	void		  setFlightdata		(TFlightdata * flightdata);
	TFlightdata * getFlightdata		(void);
};