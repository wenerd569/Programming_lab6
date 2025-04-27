#include "common/structures/person_precursor.hpp"

enum ValidatorStatusCode {
    Correct,
    Error,
};

template<typename T>
class Validator {
public:
    static ValidatorStatusCode validate (T &obj);
};

template<>
class Validator<PersonPrecursor> {
public:
    static ValidatorStatusCode validate (PersonPrecursor &obj);
};

template<>
class Validator<Coordinate> {
public:
    static ValidatorStatusCode validate (Coordinate &obj);
};

template<>
class Validator<Location> {
public:
    static ValidatorStatusCode validate (Location &obj);
};