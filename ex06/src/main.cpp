# include "../includes.hpp"

int main(void)
{
    std::cout << "Exercise 06 - Conjunctive Normal Form: " << '\n';

    std::string formula = "AB|C|D|";

    try
    {
        std::cout << "conjunctive_normal_form(\"" << formula << "\"):" << '\n' << conjunctive_normal_form(formula) << '\n';
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
        
    return (0);
}