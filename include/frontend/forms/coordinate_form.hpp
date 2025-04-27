#pragma once

#include "common/structures/coordinate.hpp"
#include "frontend/forms/form.hpp"

class CoorditateForm : public Form<Coordinate> {
public:
    CoorditateForm(std::shared_ptr<IOManager> ioInterface);

    Coordinate build () override;
};