#ifndef __elf_h_
#define __elf_h_

#include <cmath>

#include "datetime.h"
#include "toy.h"

class Toy;

using namespace std;

class Elf {
private:
	unsigned int id_;
	unsigned int toys_completed_;
	double productivity_;
	unsigned int rest_period_;

	Toy* current_toy_;
	bool is_working_;

	// elf ID counter
	static unsigned int elf_count_;

public:
	// CONSTRUCTORS
	Elf();

	// ACCESSORS
	unsigned int getId() const { return id_; }
	bool isWorking() const { return is_working_; }
	double getProductivity() const { return productivity_; }
	unsigned int getRestPeriod() const { return rest_period_; }

	unsigned int getElfCount() const { return elf_count_; }

	// MODIFIERS
	bool assignToy(Toy* t);
	bool beginWork(const DateTime& now);
	bool toyCompleted();
	bool incrementRest();
	bool decrementRest();

	// OVERLOADS

};

ostream& operator<<(ostream& os, const Elf& elf);


#endif
