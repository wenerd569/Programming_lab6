
#include "common/exeptions/program_terminate_exeption.hpp"
#include "frontend/program.hpp"
#include <iostream>
#include <ostream>

int main (int argc, char *argv[])
{

    Program program = Program();
    try {
        program.start();
    } catch ( ProgramTerminateException e ) {
        std::cout << e.what() << std::endl;
    } catch ( std::ios::failure e ) {
        std::cout << e.what() << std::endl;
    }
}