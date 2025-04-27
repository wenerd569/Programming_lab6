#include "frontend/forms/coordinate_form.hpp"
#include <memory>

CoorditateForm::CoorditateForm(std::shared_ptr<IOManager> ioInterface)
    : Form { ioInterface, "coordinate" } {};

Coordinate CoorditateForm::build()
{
    return Coordinate { askNum<double>("x: double", "Поле не может быть null", false).value(),
                        askNum<int>("y: int", "Поле не может быть null", false).value() };
}