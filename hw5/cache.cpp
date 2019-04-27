/** Weiting Tan 
 *  JHED: wtan12
 * This is the main body for different caching techniques.
*/
#include <iostream>
#include <string>
#include <cstring>
#include "caching.hpp"
#include "DIR_caching.hpp"



using namespace std;


static caching * dir;

static void opc(caching *p, unsigned long long adr)
{
    p->check_hit(adr);
}


static void print_cache(caching *p)
{
    string name = p->get_name();
    unsigned long long hits = p->get_hits();
    unsigned long long miss = p->get_miss();
    printf("%s: %20llu %20llu\n", name.c_str(), hits, miss);
}

/*
 * Takes input from cin and parse the brance trace, feeding the parsed data 
 * to update the global data about the whole set.
 */
static void parse()
{

    //initiate the pointer to different pointer:
    dir = new DIR_caching();
    
    //the branch address
    unsigned long long adr;
  
    //the token for the store or load
    char f;

    //read in the data per line with fixed format
    while (scanf("%llx %c", &adr, &f) == 2)
    {

        bool store;
        if (f == 'S')
        {
            store = true;
        }
        else
        {
            store = false;
        }
    
        opc(dir, adr);
   
    }
    
    print_cache(dir);
    
}

/*
 * Parse the input branch traces line by line, check for any data or format 
 * error, and calculate some useful measurements about the branch trace.
 */
int main(int argc, char *argv[])
{
    //parse in the input from stdin:
    parse();
    delete dir;

    return EXIT_SUCCESS;
}
