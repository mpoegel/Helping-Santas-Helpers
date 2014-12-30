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
	current_toy_->setDuration(productivity_ * current_toy_->getDuration());
	is_working_ = true;
	return true;
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// PRIVATE METHODS
// -----------------------------------------------------------------------------
bool Elf::toyCompleted(const DateTime& finish_time) {
	if (!is_working_) {
		return false;
	}
	current_toy_ = NULL;
	is_working_ = false;
	return true;
}
