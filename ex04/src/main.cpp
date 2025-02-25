# include "../BitsetU32.hpp"
# include "../includes.hpp"

int main(void)
{
    std::cout << "Exercise 04 - Truth table: " << '\n';

    std::string formula = "AB&C|";

    try
    {
        std::cout << "print_truth_table(\"" << formula << "\"):" << '\n';
        print_truth_table(formula);
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
        
    return (0);
}