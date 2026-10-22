#include <iostream>
#include "PVMat.hpp"
#include <cmath>
#include <ctime>


f32 randf(i32 min, i32 max)
{
    float zero_one = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    return min + zero_one * ((f32) (max - min) );
}


#define MIN_VAL 2
#define MAX_VAL 10


PV4 vertices[] = {PV4(-0.5, 0.0, 0.0, 1), PV4(0.5, 0.0, 0.0, 1.0), PV4(0.0, 0.5, 0.0, 1.0)};
i32 edges [3][2] =  { {0,1}, {1,2} , {2, 0} };


i32 main(void)
{




}// end of the main method
