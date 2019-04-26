/* Weiting Tan JHED: wtan12 
 * This is the implementation of predictors.hpp. 
 */
#include "Predictor.hpp"

unsigned long long Predictor::get_correct()
{
        return (this->correct);
}

unsigned long long Predictor::get_incorrect()
{
        return (this->incor);
}

unsigned long long Predictor::get_collision()
{
        return (this->coli);
}

string Predictor::get_name() 
{
        return (this->name); 
}

void Predictor::inc_cor()
{
        (this->correct)++;
}

void Predictor::inc_inc()
{
        (this->incor)++;
}

void Predictor::inc_coli()
{
        (this->coli)++;
}
