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
	double productivity_;
	Toy* current_toy_;
	bool is_working_;

	static unsigned int elf_count_;

public:
	// CONSTRUCTORS
	Elf();

	// ACCESSORS
	unsigned int getId() { return id_; }
	bool isWorking() { return is_working_; }
	double getProductivity() { return productivity_; }

	// MODIFIERS
	bool assignToy(Toy* t);

	// OVERLOADS

};


#endif
