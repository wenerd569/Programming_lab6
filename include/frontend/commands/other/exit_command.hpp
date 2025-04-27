
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief exit : завершить программу (без сохранения в файл)
 *
 */
class ExitCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface);
};