#pragma once

struct Coordinate {
    double x;
    int y;

public:
    Coordinate(double x, int y) : x { x }, y { y } {};
    Coordinate() {};
};