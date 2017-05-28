#include "memoryleakdetect.h"		// this must be the first #include in each of your .cpp files
#include "winery.h"
#include <iomanip>

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	Winery::YOUR_NAME[] = "Casey Benson";

Winery::Winery(const char * const name, const char * const location, const int acres, const int rating) :
	name(new char[strlen(name)+1]),
	location(new char[strlen(location)+1]),
	acres(acres),
	rating(rating)
{
	strcpy(this->name, name);
	strcpy(this->location, location);
}

Winery::~Winery()
{
	delete[] name;
	delete[] location;
}

void Winery::displayColumnHeadings(ostream& out)
{
	out << "name                      location           acres rating" << endl
		<< "----                      --------           ----- ------" << endl;
}

ostream& operator<<(ostream& out, Winery *w)
{
	out <<std::setw(26) << std::left << w->getName()
		<< std::setw(20) << std::left << w->getLocation()
		<< std::setw(4) << std::right << w->getAcres()
		<< std::setw(7) << std::right << w->getRating();
	return out;
}
