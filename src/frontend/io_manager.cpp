#include "frontend/io_manager.hpp"
#include <ios>

IOManager::IOManager(Reader reader, Writer writer) : readerStack {}, writer { std::move(writer) }
{
    readerStack.push_back(std::move(reader));
}

IOManager::~IOManager() = default;

void IOManager::openNewReader(Reader reader)
{
    for ( int i = 0; i <= readerStack.size(); i++ ) {
        if ( readerStack[i] == reader ) {
            throw std::ios_base::failure {
                "Возникла ошибка: попытка рекурсивного открытия скрипта"
            };
        }
    }
    readerStack.push_back(std::move(reader));
}

std::string IOManager::readline()
{
    std::string res;
    res = readerStack.back().readline();
    while ( readerStack.back().isEndOfReader() ) {
        readerStack.pop_back();
        if ( res == "" ) {
            if ( readerStack.empty() ) {
                throw ProgramTerminateException("Принудительное завершение програмы");
            }
            res = readerStack.back().readline();
        }
    }
    return res;
}

void IOManager::write(const std::string &text)
{
    if ( readerStack.back().type != Reader::Console ) {
        return;
    }
    writer.write(text);
}

void IOManager::writeError(const std::string &text)
{
    writer.write(text);
}