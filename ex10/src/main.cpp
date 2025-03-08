# include "../includes.hpp"


int main(void)
{
    std::cout << "Exercise 10 - Curve: " << '\n';

    // uint16_t x = 0;
    uint16_t y = 0;
    uint16_t x = std::numeric_limits<uint16_t>::max();
    // uint16_t y = std::numeric_limits<uint16_t>::max();
    
    // for eval testing 
    // reference http://bit-player.org/extras/hilbert/hilbert-mapping.html
    // uint16_t x = 16 - 1;
    // uint16_t y = 0;

    try
    {
        std::cout << "map(\"" << "x: " << x  << ",  y: " << y << "\") ---> " << map(x, y) << '\n';
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return (0);
}