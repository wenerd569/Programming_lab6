#pragma once

#include "common/structures/location.hpp"
#include "frontend/forms/form.hpp"
#include <memory>

class LocationForm : public Form<Location> {
public:
    LocationForm(std::shared_ptr<IOManager> ioInterface);

    Location build () override;
};