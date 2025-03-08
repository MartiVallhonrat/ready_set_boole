#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <iostream>
# include <cstdint>
# include <limits>

class ErrorException: public std::exception
{
    private:
        std::string msg;

    public:
        ErrorException(std::string new_msg): msg(new_msg) {}
        const char  *what() const throw()
        {
            return (this->msg.c_str());
        }
};

std::pair<uint16_t, uint16_t>  reverse_map(double n);

#endif