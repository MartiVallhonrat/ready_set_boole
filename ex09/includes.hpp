#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <iostream>
# include <vector>
# include <map>

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

typedef std::vector<int32_t>::iterator t_int32vec;
typedef std::vector<std::vector<int32_t>>::iterator t_vecint32vec;
typedef std::map<char, std::vector<int32_t>>::iterator t_mapvec;

std::vector<int32_t> eval_set(std::string &formula, std::vector<std::vector<int32_t>>);

#endif