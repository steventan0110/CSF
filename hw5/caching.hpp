/*
 * This header file specifies the caching abstract class.
 */
#ifndef _CACHING_HPP
#define _CACHING_HPP

#include <string> 

class caching
{
  protected:
    unsigned long long hits;
    unsigned long long miss;
    std::string name;

  public:
    /* Constructor of abstract cache */
    caching();

    /* update the load and store in side the memory.*/

    /* return true if the operation hits. */
    virtual bool check_hit(unsigned long long adr) = 0;

    /* return the name.*/
    virtual std::string get_name();

    unsigned long long get_hits();
    unsigned long long get_miss();

    /* Destructor of abstract cache */
    virtual ~caching() = default;
};
#endif
