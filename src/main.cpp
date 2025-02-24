# include "../BitsetU32.hpp"
# include "../includes.hpp"

int main(void)
{
    // {
    //     std::cout << "Exercise 00 - Adder: " << '\n';
        
    //     BitsetU32 bitset1(22);
    //     BitsetU32 bitset2(20);
    
    //     std::cout << bitset1  << " + " << bitset2 << " = " << bitset1 + bitset2 << '\n';
    // }
    // {
    //     std::cout << "\n"
    //     << "Exercise 01 - Multiplier: " << '\n';

    //     BitsetU32 bitset1(7);
    //     BitsetU32 bitset2(6);
    
    //     std::cout << bitset1  << " * " << bitset2 << " = " << bitset1 * bitset2 << '\n';
    // }
    // {
    //     std::cout << "\n"
    //     << "Exercise 02 - Gray code: " << '\n';

    //     BitsetU32 bitset1(42);
    //     BitsetU32 bitset2 = bitset1.getGC();
    
    //     std::cout << bitset1 << ": " << "(Binary: " << bitset1.getBinary() << ") ---> " << "(GrayCode: " << bitset2.getBinary() << ")\n";
    // }
    // {
    //     std::cout << "\n"
    //     << "Exercise 03 - Boolean evaluation: " << '\n';

    //     std::string formula = "1011||=";

    //     try
    //     {
    //         std::cout << "eval_formula(\"" << formula << "\") ---> " << (eval_formula(formula) ? "true" : "false") << '\n';
    //     }
    //     catch(std::exception  &e)
    //     {
    //         std::cerr << "Error: " << e.what() << '\n';
    //     }
        
    // }
    {
        std::cout << "\n"
        << "Exercise 04 - Truth table: " << '\n';

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
        
    }
    return (0);
}