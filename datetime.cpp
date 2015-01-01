#include "datetime.h"

const unsigned int DateTime::max_days_[12] = {31,28,31,30,31,30,31,31,30,31,30,
	31};
const unsigned int DateTime::max_days_leap_[12] = {31,29,31,30,31,30,31,31,30,
	31,30,31};
// -----------------------------------------------------------------------------
// CONSTRUCTORS
// -----------------------------------------------------------------------------
DateTime::DateTime() {
	year_ = 2014;
	month_ = 1;
	day_ = 1;
	hour_ = 0;
	minute_ = 0;
}

DateTime::DateTime(unsigned int year, unsigned int month, unsigned int day,
									 unsigned int hour, unsigned int minute) {
	year_ = year;
	month_ = month;
	day_ = day;
	hour_ = hour;
	minute_ = minute;
	validate();
}

DateTime::DateTime(const string& dtString) {
	stringstream ss(dtString);
	ss >> year_;
	ss >> month_;
	ss >> day_;
	ss >> hour_;
	ss >> minute_;
	validate();
}

DateTime::DateTime(const DateTime& dt) {
	this->copy(dt);
}

// -----------------------------------------------------------------------------
// ACCESSORS
// -----------------------------------------------------------------------------
void DateTime::printDateTime(ostream& out_str) const {
	out_str << year_ << " " << month_ << " " << day_ << " " << hour_
		<< " " << minute_;
}

unsigned int DateTime::getJulianDay() const {
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

bool DateTime::isLeapYear() const {
	return year_ % 4 == 0 && !(year_ % 100 == 0 && year_ % 400 != 0);
}

bool DateTime::isSanctioned() const {
	return hour_ >= 9 && hour_ < 19;
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

DateTime& DateTime::addMinutes(unsigned int min) {
	minute_ += min;
	normalize();
	return *this;
}

void DateTime::copy(const DateTime& dt) {
	year_ = dt.year_;
	month_ = dt.month_;
	day_ = dt.day_;
	hour_ = dt.hour_;
	minute_ = dt.minute_;
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS
// -----------------------------------------------------------------------------
DateTime& DateTime::operator=(const DateTime& d2) {
	year_ = d2.year_;
	month_ = d2.month_;
	day_ = d2.day_;
	hour_ = d2.hour_;
	minute_ = d2.minute_;
	return *this;
}

bool DateTime::operator==(const DateTime& d2) const {
	return year_ == d2.year_ &&
					month_ == d2.month_ &&
					day_ == d2.day_ &&
					hour_ == d2.hour_ &&
					minute_ == d2.minute_;
}

bool DateTime::operator<(const DateTime& d2) const {
	return year_ < d2.year_ ||
					(year_ == d2.year_ && month_ < d2.month_) ||
					(year_ == d2.year_ && month_ == d2.month_ && day_ < d2.day_) ||
					(year_ == d2.year_ && month_ == d2.month_ && day_ == d2.day_ &&
						hour_ < d2.hour_) ||
					(year_ == d2.year_ && month_ == d2.month_ && day_ == d2.day_ &&
						hour_ == d2.hour_ && minute_ < d2.minute_);
}

bool DateTime::operator<=(const DateTime& d2) const {
	return *this < d2 || *this == d2;
}

// -----------------------------------------------------------------------------
// PRIVATE METHODS
// -----------------------------------------------------------------------------
void DateTime::normalize() {
	while (minute_ > 59) {
		hour_++;
		minute_ -= 60;
	}
	while (hour_ > 23) {
		day_++;
		hour_ -= 24;
	}
	if (isLeapYear()) {
		while (day_ > max_days_leap_[month_-1]) {
			day_ -= max_days_leap_[month_-1];
			month_++;
		}
	}
	else {
		while (day_ > max_days_[month_-1]) {
			day_ -= max_days_[month_-1];
			month_++;
		}
	}
	while (month_ > 12) {
		year_++;
		month_ -= 12;
	}
}

void DateTime::validate() {
	// check the date input
	if (month_ == 0 || month_ > 12 || day_ == 0 ||
			(isLeapYear() && day_ > max_days_leap_[month_-1]) ||
			(!isLeapYear() && day_ > max_days_[month_-1])) {
		throw 0;
	}
	// check the time input
	if (hour_ > 23 || minute_ > 60) {
		throw 0;
	}
}

// -----------------------------------------------------------------------------
// HELPERS
// -----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const DateTime& dt) {
	os << dt.getYear() << " " << dt.getMonth() << " " << dt.getDay() << " " <<
		dt.getHour() << " " << dt.getMinute();
	return os;
}
