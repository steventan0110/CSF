/* Weiting Tan JHED:wtan12
 * This is the header file of predictors.cpp, which specify the predictor 
 * abstract class. 
 */
#ifndef _PREDICTORS_HPP
#define _PREDICTORS_HPP

#include <string>
using std::string;


class Predictor
{
      protected:
        unsigned correct;
        unsigned incor;
        unsigned coli;
        string name;

        /*
         * Takes pc and bt and return predicted taken or not.
         */
        virtual bool predict(int pc, int bt) = 0;

      public:
        unsigned get_correct();
        unsigned get_incorrect();
        unsigned get_collision();
        void inc_cor();
        void inc_inc();
        void inc_coli();
        string get_name();
        /*
         * Takes program counter, branch target, and taken indicator 
         * and use the predictor set by the argument to predict the 
         * branch, then return true if prediction is correct.
         */
        virtual bool get_result(int pc, int bt, bool ind) = 0;

        /* Virtual destructor */
        virtual ~Predictor() = default;
};
#endif
