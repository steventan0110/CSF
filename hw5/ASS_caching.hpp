/*
 * This header file specifies the ASS caching tenique. 
 */
#ifndef _ASS_CACHING_HPP
#define _ASS_CACHING_HPP

#include "caching.hpp"
#include <string>
#define MAX_Line 8192

class ASS_caching : public caching
{

  private:
    unsigned long long check[MAX_Line] = {}; //store the time the address is used last time
    unsigned long long collision[MAX_Line] = {}; //store the value in the corresponding location
    unsigned long long cycle = 0;


  public:
    ASS_caching();

    /* return true if the operation hits. */
    bool check_hit(unsigned long long adr);

    int has_adr(unsigned long long adr);

    int find_unused();
};

#endif
