#pragma once

struct Location {
    int x;    //
    float y;  //
    long z;   //

    Location(int x, float y, long z) : x { x }, y { y }, z { z } {};

    Location() {};
};