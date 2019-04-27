/*
 * This header file specifies the ASS caching tenique. 
 */
#ifndef _ASS_CACHING_HPP
#define _ASS_CACHING_HPP

#include "caching.hpp"
#include <string>
#include <stack>
#define MAX 8192

class ASS_caching : public caching
{

  private:
    unsigned long long check[MAX] = {};
    std::stack<int> his; //keep track of the index of recently used

  public:
    ASS_caching();

    /* return true if the operation hits. */
    bool check_hit(unsigned long long adr);
};

#endif
