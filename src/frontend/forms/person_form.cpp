#include "frontend/forms/person_form.hpp"
#include "common/structures/person_precursor.hpp"
#include "frontend/forms/coordinate_form.hpp"
#include "frontend/forms/location_form.hpp"
#include <memory>

PersonForm::PersonForm(std::shared_ptr<IOManager> ioInterface) : Form { ioInterface, "person" } {};

PersonPrecursor PersonForm::build()
{
    CoorditateForm cf(io);
    LocationForm lf(io);
    return PersonPrecursor {
        askString("name: string", "не может быть null или пустой", false).value(),
        askFоrm("coordinate", &cf, false).value(),
        askNum<double>("height: double", "высота должна быть больше 0", false,
                       [] (double h) -> bool {
                           return h > 0;
                       })
            .value(),
        askEnum<Color>("eyeColor", "может быть null", true),
        askEnum<Color>("hairColor", "не может быть null", false).value(),
        askEnum<Country>("nationality", "не может быть null", false).value(),
        askFоrm("location", &lf, true)
    };
}