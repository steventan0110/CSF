/* Weiting Tan JHED:wtan12
 * This program takes in a branch trace from std::cin and a predictor and its 
 * settings from commandline arguments, then attemps to predict each branch 
 * while recording the results. When all are predicted, it output relevant 
 * data about the predictions to std::cout.
 * Those data include how many total branch has been predicted, how many were
 * correct, how many were not, and their respective percentages. It also output
 * the theoratical size of a hardware implementation of the predictor used.
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>

#include "Predictor.hpp"
#include "STA_Predictor.hpp"
#include "BAH_Predictor.hpp"
#include "TAH_Predictor.hpp"
#include "BTA_Predictor.hpp"
#include "SAT_Predictor.hpp"
#include "COL_Predictor.hpp"
#include "TWO_Predictor.hpp"

using namespace std;

static Predictor *sta; /* predictor object pointer */
static Predictor *bah;
static Predictor *tah;
static Predictor *bta;
static Predictor *sat;
static Predictor *col;
static Predictor *two;
static int cl;         /* current line number */

static void opc(Predictor *p, int banch, int target, bool token)
{
    p->get_result(banch, target, token);
}


static void print_predictor(Predictor *p)
{
    string name = p->get_name();
    unsigned long long correct = p->get_correct();
    unsigned long long incorrect = p->get_incorrect();
    unsigned long long collision = p->get_collision();
    printf("%s: %20llu %20llu %20llu\n", name.c_str(), correct, incorrect, collision);
}

/*
 * Takes input from cin and parse the brance trace, feeding the parsed data 
 * to update the global data about the whole set.
 */
static void parse()
{
    int pc;
    int bt;

    bool result;
    bool actual;

    //initiate the pointer to different pointer:
    sta = new STA_Predictor();
    bah = new BAH_Predictor();
    tah = new TAH_Predictor(); 
    bta = new BTA_Predictor();
    col = new COL_Predictor();
    sat = new SAT_Predictor();
    two = new TWO_Predictor();
    //the branch address
    unsigned long long b_adr;
    //the target address
    unsigned long long t_adr;
    //the token for the flag
    char f;
    //read in the data per line with fixed format
    while (scanf("%llx %llx %c", &b_adr, &t_adr, &f) == 3)
    {
        cl++;
        //cout<<"current address is "<<cl << endl;
        bool token;
        if (f == 'T')
        {
            token = true;
        }
        else
        {
            token = false;
        }
        opc(sta, b_adr, t_adr, token);
        opc(bah, b_adr, t_adr, token);
        opc(tah, b_adr, t_adr, token);
        opc(bta, b_adr, t_adr, token);
        opc(col, b_adr, t_adr, token);
        opc(sat, b_adr, t_adr, token);
        opc(two, b_adr, t_adr, token);
        
    }
    
    print_predictor(sta);
    print_predictor(bah);
    print_predictor(tah);
    print_predictor(bta);
    print_predictor(col);
    print_predictor(sat);
    print_predictor(two);
}

/*
 * Parse the input branch traces line by line, check for any data or format 
 * error, and calculate some useful measurements about the branch trace.
 */
int main(int argc, char *argv[])
{
    //parse in the input from stdin:
    parse();
    delete sta;
    delete bah;
    delete tah;
    delete bta;
    delete col;
    delete sat;
    delete two;
    return EXIT_SUCCESS;
}
