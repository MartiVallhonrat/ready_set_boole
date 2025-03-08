
# include "../includes.hpp"

static void rotate(uint16_t n, uint16_t &x, uint16_t &y, uint16_t rx, uint16_t ry)
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

double  map(uint16_t x, uint16_t y)
{
    // size is max of 2^16x2^16
    uint32_t n = std::numeric_limits<uint16_t>::max() + 1;
    // eval testing
    // int32_t n = 16;
    uint32_t max = n * n - 1;

    uint16_t rx;
    uint16_t ry;
    uint32_t result = 0;

    // check for all the orders recursively
    for (uint16_t s = n/2; s > 0; s /= 2)
    {
        // check if it is in the right part
        rx = (x & s) > 0;
        // check if it is in the upper part
        ry = (y & s) > 0;
        // get result count set to the start of the quarter
        result += s * s * ((3 * rx) ^ ry);
        rotate(n, x, y, rx, ry);
    }
    
    return (static_cast<double>(result) / static_cast<double>(max));
}