/*
 * This header file specifies the BLK caching tenique. 
 */
#ifndef _BLK_CACHING_HPP
#define _BLK_CACHING_HPP

#include "caching.hpp"
#include <string>
#define MAX_Block 256

class BLK_caching : public caching
{

  private:
 
    unsigned long long block[MAX_Block][4] = {}; //use 2D array to store how recently the block is used
    unsigned long long collision[MAX_Block][4] = {}; //store the value in the corresponding location
    unsigned long long cycle = 0;


  public:
    BLK_caching();

    /* return true if the operation hits. */
    bool check_hit(unsigned long long adr);

    int has_adr(unsigned long long adr);

    int find_unused(int hashcode);
};

#endif
