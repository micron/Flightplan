#pragma once

#include <iostream>
using namespace std;

struct TFlightdata
{
	int		number;
	string	destination;
	string	time;
	int		rollway;
	string	pilot;
	string	numberplate;
};

TFlightdata * createFlightdata	(void);						//Constructor
void		  deleteFlightdata	(TFlightdata * flightdata);	//Destructor
void		  setFlightdata		(TFlightdata * flightdata,
								 int	number,
								 string	destination,
								 string	time,
								 int	rollway,
								 string	pilot,
								 string	numberplate);


