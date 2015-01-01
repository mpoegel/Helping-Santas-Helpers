#ifndef __date_h_
#define __date_h_

#include <fstream>
#include <string>
#include <sstream>

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
	void validate();

public:
	// CONSTRUCTORS
	DateTime();
	DateTime(unsigned int year, unsigned int month, unsigned int day,
					 unsigned int hour, unsigned int minute);
	DateTime(const string& dtString);
	DateTime(const DateTime& dt);

	// ACCESSORS
	unsigned int getYear() const { return year_; }
	unsigned int getMonth() const { return month_; }
	unsigned int getDay() const { return day_; }
	unsigned int getHour() const { return hour_; }
	unsigned int getMinute() const { return minute_; }
	void printDateTime(ostream& out_str) const;
	unsigned int getJulianDay() const;
	bool isLeapYear() const;
	bool isSanctioned() const;

	// MODIFIERS
	void tick();
	DateTime& addMinutes(unsigned int min);
	void copy(const DateTime& dt);

	// OVERLOADS
	DateTime& operator=(const DateTime& d2);
	bool operator==(const DateTime& d2) const;
	bool operator<(const DateTime& d2) const;
	bool operator<=(const DateTime& d2) const;
};

// HELPERS
ostream& operator<<(ostream& os, const DateTime& dt);

#endif
