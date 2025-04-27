#pragma once

#include "common/exeptions/program_terminate_exeption.hpp"
#include "frontend/reader.hpp"
#include "frontend/writer.hpp"
#include <vector>

class IOManager {
protected:
    std::vector<Reader> readerStack;
    Writer writer;

public:
    IOManager(Reader reader, Writer writer);

    ~IOManager();
    void openNewReader (Reader reader);
    std::string readline ();
    void write (const std::string &text);
    void writeError (const std::string &text);
};
