/** @file callpaillier.h
 *  @author shawnhe
 *  @date 20190816
 */

#pragma once
#include <exception>
#include <string>

struct CallException : public std::exception {

public:
  CallException(char *e) { myException = e; }
  virtual char *what() { return myException; }

private:
  char *myException;
};

class CallPaillier {
  // Encapsulate call protocol
public:
  CallPaillier(){};
  ~CallPaillier(){};

  // cipher is hex structured
  std::string paillierAdd(const std::string &cipher1,
                          const std::string &cipher2);

  // cipher is non-hex structured
  std::vector<unsigned char>
  paillierAdd(const std::vector<unsigned char> &cipher1,
              const std::vector<unsigned char> &cipher2);
};