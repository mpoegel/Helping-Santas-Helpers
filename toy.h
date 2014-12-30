#ifndef __toy_h_
#define __toy_h_

#include "elf.h"
#include "datetime.h"

class Elf;

class Toy {
private:
	unsigned int id_;
	DateTime start_;
	DateTime finish_;
	unsigned int duration_;
	Elf* assigned_elf_;

	static unsigned int toy_count_;

public:
	// CONSTRUCTORS
	Toy();
	Toy(const DateTime& dt, unsigned int duration);

	// ACCESSORS
	unsigned int getId() { return id_; }
	unsigned int getDuration() { return duration_; }
	const DateTime& getStartTime() { return start_; }
	const DateTime& getFinishTime() { return finish_; }

	// MODIFIERS
	void setDuration(unsigned int minutes);

	// OVERLOADS

};


#endif
