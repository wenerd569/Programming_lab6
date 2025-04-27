#include "frontend/writer.hpp"
#include <iostream>

bool Writer::operator==(Writer writer)
{
    if ( type == writer.type && name == writer.name ) {
        return true;
    }
    return false;
}

Writer Writer::makeCinsoleWriter()
{
    return Writer { Writer::Console, "console", [] (std::string text) {
                       std::cout << text;
                   } };
}