# include "../includes.hpp"


int main(void)
{
    std::cout << "Exercise 11 - Inverse function: " << '\n';

    // reference http://bit-player.org/extras/hilbert/hilbert-mapping.html
    // double n = 1;
    double n = 0;
    // double n = 0.13498;

    try
    {
        std::pair<uint16_t, uint16_t> result = reverse_map(n);
        std::cout << "reverse_map(\"" << "n: " << n << "\") ---> " << "(x: " << result.first << ", y: " << result.second << ")" << '\n';
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return (0);
}