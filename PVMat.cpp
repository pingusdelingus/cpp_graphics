#include "PVMat.hpp"
#include "rstdlib.hpp"
#include <cmath>


PV2::PV2(f32 a, f32 b )
{
    x = a;
    y = b;
}


PV2::PV2(bool t ){
            x = 1 * t;
            y = 1 * t;
}

f32& PV2::operator[](i32 index)
        {
            switch( index ){
                case 0: return x;
                case 1: return y;
                default: throw std::out_of_range("Index out of bounds!");
        }
    }

PV2 PV2::plus(PV2& that)
{
    return *(new PV2(this->x + that.x, this->y + that.y ));
}


PV2 PV2::minus(PV2& that)
{
    return *(new PV2(this->x - that.x, this->y - that.y));
}

PV2 PV2::times(PV2& that)
{
    return *(new PV2(this->x * that.x, this->y * that.y ));
}

PV2 PV2::times(f32 that)
{
    return *(new PV2(this->x * that, this->y * that ));
}

f32 PV2::dot(PV2& that)
{
    return (this->x * that.x + this->y * that.y );
}


f32 PV2::dot(PV2 that)
{
    return (this->x * that.x + this->y * that.y );
}


f32 PV2::cross(PV2& that)
{
    return (this->x * that.y) - (this->y * that.x);
}


f32 PV2::determinant(PV2& that)
{
    return this->cross(that);
}


f32 PV2::magnitude()
{
    return std::sqrt(this->dot((PV2*)this));
}



f32 PV2::distance(PV2& that)
{
    return this->minus(that).magnitude();
}


PV2 PV2::unit()
{
    f32 mag = this->magnitude();
    if (mag != 0){
    PV2 ans = *this;

    return ans.times( 1.0/ mag );

    }
    return *this;
}


void PV2::unitize()
{
    f32 mag = this->magnitude();
    if (mag != 0){
        this->x /= mag;
        this->y /= mag;
    }
}

// start pv3

PV2 PV3::xy()
{
   return PV2(this->x, this->y);
}
PV2 PV3::yz()
{
   return PV2(this->y, this->z);
}

PV2 PV3::zx()
{
   return PV2(this->z, this->x);
}


PV3::PV3(f32 a, f32 b ,f32 c)
{
    x = a;
    y = b;
    z = c;
}


PV3::PV3(bool t ){
            x = 1 * t;
            y = 1 * t;
            z = 1 * t;


}

f32& PV3::operator[](i32 index)
        {
            switch( index ){
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw std::out_of_range("Index out of bounds!");
        }
    }

PV3 PV3::plus(PV3& that)
{
    return *(new PV3(this->x + that.x, this->y + that.y, this->z + that.z));
}


PV3 PV3::minus(PV3& that)
{
    return *(new PV3(this->x - that.x, this->y - that.y, this->z - that.z));
}

PV3 PV3::times(PV3& that)
{
    return *(new PV3(this->x * that.x, this->y * that.y, this->z * that.z ));
}

PV3 PV3::times(f32 that)
{
    return *(new PV3(this->x * that, this->y * that, this->z * that ));
}

f32 PV3::dot(PV3& that)
{
    return (this->x * that.x + this->y * that.y + this->z * that.z );
}


f32 PV3::dot(PV3 that)
{
    return (this->x * that.x + this->y * that.y + this->z * that.z );
}


PV3 PV3::cross(PV3& that)
{
            return *(new PV3(this->y * that.z - this->z * that.y,
                          this->z * that.x - this->x * that.z,
                          this->x * that.y - this->y * that.x
                          ));
}

f32 PV3::magnitude()
{
    return std::sqrt(this->dot((PV3*)this));
}



f32 PV3::distance(PV3& that)
{
    return this->minus(that).magnitude();
}


PV3 PV3::unit()
{
    f32 mag = this->magnitude();
    if (mag != 0){
    PV3 ans = *this;

    return ans.times( 1.0/ mag );

    }
    return *this;
}


void PV3::unitize()
{
    f32 mag = this->magnitude();
    if (mag != 0){
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }
}








// start
PV4::PV4(f32 a, f32 b ,f32 c, f32 d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}


PV4::PV4(bool t ){
            x = 0;
            y = 0;
            z = 0;
            if (t){
                w = 1;
            }else{
            w = 0;

        }
}

f32& PV4::operator[](i32 index)
        {
            switch( index ){
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: throw std::out_of_range("Index out of bounds!");
        }
    }

PV4 PV4::plus(PV4& that)
{
    return *(new PV4(this->x + that.x, this->y + that.y, this->z + that.z, this->w + that.w));
}


PV4 PV4::minus(PV4& that)
{
    return *(new PV4(this->x - that.x, this->y - that.y, this->z - that.z, this->w - that.w));
}

PV4 PV4::times(PV4& that)
{
    return *(new PV4(this->x * that.x, this->y * that.y, this->z * that.z, this->w * that.w));
}

PV4 PV4::times(f32 that)
{
    return *(new PV4(this->x * that, this->y * that, this->z * that, this->w * that));
}

f32 PV4::dot(PV4& that)
{
    return (this->x * that.x + this->y * that.y + this->z * that.z + this->w * that.w);
}


f32 PV4::dot(PV4 that)
{
    return (this->x * that.x + this->y * that.y + this->z * that.z + this->w * that.w);
}


PV4 PV4::cross(PV4& that)
{
            return *(new PV4(this->y * that.z - this->z * that.y,
                          this->z * that.x - this->x * that.z,
                          this->x * that.y - this->y * that.x,
                          0.0f));
}

f32 PV4::magnitude()
{
    return std::sqrt(this->dot((PV4*)this));
}



f32 PV4::distance(PV4& that)
{
    return this->minus(that).magnitude();
}


