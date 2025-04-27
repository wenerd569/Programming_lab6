
#include "frontend/reader.hpp"
#include <fstream>
#include <iostream>
#include <memory>

bool Reader::operator==(Reader other)
{
    return name == other.name;
}

Reader Reader::makeConsoleReader()
{

    return Reader { "concole", Reader::Console,
                    [] () {
                        std::string line;
                        std::getline(std::cin, line);
                        return line;
                    },
                    [] () {
                        return std::cin.eof();
                    } };
}

Reader Reader::makeFileReader(std::string fileName)
{
    std::shared_ptr<std::ifstream> file = std::make_shared<std::ifstream>(fileName);
    if ( ! file || ! file->is_open() ) {
        throw std::ios_base::failure { "Не удалось открыть файл" };
    };
    return Reader { fileName, Reader::File,
                    [file] () {
                        std::string line;
                        getline(*file, line);
                        return line;
                    },
                    [file] () {
                        return file->eof();
                    } };
}