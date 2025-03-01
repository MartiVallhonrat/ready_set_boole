# include "../BitsetU32.hpp"
# include "../includes.hpp"

int main(void)
{
    std::cout << "Exercise 07 - SAT: " << '\n';

    std::string formula = "AA!&";

    try
    {
        std::cout << "sat(\"" << formula << "\") ---> " << (sat(formula) ? "true" : "false") << '\n';
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
        
    return (0);
}