PV4 PV4::unit()
{
    f32 mag = this->magnitude();
    if (mag != 0){
    PV4 ans = *this;

    return ans.times( 1.0/ mag );

    }
    return *this;
}


void PV4::unitize()
{
    f32 mag = this->magnitude();
    if (mag != 0){
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
        this->w /= mag;
    }
}

PV4 PV4::homogeneous()
{
    if (this->w == 0){
        return *this;
    }

    return this->times(1.0 / this->w);
}



void PV4::homogenize()
{
    if (this->w == 0){
        return;
    }
        this->x /= this->w;
        this->y /= this->w;
        this->z /= this->w;
        this->w /= this->w;
}

f32* Mat::operator[](i32 row )
    {
        switch(row){
            case 0:
            case 1:
            case 2:
            case 3:
                return data[row];
            default:
            throw std::out_of_range("Index out of bounds!");
        }
}
Mat::Mat(PV4 c0, PV4 c1, PV4 c2, PV4 c3)
    {
        data[0][0] = c0.x;
        data[0][1] = c0.y;
        data[0][2] = c0.z;
        data[0][3] = c0.w;

        data[1][0] = c1.x;
        data[1][1] = c1.y;
        data[1][2] = c1.z;
        data[1][3] = c1.w;

        data[2][0] = c2.x;
        data[2][1] = c2.y;
        data[2][2] = c2.z;
        data[2][3] = c2.w;

        data[3][0] = c3.x;
        data[3][1] = c3.y;
        data[3][2] = c3.z;
        data[3][3] = c3.w;
    }
Mat::Mat()
{
        for (i32 i = 0; i < 4; i++){
            for (i32 j = 0; j < 4; j++){
                if (i != j){
                    data[i][j] = 0.0f;
                }else{
                    data[i][j] = 1.0f;
                }
            }
        }
}

Mat::Mat(b8 t)
    {
        for (i32 i = 0; i < 4; i++){
            for (i32 j = 0; j < 4; j++){
                if (i != j){
                    data[i][j] = 0.0f;
                }else{
                    data[i][j] = 1.0f * t;
                }
            }
        }
    }


PV4 Mat::times(PV4& that)
{
    PV4 v = new PV4(false);

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
                m[i][j] += this->data[i][k] * that.data[k][j];
            }
        }
    }

    return m;
}



Mat Mat::transpose()
{
    Mat res(false);

    for (i32 i = 0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
            res[i][j] = this->data[j][i];
        }
    }
    return res;
}



Mat Mat::rotation(i32 axes, f32 angle)
{
    Mat mat(false);
    i32 i = axes;
    i32 j = (i + 1) % 3;
    i32 k = (i + 2) % 3;
    mat[j][j] = std::cos(angle);
    mat[k][j] = std::sin(angle);
    mat[j][k] = -mat[k][j];
    mat[k][k] = mat[j][j];

    return mat;
}


Mat Mat::translation(f32 t)
{
    Mat mat(true);
    for (i32 i = 0; i < 3; i++){
        mat[i][3] = t;
    }
    return mat;


}

PV4 Mat::operator*(PV4& that)
{
    PV4 res(false);
    f32 sum = 0.0f;
    for (i32 i = 0; i < 4; i++){
        for (i32 j = 0; j < 4 ; j ++){
            sum += this->data[i][j] * that[j];
        }
        res[i] = sum;
        sum = 0.0f;
    }
    return res;
}


Mat Mat::operator+(const f32 s )
{
    Mat m(false);
    for (i32 i =0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
                m[i][j] = this->data[i][j] + s;
        }
    }

    return m;


}


Mat Mat::operator+(const Mat& that)
{
    Mat m(false);
    for (i32 i =0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
                m[i][j] = this->data[i][j] + that.data[i][j];
        }
    }

    return m;

}


Mat Mat::operator*(const f32 s)
{
    Mat m(false);
    for (i32 i =0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
                m[i][j] = this->data[i][j] * s;
        }
    }

    return m;
}



Mat Mat::operator*(const Mat& that)
{
    Mat m(false);
    for (i32 i =0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
            for (i32 k = 0; k < 4; k++ ){
                m[i][j] += this->data[i][k] * that.data[k][j];
            }
        }
    }

    return m;
}



Mat Mat::translation(PV4& p)
{
    Mat mat(true);
    for (i32 i = 0; i < 3; i++){
        mat[i][3] = p[i];
    }
    return mat;


}



Mat Mat::scale(PV4& p)
{
    Mat mat(true);
    for (i32 i = 0; i < 3; i++){
        mat[i][i] = p[i];
    }
    return mat;


}



Mat Mat::scale(f32 scale)
{
    Mat mat(true);
    for (i32 i = 0; i < 3; i++){
        mat[i][i] = scale;
    }
    return mat;
}



PV2 normalize(PV2 a)
{
    f32 mag = a.magnitude();
    return PV2(a.x / mag, a.y / mag);
}
PV3 normalize(PV3 a)
{
    f32 mag = a.magnitude();
    return PV3(a.x / mag, a.y / mag, a.z / mag);

}
PV4 normalize(PV4 a)
{
    f32 mag = a.magnitude();
    return PV4(a.x / mag, a.y / mag, a.z / mag, a.w / mag);
}

f32 dot(PV2 a, PV2 b)
{
    return a.dot(std::move(b));
}


f32 dot(PV3 a, PV3 b)
{
    return a.dot(std::move(b));
}
f32 dot(PV4 a, PV4 b)
{
    return a.dot(std::move(b));
}

Mat transpose(Mat a)
{
    Mat r(false);
    for (i32 i = 0; i < 4; i++){
        for (i32 j = 0; j < 4; j++){
            r.data[i][j] = a.data[j][i];
        }
    }
    return r;
}
