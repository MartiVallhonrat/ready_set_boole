#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <iostream> 

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

bool    eval_formula(std::string &formula);
void    print_truth_table(std::string &formula);

#endif