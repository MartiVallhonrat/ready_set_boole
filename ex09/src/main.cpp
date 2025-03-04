# include "../includes.hpp"

static std::string printSet(std::vector<int32_t> set)
{
    std::string strSet = "{";
    for (t_int32vec it = set.begin(); it != set.end(); it++)
    {
        strSet += (*it + '0');
        if (it + 1 != set.end())
            strSet += ", ";
    }
    strSet += "}";

    return (strSet);
}

static std::string printGroup(std::vector<std::vector<int32_t>> set)
{
    std::string strSet = "{";
    for (t_vecint32vec it = set.begin(); it != set.end(); it++)
    {
        strSet += printSet(*it);
        if (it + 1 != set.end())
            strSet += ", ";
    }
    strSet += "}";

    return (strSet);
}

int main(void)
{
        std::cout << "Exercise 09 - Set evaluation: " << '\n';

        std::string formula = "AB&";
        std::vector<std::vector<int32_t>> sets = {
            {0, 1, 2},
            {0, 3, 4},
        };

        try
        {
            std::cout << "eval_set(\"" << formula << "\", " << printGroup(sets)<< ") ---> " << printSet(eval_set(formula, sets)) << '\n';
        }
        catch(std::exception  &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }

    return (0);
}