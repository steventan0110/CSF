/** Weiting Tan 
 *  JHED: wtan12
 * This is the main body for different caching techniques.
*/
#include <iostream>
#include <string>
#include <cstring>
#include "caching.hpp"
#include "DIR_caching.hpp"
#include "ASS_caching.hpp"
#include "SET_caching.hpp"
#include "BLK_caching.hpp"
#include "NWA_caching.hpp"
#include "PRF_caching.hpp"

using namespace std;

static int cl;
static caching * dir;
static caching * ass;
static caching * set;
static caching * blk;
static NWA_caching * nwa;
static PRF_caching * prf;

static void opc(caching *p, unsigned long long adr)
{
    p->check_hit(adr);
}

static void opc_nwa(NWA_caching *p, unsigned long long adr, bool store)
{
    p->set_load(store);
    p->check_hit(adr);
}

static void opc_prf(PRF_caching *p, unsigned long long adr, bool store)
{
    p->set_load(store);
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
    ass = new ASS_caching(); 
    set = new SET_caching();
    blk = new BLK_caching();
    nwa = new NWA_caching();
    prf = new PRF_caching(); 
    //the branch address
    unsigned long long adr;
  
    //the token for the store or load
    char f;

    //read in the data per line with fixed format
    while (scanf("%llx %c", &adr, &f) == 2)
    {
        cl++;
        //cout << "reach line: "<<cl << endl;
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
        opc(ass, adr);
        opc(set, adr);
        opc(blk, adr);
        opc_nwa(nwa, adr, store);
        opc_prf(prf, adr, store);
    }
    
    print_cache(dir);
    print_cache(ass);
    print_cache(set);
    print_cache(blk);
    print_cache(nwa);
    print_cache(prf);
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
    delete ass;
    delete set;
    delete blk;
    delete nwa;
    delete prf;
    return EXIT_SUCCESS;
}
