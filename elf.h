#ifndef __elf_h_
#define __elf_h_

#include "datetime.h"
#include "toy.h"

class Toy;

using namespace std;

class Elf {
	friend class Toy;
private:
	unsigned int id_;
	unsigned int toys_completed_;
	double productivity_;
	unsigned int rest_period_;

	Toy* current_toy_;
	bool is_working_;

	// elf ID counter
	static unsigned int elf_count_;

	bool toyCompleted(const DateTime& finish_time);

public:
	// CONSTRUCTORS
	Elf();

	// ACCESSORS
	unsigned int getId() { return id_; }
	bool isWorking() { return is_working_; }
	double getProductivity() { return productivity_; }
	unsigned int getRestPeriod() { return rest_period_; }

	// MODIFIERS
	bool assignToy(Toy* t);
	void incrementRest();
	void decrementRest();

	// OVERLOADS

};


#endif
