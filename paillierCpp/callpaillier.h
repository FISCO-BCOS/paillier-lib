/** @file callpaillier.h
 *  @author shawnhe 
 *  @date 20190816
 */

#pragma once
#include <exception>
#include <string>

struct CallException : public std::exception
{

public:
    CallException(char *e)
    {
        myException = e;
    }
    virtual char *what()
    {
        return myException;
    }

private:
    char *myException;
};

class CallPaillier
{
    // Encapsulate call protocol
public:
    CallPaillier(){};
    ~CallPaillier(){};
    std::string paillierAdd(std::string &cipher1, std::string &cipher2);
};