#pragma once

#include <functional>
#include <string>

class Reader {
public:
    enum ReaderType {
        Console,
        File
    };

    std::string name;
    ReaderType type;

    std::function<std::string()> readline;
    std::function<bool()> isEndOfReader;
    bool operator==(Reader other);

    static Reader makeFileReader (std::string fileNmae);
    static Reader makeConsoleReader ();
};
