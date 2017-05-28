// make NO CHANGES to this file

#pragma once				// include this .h file file only once

#include <ostream>

class Winery
{
public:
	static const char	YOUR_NAME[];	// used for printing out programmer's name

	Winery(const char * const name, const char * const location, const int acres, const int rating);
	virtual ~Winery(void);

	// nothing needed in the .cpp file for these functions - complete implementation is provided
	const char * const getName() const { return name; }
	const char * const getLocation() const { return location; }
	const int getAcres() const { return acres; }
	const int getRating() const { return rating; }

	// print out column headings for lists of wineries, as specified by lab1output.txt
	static void displayColumnHeadings(std::ostream& out);

	// print out a winery, as specified by lab1output.txt
	friend std::ostream& operator<<(std::ostream& out, Winery *w);

private:
	char	*name;
	char	*location;
	int		acres;
	int		rating;
};
