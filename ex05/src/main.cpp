# include "../includes.hpp"

int main(void)
{
    std::cout << "Exercise 05 - Negation Normal Form: " << '\n';

    std::string formula = "AB&!";

    try
    {
        std::cout << "negation_normal_form(\"" << formula << "\"):" << '\n' << negation_normal_form(formula) << '\n';
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
        
    return (0);
}