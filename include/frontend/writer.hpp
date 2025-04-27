#pragma once

#include <functional>
#include <string>

class Writer {
public:
    enum WriterType {
        Console,
        File
    };

    const WriterType type;
    const std::string name;

    bool operator==(Writer writer);
    std::function<void(const std::string &)> write;
    static Writer makeCinsoleWriter ();
};
