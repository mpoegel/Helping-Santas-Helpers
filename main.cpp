/*
Kaggle - Helping Santa's Helpers

Created: 20-December-2014
Author:  Matt Poegel
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <sstream>
#include <cstdlib>

#include "datetime.h"
#include "toy.h"
#include "elf.h"
using namespace std;


pair<DateTime,unsigned int> generateSolution(ifstream& in_str, ostream& out_str) {

  list<Toy*> working_toys;  // toys being worked (COMPLETED TOYS ARE DELETED)
  queue<Toy*> toy_queue;    // toys waiting to be worked
  list<Elf*> working_elves; // elves working on a toy
  list<Elf*> resting_elves; // elves required to rest for working overtime
  stack<Elf*> idle_elves;   // elves available to work on a toy
  list<Toy*>::iterator t_itr;
  list<Elf*>::iterator e_itr;

  const unsigned int MAX_ELVES = 900;
  unsigned int total_elves = 0;
  DateTime datetime(2014,1,1,0,0);
  string toy_str, toy_num_str, toy_datetime_string, toy_dur_str;
  getline(in_str, toy_str); // ignore the header

  // loop while there are toys in the file or toys being made
  while (in_str.good() || working_toys.size() || toy_queue.size()) {
    // while there are toys in the file and the newest toy qualifies to be built
    // this way all of the toys are not loaded at the same time
    while (in_str.good() && (toy_queue.size() == 0 ||
        toy_queue.back()->getStartTime() <= datetime)) {
      getline(in_str, toy_str);
      stringstream ss(toy_str);
      // extract the information from the comma delimited line
      getline(ss, toy_num_str, ',');
      getline(ss, toy_datetime_string, ',');
      getline(ss, toy_dur_str, ',');
      // create the new toy object and add it to the list of toys to make
      Toy* t = new Toy(DateTime(toy_datetime_string), atoi(toy_dur_str.c_str()));
      toy_queue.push(t);
      // cout << "new toy: " << *t << endl;
    }

    // check if any elves are working overtime (during unsanctioned hours)
    if (!datetime.isSanctioned()) {
      // increment all working elves' rest period
      for (e_itr = working_elves.begin(); e_itr != working_elves.end();
          e_itr++) {
        (*e_itr)->incrementRest();
      }
    }

    // check if any elves are resting during sanctioned hours
    if (datetime.isSanctioned()) {
      // decrement all resting elves rest period
      // should any be done resting move them to the idle group
      for (e_itr = resting_elves.begin(); e_itr != resting_elves.end();
          e_itr++) {
        (*e_itr)->decrementRest();
        if ((*e_itr)->getRestPeriod() == 0) {
          idle_elves.push(*e_itr);
          resting_elves.erase(e_itr);
        }
      }
    }

    // check to see if any toys are finished being built
    for (t_itr = working_toys.begin(); t_itr != working_toys.end(); t_itr++) {
      if ((*t_itr)->getFinishTime() == datetime) {
        // record the information about the work
        out_str << (*t_itr)->getId() << ",";
        out_str << (*t_itr)->getElf()->getId() << ",";
        out_str << (*t_itr)->getStartTime() << ",";
        out_str << (*t_itr)->getDuration() << endl;
        // find the elf and move the elf to either idle or rest
        e_itr = working_elves.begin();
        while (e_itr != working_elves.end() &&
            (*e_itr)->getId() != (*t_itr)->getElf()->getId()) {
          e_itr++;
        }
        if (e_itr == working_elves.end()) throw 0; // should never happen...
        (*e_itr)->toyCompleted();
        if ((*e_itr)->getRestPeriod() > 0) {
          resting_elves.push_back(*e_itr);
        }
        else {
          idle_elves.push(*e_itr);
        }
        working_elves.erase(e_itr);
        // now throw away the toy because we actually don't want it
        delete *t_itr;
        working_toys.erase(t_itr);
        t_itr--;
      }
    }

    // assign new toys to idle elves
    if (datetime.isSanctioned()) {
      // cout << "toy Q size = " << toy_queue.size() << endl;
      // cout << "# idle elves = " << idle_elves.size() << endl;
      while (toy_queue.size() && toy_queue.front()->getStartTime() <= datetime) {
        // check if we are at the elf limit
        if (total_elves >= MAX_ELVES) {
          break;
        }
        // if there are no idle elves then hire a new recruit!
        if (idle_elves.size() == 0) {
          idle_elves.push(new Elf());
          total_elves++;
          // cout << "new elf: " << *(idle_elves.top()) << endl;
        }
        idle_elves.top()->assignToy(toy_queue.front());
        // start work immediately
        idle_elves.top()->beginWork(datetime);
        // move elf and toy to appropriate containers
        working_toys.push_back(toy_queue.front());
        working_elves.push_back(idle_elves.top());
        // pop from queue/stack
        idle_elves.pop();
        toy_queue.pop();
      }
    }

    // always tick the clock
    datetime.tick();
  } // END OUT-MOST WHILE LOOP

  // terminate all employment
  for (e_itr = working_elves.begin(); e_itr != working_elves.end(); e_itr++) {
    delete *e_itr;
  }
  for (e_itr = resting_elves.begin(); e_itr != resting_elves.end(); e_itr++) {
    delete *e_itr;
  }
  while (idle_elves.size()) {
    delete idle_elves.top();
    idle_elves.pop();
  }

  // return the results
  return make_pair(datetime, total_elves);
}

float calculateScore(const pair<DateTime,unsigned int>& solution) {
  DateTime reference_date = DateTime(2014,1,1,0,0);
  unsigned int minutes_since = solution.first.minutesSince(reference_date);
  return minutes_since * log(1 + solution.second);
}

void printUsage(const string& f_name) {
  cout << "Usage: " << f_name << " data_file" << endl;
  cout << "  -o  out_file" << endl;
  cout << "  -score  calculate the score" << endl;
}

int main(int argc, char* argv[]) {
  // validate input
  if (argc < 2) {
    printUsage(argv[0]);
    return 1;
  }
  // check the data file
  ifstream in_str(argv[1]);
  if (!in_str.good()) {
    cerr << "Could not open data file: " << argv[1] << endl;
    return 1;
  }
  // check for other flags
  bool score_flag = false;
  bool out_file_flag = false;
  ofstream out_str;
  for (unsigned int i=2; i<argc; i++) {
    if (argv[i] == string("-o") && i+1 < argc) {
      out_file_flag = true;
      i++;
      out_str.open(argv[i]);
      if (!out_str.good()) {
        cerr << "Could not open output file: " << argv[i] << endl;
        return 1;
      }
    }
    else if (argv[i] == string("-score")) {
      score_flag = true;
    }
  }

  // generate the basic solution
  pair<DateTime, unsigned int> solution;

  if (out_file_flag) {
    out_str << "ToyId,ElfId,StartTime,Duration" << endl;
    solution = generateSolution(in_str, out_str);
  }
  else {
    cout << "ToyId,ElfId,StartTime,Duration" << endl;
    solution = generateSolution(in_str, cout);
  }

  if (score_flag) {
    float score = calculateScore(solution);
    cout << "Finish Time: " << solution.first << endl;
    cout << "Elves Used: " << solution.second << endl;
    cout << "Score: " << score << endl;
  }


  return 0;
}
