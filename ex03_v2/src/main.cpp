
# include "../includes.hpp"

int main(void)
{
        std::cout << "Exercise 03 - Boolean evaluation: " << '\n';

        std::string formula = "1011||=";

        try
        {
            std::cout << "eval_formula(\"" << formula << "\") ---> " << (eval_formula(formula) ? "true" : "false") << '\n';
        }
        catch(std::exception  &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }

    return (0);
}