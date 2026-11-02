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

        PV4(f32 a, f32 b ,f32 c, f32 d);


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

}; // end of PV4 class

#include <iomanip>

class Mat
{
    public:
    f32 data[4][4];


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

    Mat();
    Mat(b8 t);

    Mat(PV4 c0, PV4 c1, PV4 c2, PV4 c3);

    PV4 times(PV4& that);
    Mat times(Mat& that);


    f32* operator[](i32 row );
    Mat operator*(const Mat& that);
    Mat operator*(const f32 s);
    PV4 operator*(PV4& that);
    Mat operator+(const Mat& that);
    Mat operator+(const f32 s);

    Mat transpose();

    static Mat rotation(i32 axes, f32 angle);
    static Mat translation(PV4 &v);
    static Mat translation(f32 t);
    static Mat scale(PV4& v);
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
