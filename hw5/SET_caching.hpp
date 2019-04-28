/*
 * This header file specifies the SET caching tenique. 
 */
#ifndef _SET_CACHING_HPP
#define _SET_CACHING_HPP

#include "caching.hpp"
#include <string>
#include <stack>
#define MAX 2048

class SET_caching : public caching
{

  private:
 
    unsigned long long set[MAX][4] = {}; //use 2D array to store the set
    unsigned long long collision[MAX][4] = {}; //store the value in the corresponding location
    unsigned long long cycle = 0;


  public:
    SET_caching();

    /* return true if the operation hits. */
    bool check_hit(unsigned long long adr);

    int has_adr(unsigned long long adr);

    int find_unused(int hashcode);
};

#endif
