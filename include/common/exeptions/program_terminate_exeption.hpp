#pragma once

#include "string"
#include <stdexcept>

class ProgramTerminateException : public std::logic_error {
public:
    ProgramTerminateException(std::string message) : std::logic_error { std::move(message) } { }
};