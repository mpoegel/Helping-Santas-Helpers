#ifndef __date_h_
#define __date_h_

#include <fstream>

using namespace std;

class DateTime {
private:
	unsigned int year_;
	unsigned int month_;
	unsigned int day_;
	unsigned int hour_;
	unsigned int minute_;

	const static unsigned int max_days_[12];
	const static unsigned int max_days_leap_[12];

	void normalize();

public:
	// CONSTRUCTORS
	DateTime();
	DateTime(unsigned int year, unsigned int month, unsigned int day,
					 unsigned int hour, unsigned int minute);
	DateTime(const DateTime& dt);

	// ACCESSORS
	void printDateTime(ostream& out_str);
	unsigned int getJulianDay();
	bool isLeapYear();
	bool isSanctioned();

	// MODIFIERS
	void tick();
	DateTime& addMinutes(unsigned int min);
	void copy(const DateTime& dt);

	// OVERLOADS
	DateTime& operator=(const DateTime& d2);
	bool operator==(const DateTime& d2);
	bool operator<(const DateTime& d2);
};

#endif
