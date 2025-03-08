
# include "../includes.hpp"

static void rotate(uint32_t n, uint16_t &x, uint16_t &y, uint16_t rx, uint16_t ry)
{
    int tmp;
    // only rotate the quarter if it is in the bottom half like the Hilbert Curve sequence
    if (ry == 0)
    {
        // if it is in the right quarter
        if (rx == 1)
        {
            x = (n - 1) - x;
            y = (n - 1) - y;
        }
        tmp = x;
        x = y;
        y = tmp;
    }
}

std::pair<uint16_t, uint16_t>  reverse_map(double n)
{
    if (n > 1 || n < 0)
        throw ErrorException("Please enter a valid number (from 0 to 1).");
    
    // size is max of 2^16x2^16
    uint32_t side = std::numeric_limits<uint16_t>::max();
    std::cout << "side: " << side << '\n';
    // eval testing
    // int32_t side = 16;
    uint32_t max = side * side - 1;

    uint16_t rx;
    uint16_t ry;
    uint32_t int_n = n * max;
    uint32_t t = int_n;
    std::pair<uint16_t, uint16_t> result = {0, 0};

    for (uint32_t s = 1; s < side; s *= 2)
    {
        rx = 1 & (t/2);
        ry = 1 & (t ^ rx);
        rotate(s, result.first, result.second, rx, ry);
        result.first += s * rx;
        result.second += s * ry;
        t /= 4;
    }
    
    
    return (result);
}