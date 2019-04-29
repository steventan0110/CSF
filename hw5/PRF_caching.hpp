/*
 * This header file specifies the BLK caching tenique. 
 */
#ifndef _PRF_CACHING_HPP
#define _PRF_CACHING_HPP

#include "caching.hpp"
#include <string>
#define MAX_Block 256

class PRF_caching : public caching
{

  private:
 
    unsigned long long block[MAX_Block][4] = {}; //use 2D array to store how recently the block is used
    unsigned long long collision[MAX_Block][4] = {}; //store the value in the corresponding location
    unsigned long long cycle = 0;
    bool load = false;


  public:
    PRF_caching();

    /* return true if the operation hits. */
    bool check_hit(unsigned long long adr);

    int has_adr(unsigned long long adr);

    int find_unused(int hashcode);

    void set_load(bool store);
};

#endif
