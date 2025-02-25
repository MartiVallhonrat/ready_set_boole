# include "../includes.hpp"
# include <exception>
# include <algorithm>
# include <array>
# include <stack>

bool eval_formula(std::string &formula)
{
    if (formula.empty())
        throw ErrorException("No input provided");
    // no negative in operators
    std::array<char, 6> operators = {'&', '|', '^', '>', '='};
    std::array<char, 2> values = {'0', '1'};
    size_t formLen = formula.length();

    std::stack<int> numStack;
    int result;

    for (size_t i = 0; i < formLen; i++)
    {
        if (std::find(operators.begin(), operators.end(), formula[i]) != operators.end())
        {
            if (numStack.empty())
                throw ErrorException("Invalid number of operators");
            int fromStack = numStack.top();
            numStack.pop();
            if (numStack.empty())
                throw ErrorException("Invalid number of operators");
            result = numStack.top();
            numStack.pop();
            switch (formula[i])
            {
                case '&':
                    result &= fromStack;
                    break;
                case '|':
                    result |= fromStack;
                    break;               
                case '^':
                    result ^= fromStack;
                    break;
                case '>':
                        result = (!result) | fromStack;
                    break;
                case '=':
                    result = (result == fromStack);
                    break;
            }
            numStack.push(result);
        }
        else if (std::find(values.begin(), values.end(), formula[i]) != values.end())
        {
            numStack.push(formula[i] - '0');
        }
        else if (formula[i] == '!')
        {
            if (numStack.empty())
                throw ErrorException("Invalid number of numbers");

            result = numStack.top();
            numStack.pop();
            result = !result;
            numStack.push(result);
        }
        else
            throw ErrorException("Invalid Input");
    }

    result = numStack.top();
    numStack.pop();
    if (!numStack.empty())
        throw ErrorException("Invalid number of values");

    return (result);
}