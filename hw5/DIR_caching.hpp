/*
 * This header file specifies the Direct Map caching tenique. 
 */
#ifndef _DIR_CACHING_HPP
#define _DIR_CACHING_HPP

#include "caching.hpp"
#include <string>
#define MAX 8192

class DIR_caching : public caching
{

  private:
    unsigned long long check[MAX] = {};

  public:
    DIR_caching();

    /* return true if the operation hits. */
    bool check_hit(unsigned long long adr);
};

#endif
