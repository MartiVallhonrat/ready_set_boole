# include "../includes.hpp"
# include "../BitsetU32.hpp"
# include <exception>
# include <map>

bool sat(std::string &formula)
{
    if (formula.empty())
        throw ErrorException("No input provided");
    size_t formLen = formula.length();
    std::map<char, int> variables;
    typedef std::map<char, int>::iterator map_it;

    // get variables and set them to 0
    for (size_t i = 0; i < formLen; i++)
    {
        if (std::isalpha(formula[i]))
        {
            if (std::isupper(formula[i]))
                variables[formula[i]] = 0;
            else
                throw ErrorException("All the variables must be in uppercase");
        }
    }

    // check variables size
    size_t varSize = variables.size();
    if (varSize < 1)
        throw ErrorException("Please enter at least a variable");
    if (varSize > 26)
        throw ErrorException("Max size is 26 (The English alphabet consists of 26 letters)");
    
    // get number of iters
    size_t rows = 1;
    for (size_t i = 0; i < varSize; i++)
        rows *= 2;

    BitsetU32 bitsetValues(0);
    for (size_t i = 0; i < rows; i++)
    {
        // substitute form for values
        std::string new_formula = formula;
        for (size_t i = 0; i < formLen; i++)
        {
            if (std::isalpha(formula[i]) && std::isupper(formula[i]))
                new_formula[i] = variables[formula[i]] + '0';
        }

        //calculate the result & return if true
        if (eval_formula(new_formula))
            return (true);

        // set new values
        bitsetValues.setDigit(bitsetValues.getDigit() + 1);
        int idxVar = varSize - 1;
        for (map_it it = variables.begin(); it != variables.end(); it++)
            it->second = bitsetValues[idxVar--];
    }
    
    return (false);
}