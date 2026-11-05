#ifndef PVMAT_H_
#define PVMAT_H_
#include <stdexcept>

#include "rstdlib.hpp"
#include <array>
#include <iostream>



class PV2 {
    public:
        f32 x = 0;
        f32 y = 0;

        PV2(bool t );

        PV2(f32 a, f32 b );



        friend std::ostream& operator <<(std::ostream& os, const PV2& p){
            os <<"<" << p.x << ", " << p.y << "> ";
            return os;
        };

        PV2 plus(PV2& that);
        PV2 minus(PV2& that);
        PV2 times(PV2& that);
        PV2 times(f32 that);
        f32 dot(PV2& that);
        f32 cross(PV2& that);
        f32 determinant(PV2& that);
        f32 dot(PV2 that);
        f32 magnitude();
        f32 distance(PV2& that);
        PV2 unit();
        void unitize();


        f32& operator[](i32 index);

}; // end of PV2 class

// start
class PV3 {
    public:
        f32 x = 0;
        f32 y = 0;
        f32 z = 0;

        PV3(bool t );

        PV3(f32 a, f32 b ,f32 c);

        PV2 xy();
        PV2 yz();
        PV2 zx();

        friend std::ostream& operator <<(std::ostream& os, const PV3& p){
            os <<"<" << p.x << ", " << p.y << ", " << p.z << ">";
            return os;
        };

        PV3 plus(PV3& that);
        PV3 minus(PV3& that);
        PV3 times(PV3& that);
        PV3 times(f32 that);
        f32 dot(PV3& that);
        PV3 cross(PV3& that);
        f32 dot(PV3 that);
        f32 magnitude();
        f32 distance(PV3& that);
        PV3 unit();
        void unitize();


        f32& operator[](i32 index);

}; // end of PV3 class

class PV4 {
    public:
        f32 x = 0;
        f32 y = 0;
        f32 z = 0;
        f32 w = 0;

        PV4(bool t );

        constexpr PV4(f32 a, f32 b ,f32 c, f32 d)
            : x(a), y(b), z(c), w(d){}


    b8 isPoint() {return this->w > 0 ;};
    b8 isVector() {return this->w == 0 ;};

        friend std::ostream& operator <<(std::ostream& os, const PV4& p){
            os <<"<" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ">";
            return os;
        };

        PV4 plus(PV4& that);
        PV4 minus(PV4& that);
        PV4 times(PV4& that);
        PV4 times(f32 that);
        f32 dot(PV4& that);
        PV4 cross(PV4& that);
        f32 dot(PV4 that);
        f32 magnitude();
        f32 distance(PV4& that);
        PV4 unit();
        void unitize();
        PV4 homogeneous();
        void homogenize();



        f32& operator[](i32 index);
        PV4 operator+(const PV4& that );

}; // end of PV4 class

#include <iomanip>

class Mat
{
    public:
        f32 data[4][4]{};

        friend std::ostream& operator <<(std::ostream& os, const Mat& m)
        {
            for (i32 i = 0; i < 4; i++) {
                os << "[";
            for (i32 j = 0; j < 4; j++) {
                os << std::fixed << std::setprecision(2) << m.data[i][j] << (j == 3 ? "" : " ");
            }
            os << "]";
            os << "\n";
        }
        return os;
        }

        constexpr Mat(): Mat(true) {};
        constexpr Mat(b8 isId)
        {
            for (i32 i = 0; i < 4; i++){
                data[i][i] = isId ? 1.0f : 0.0f;
            }
        }

    constexpr Mat(PV4 c0, PV4 c1, PV4 c2, PV4 c3);

    PV4 times(PV4& that);
    Mat times(Mat& that);


    f32* operator[](i32 row );
        constexpr Mat operator*(const Mat& that) const
        {
            Mat result(false);
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    for (int k = 0; k < 4; ++k)
                        result.data[row][col] += data[row][k] * that.data[k][col];
                }
            }
            return result;
        }
    constexpr Mat operator*(const f32 s);
        PV4 operator*(const PV4& that)
        {
            PV4 res(false);
            for (i32 i = 0; i < 4; i++){
                res[i] = this->data[i][0] * that.x +  this->data[i][1] * that.y + this->data[i][2] * that.z + this->data[i][3] * that.w;
            }
            return res;

        }
    constexpr Mat operator+(const Mat& that);
    constexpr Mat operator+(const f32 s);
        constexpr b8 operator==(const Mat& that) const
        {
            for (int row = 0; row < 4; ++row) {
                    for (int col = 0; col < 4; ++col) {
                        if ( std::abs (data[row][col] - that.data[row][col]) >  1e-4)
                            return false;
                    }
                }
                return true;
        }

    Mat transpose();

    static Mat rotation(i32 axes, f32 angle);
    static constexpr Mat translation(const PV4 &v)
        {
            Mat m(true);
            m.data[0][3] = v.x;
            m.data[1][3] = v.y;
            m.data[2][3] = v.z;
            return m;
        }
        static Mat translation(f32 t);
        static constexpr Mat scale(const PV4& v)
        {
            Mat m(true);
            m.data[0][0] = v.x;
            m.data[1][1] = v.y;
            m.data[2][2] = v.z;
            return m;
        }
    static Mat scale(f32 s);
}; // end of mat class


PV2 normalize(PV2 a);
PV3 normalize(PV3 a);
PV4 normalize(PV4 a);

f32 dot(PV2 a, PV2 b);
f32 dot(PV3 a, PV3 b);
f32 dot(PV4 a, PV4 b);

Mat transpose(Mat a);


#endif // PVMAT_H_
