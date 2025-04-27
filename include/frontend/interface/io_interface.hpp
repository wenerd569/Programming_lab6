#pragma once

#include "frontend/reader.hpp"
#include <string>

class IOInterface {
public:
    virtual ~IOInterface() {};
    virtual std::string readline () = 0;
    virtual void write (const std::string &text) = 0;
    virtual void writeError (const std::string &text) = 0;
    virtual void addNewReader (Reader reader) = 0;
};