#include "toy.h"

unsigned int Toy::toy_count_ = 1;
// -----------------------------------------------------------------------------
// CONSTRUCTORS
// -----------------------------------------------------------------------------
Toy::Toy() {
	id_ = toy_count_;
	toy_count_++;
	start_ = DateTime();
	duration_ = 0;
	assigned_elf_ = NULL;
}

Toy::Toy(const DateTime& dt, unsigned int duration) {
	id_ = toy_count_;
	toy_count_++;
	start_ = dt;
	duration_ = duration;
	finish_ = DateTime(dt).addMinutes(duration);
	assigned_elf_ = NULL;
}

// -----------------------------------------------------------------------------
// ACCESSORS
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// MODIFIERS
// -----------------------------------------------------------------------------
void Toy::setDuration(unsigned int minutes) {
	duration_ = minutes;
}

bool Toy::startWork(DateTime now) {
	finish_ = now.addMinutes(duration_);
	return true;
}

bool Toy::assignElf(Elf* elf) {
	assigned_elf_ = elf;
	return true;
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// HELPERS
// -----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Toy& t) {
	os << "ID: " << t.getId() << " START: " << t.getStartTime() << " DURATION: "
		<< t.getDuration();
	return os;
}
