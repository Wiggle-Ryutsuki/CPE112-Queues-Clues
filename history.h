#ifndef HISTORY_H
#define HISTORY_H

#include "world.h"

extern Location *history[MaxLocations];

// Stack functions
void push(Location *prev); // Stack push function
Location *pop();           // Stack pop function

#endif