#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <iostream>
#include "UTkala.hpp"

class SignupHandler : public RequestHandler {
public:
  SignupHandler(UTkala* _UTkala) { UTKALA = _UTkala; }
  Response *callback(Request *);
private:
  UTkala* UTKALA;
};

Response *show_message(std::string err);

#endif