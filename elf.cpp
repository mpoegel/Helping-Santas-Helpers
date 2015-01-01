#include "elf.h"

unsigned int Elf::elf_count_ = 1;
// -----------------------------------------------------------------------------
// CONSTRUCTORS
// -----------------------------------------------------------------------------
Elf::Elf() {
	id_ = elf_count_;
	elf_count_++;
	toys_completed_ = 0;
	productivity_ = 1.0;
	rest_period_ = 0;
	is_working_ = false;
	current_toy_ = NULL;
}

// -----------------------------------------------------------------------------
// ACCESSORS
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// MODIFIERS
// -----------------------------------------------------------------------------
bool Elf::assignToy(Toy* t) {
	if (is_working_ || rest_period_ > 0) {
		return false;
	}
	current_toy_ = t;
	current_toy_->assignElf(this);
	current_toy_->setDuration(productivity_ * current_toy_->getDuration());
	return true;
}

bool Elf::beginWork(const DateTime& now) {
	if (is_working_ || current_toy_ == NULL) {
		return false;
	}
	is_working_ = true;
	current_toy_->startWork(now);
	return true;
}

bool Elf::toyCompleted() {
	if (!is_working_) {
		return false;
	}
	unsigned int time_spent = current_toy_->getDuration();
	// calculate the new productivity after completing a toy
	productivity_ = productivity_ * pow(1.02,time_spent) * pow(0.9,rest_period_);
	current_toy_ = NULL;
	is_working_ = false;
	return true;
}

bool Elf::incrementRest() {
	if (!is_working_) {
		return false;
	}
	rest_period_++;
	return true;
}

bool Elf::decrementRest() {
	if (is_working_ || rest_period_ == 0) {
		return false;
	}
	rest_period_--;
	return true;
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// HELPERS
// -----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Elf& elf) {
	os << "ID: " << elf.getId();
	return os;
}
