/*
 * This is the implementation of abstract class caching.
 */

#include <string.h>
#include "caching.hpp"


using namespace std;

/* 
 * Constructor, initialize all relevant settings.
 */
caching::caching()
{
    this->miss = 0;
    this->hits = 0; 
    this->name = "caching";
}

string caching::get_name()
{
    return this->name;
}

unsigned long long caching::get_hits()
{   
    return this->hits;
}

unsigned long long caching::get_miss()
{   
    return this->miss;
}
