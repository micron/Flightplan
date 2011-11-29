#pragma once

#include <iostream>
using namespace std;

class TFlightdata
{
private:
	int		number;
	string	destination;
	string	time;
	int		rollway;
	string	pilot;
	string	numberplate;
public:
			TFlightdata		(void);						//Constructor
			~TFlightdata	(void);						//Destructor
	/*void	setFlightdata	(int	number,
							 string	destination,
							 string	time,
							 int	rollway,
							 string	pilot,
							 string	numberplate);*/

	void	setNumber		(int number);
	void	setDestination	(string destination);
	void	setTime			(string time);
	void	setRollway		(int rollway);
	void	setPilot		(string pilot);
	void	setNumberplate	(string numberplate);

	int		getNumber		(void);
	string	getDestination	(void);
	string	getTime			(void);
	int		getRollway		(void);
	string	getPilot		(void);
	string	getNumberplate	(void);
};




