#include "byte-utils.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

template< typename T >
string int_to_hex( T i )
{
  stringstream stream;
  /*stream << "\x"
         << std::setfill ('0') << std::setw(sizeof(T)*2)
         << std::hex << i;*/
  return stream.str();
}
