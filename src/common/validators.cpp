#include "common/validators.hpp"
#include <cstddef>

// public class Person {
//     private Long id; //Поле не может быть null, Значение поля должно быть больше 0, Значение
//     этого поля должно быть уникальным, Значение этого поля должно генерироваться автоматически
//     private String name; //Поле не может быть null, Строка не может быть пустой
//     private Coordinates coordinates; //Поле не может быть null
//     private java.time.LocalDate creationDate; //Поле не может быть null, Значение этого поля
//     должно генерироваться автоматически private double height; //Значение поля должно быть больше
//     0 private Color eyeColor; //Поле может быть null private Color hairColor; //Поле не может
//     быть null private Country nationality; //Поле не может быть null private Location location;
//     //Поле может быть null
// }
// public class Coordinates {
//     private double x;
//     private Integer y; //Поле не может быть null
// }
// public class Location {
//     private Integer x; //Поле не может быть null
//     private Float y; //Поле не может быть null
//     private Long z; //Поле не может быть null
// }

ValidatorStatusCode Validator<PersonPrecursor>::validate(PersonPrecursor &obj)
{
    if ( obj.name != "" && obj.height > 0
         && Validator<Coordinate>::validate(obj.coordinate) == ValidatorStatusCode::Correct
         && (! obj.location.has_value()
             || Validator<Location>::validate(obj.location.value())
                    == ValidatorStatusCode::Correct) ) {
        return ValidatorStatusCode::Correct;
    }
    return ValidatorStatusCode::Error;
}

ValidatorStatusCode Validator<Coordinate>::validate(Coordinate &obj)
{

    return ValidatorStatusCode::Correct;
}

ValidatorStatusCode Validator<Location>::validate(Location &obj)
{
    return ValidatorStatusCode::Correct;
}

template<size_t N>
size_t indsdt ()
{
}
