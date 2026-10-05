#include "PVMat.hpp"
#include "rstdlib.hpp"
#include <cmath>


PV PV::plus(PV& that)
{
    return *(new PV(this->x + that.x, this->y + that.y, this->z + that.z, this->w + that.w));
}


PV PV::minus(PV& that)
{
    return *(new PV(this->x - that.x, this->y - that.y, this->z - that.z, this->w - that.w));
}

PV PV::times(PV& that)
{
    return *(new PV(this->x * that.x, this->y * that.y, this->z * that.z, this->w * that.w));
}

PV PV::times(f32 that)
{
    return *(new PV(this->x * that, this->y * that, this->z * that, this->w * that));
}

f32 PV::dot(PV& that)
{
    return (this->x * that.x + this->y * that.y + this->z * that.z + this->w * that.w);
}


PV PV::cross(PV& that)
{
            return *(new PV(this->y * that.z - this->z * that.y,
                          this->z * that.x - this->x * that.z,
                          this->x * that.y - this->y * that.x,
                          0.0f));
}

f32 PV::magnitude()
{
    return std::sqrt(this->dot(&this));
}



f32 PV::distance(PV& that)
{
    return this->minus(that).magnitude();
}


PV PV::unit()
{
    f32 mag = this->magnitude();
    if (mag != 0){
    PV ans = *this;

    return ans.times( 1.0/ mag );

    }
    return *this;
}


void PV::unitize()
{
    f32 mag = this->magnitude();
    if (mag != 0){
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
        this->w /= mag;
    }
}

PV PV::homogeneous()
{
    if (this->w == 0){
        return *this;
    }

    return this->times(1.0 / this->w);
}



void PV::homogenize()
{
    if (this->w == 0){
        return;
    }
        this->x /= this->w;
        this->y /= this->w;
        this->z /= this->w;
        this->w /= this->w;
}


PV Mat::times(PV& that)
{
    PV v = new PV(false);

    for (i32 i = 0 ; i < 4; i++){
        f32 sum = 0.0f;
        for (i32 j = 0; j < 4; j++){
            sum+= this->data[i][j] * that[i];
        }
        v[i] = sum;

    }
    return v;
}


Mat Mat::times(Mat& that)
{
    Mat m(false);
    for (i32 i =0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
            for (i32 k = 0; k < 4; k++ ){
                m[i][j] += this->data[i][k] * that.data[k][j]
            }
        }
    }


}
