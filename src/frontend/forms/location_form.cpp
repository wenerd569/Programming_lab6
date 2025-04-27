#include "frontend/forms/location_form.hpp"
#include <memory>

LocationForm::LocationForm(std::shared_ptr<IOManager> ioInterface)
    : Form { ioInterface, "location" } {};

Location LocationForm::build()
{
    return Location { askNum<int>("x: int", "не может быть null", false).value(),
                      askNum<float>("y: float", "не может быть null", false).value(),
                      askNum<long>("z: long", "не может быть null", false).value() };
}