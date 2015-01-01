#ifndef __toy_h_
#define __toy_h_

#include "elf.h"
#include "datetime.h"

class Elf;

class Toy {
	friend class Elf;
private:
	unsigned int id_;
	DateTime start_;
	DateTime finish_;
	unsigned int duration_;
	Elf* assigned_elf_;

	static unsigned int toy_count_;

	void setDuration(unsigned int minutes);
	bool startWork(DateTime now);
	bool assignElf(Elf* elf);

public:
	// CONSTRUCTORS
	Toy();
	Toy(const DateTime& dt, unsigned int duration);

	// ACCESSORS
	unsigned int getId() const { return id_; }
	unsigned int getDuration() const { return duration_; }
	const DateTime& getStartTime() const { return start_; }
	const DateTime& getFinishTime() const { return finish_; }
	Elf* getElf() { return assigned_elf_; }

	// MODIFIERS


	// OVERLOADS

};

// HELPERS
ostream& operator<<(ostream& os, const Toy& t);

#endif
