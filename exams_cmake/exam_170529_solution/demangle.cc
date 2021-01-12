/*
 * demangle.cc    Name demangle hack for g++
 */
#include <cxxabi.h>
#include <typeinfo>
#include <string>
using namespace std;
using abi::__cxa_demangle;

string demangle_name(const type_info& typeinfo)
{
   int status;
   char* name = __cxa_demangle(typeinfo.name(), nullptr, nullptr, &status);

   if (name)
   {
      string demangled(name);
      free(name);
      return demangled;
   }

   if (status == 0)
      return "error code = 0: success";
   else if (status == -1)
      return "error code = -1: memory allocation failure";
   else if (status == -2)
      return "error code = -2: invalid mangled name";
   else if (status == -3)
      return "error code = -3: invalid arguments";
   else
      return "error code unknown - who knows what happened";
}
