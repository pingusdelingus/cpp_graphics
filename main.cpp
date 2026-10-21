#include <iostream>
#include "PVMat.hpp"
#include <cmath>
#include <ctime>



f32 randf(i32 max, i32 min)
{

float zero_one = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

    i32 tempmax = min + 1;


    f32 mult = (f32)max / tempmax;

    return min + zero_one * ((f32) (max - min) );
}

#define MIN_VAL 2
#define MAX_VAL 10
auto main(int argc, char *argv[]) -> int {

srand(time(NULL));
    Mat id(true);


    PV4 p1(randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL));
    PV4 p2(randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL));
    PV4 p3(randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL));
    PV4 p4(randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL),randf(MAX_VAL, MIN_VAL));



    Mat m;


    std::cout << p1 << std::endl;
    std::cout << m * Mat::translation(2.0);

    return 0;
}
