/*
 * demangle.h    Name demangle hack for g++
 */
#ifndef DEMANGLE_H
#define DEMANGLE_H
#include <typeinfo>
#include <string>

std::string demangle_name(const std::type_info& typeinfo);

#endif
