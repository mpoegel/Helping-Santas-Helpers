#include "datetime.h"

const unsigned int DateTime::max_days_[12] = {31,28,31,30,31,30,31,31,30,31,30,
	31};
// -----------------------------------------------------------------------------
// CONSTRUCTORS
// -----------------------------------------------------------------------------
DateTime::DateTime(unsigned int year, unsigned int month, unsigned int day,
									 unsigned int hour, unsigned int minute) {
	year_ = year;
	month_ = month;
	day_ = day;
	hour_ = hour;
	minute_ = minute;
	// check the date input
	if ((month == 2 && isLeapYear() && day > 29) ||
			(month == 2 && !isLeapYear() &&  day > 28)) {
		throw 0;
	}
	else if (month_ == 0 || month_ > 12 || day_ == 0 ||
					 max_days_[month_-1] > day_) {
		throw 0;
	}
	// check the time input
	if (hour_ > 23 || minute_ > 60) {
		throw 0;
	}
}

// -----------------------------------------------------------------------------
// ACCESSORS
// -----------------------------------------------------------------------------
void DateTime::printDateTime(ostream& out_str) {
	out_str << year_ << " " << month_ << " " << day_ << " " << hour_
		<< " " << minute_;
}

unsigned int DateTime::getJulianDay() {
	unsigned int jDay = 0;
	for (unsigned int i=1; i<month_; i++) {
		if (i==2 && isLeapYear()) {
			jDay += 29;
		}
		else {
			jDay += max_days_[i];
		}
	}
	jDay += day_;
	return jDay;
}

bool DateTime::isLeapYear() {
	return year_ % 4 == 0 && !(year_ % 100 == 0 && year_ % 400 != 0);
}

// -----------------------------------------------------------------------------
// MODIFIERS
// -----------------------------------------------------------------------------
void DateTime::tick() {
	minute_++;
	if (minute_ > 59) {
		hour_++;
		minute_ = 0;
		if (hour_ > 23) {
			day_++;
			hour_ = 0;
			if (month_ == 2 && isLeapYear() && day_ > 29) {
				month_++;
				day_ = 1;
				if (month_ > 12) {
					year_++;
					month_ = 1;
				}
			}
			else if (!(month_ == 2 && isLeapYear()) && day_ > max_days_[month_-1]) {
				month_++;
				day_ = 1;
				if (month_ > 12) {
					year_++;
					month_ = 1;
				}
			}
		}
	}
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS
// -----------------------------------------------------------------------------
bool DateTime::operator=(const DateTime& d2) {
	return year_ == d2.year_ &&
					month_ == d2.month_ &&
					day_ == d2.day_ &&
					hour_ == d2.hour_ &&
					minute_ == d2.minute_;
}

bool DateTime::operator<(const DateTime& d2) {
	return year_ < d2.year_ ||
					(year_ == d2.year_ && month_ < d2.month_) ||
					(year_ == d2.year_ && month_ == d2.month_ && day_ < d2.day_) ||
					(year_ == d2.year_ && month_ == d2.month_ && day_ == d2.day_ &&
						hour_ < d2.hour_) ||
					(year_ == d2.year_ && month_ == d2.month_ && day_ == d2.day_ &&
						hour_ == d2.hour_ && minute_ < d2.minute_);
}
