#ifndef PVMAT_H_
#define PVMAT_H_
#include <stdexcept>

#include "rstdlib.hpp"
#include <array>
#include <iostream>
class PV {
    public:
        f32 x = 0;
        f32 y = 0;
        f32 z = 0;
        f32 w = 0;

        PV(bool t ){
            x = 0;
            y = 0;
            z = 0;
            if (t){
                w = 1;
            }else{
            w = 0;

        }
        }
        PV(f32 a, f32 b ,f32 c, f32 d){
            x = a;
            y = b;
            z = c;
            w = d;
        }


    b8 isPoint() {return this->w > 0 ;};
    b8 isVector() {return this->w == 0 ;};

        friend std::ostream& operator <<(std::ostream& os, const PV& p){
            os << p.x << " " << p.y << " " << p.z << " " << p.w;
            return os;
        };

        PV plus(PV& that);
        PV minus(PV& that);
        PV times(PV& that);
        PV times(f32 that);
        f32 dot(PV& that);
        PV cross(PV& that);
        f32 dot(PV that);
        f32 magnitude();
        f32 distance(PV& that);
        PV unit();
        void unitize();
        PV homogeneous();
        void homogenize();


        f32& operator[](i32 index)
        {
            switch( index ){
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: throw std::out_of_range("Index out of bounds!");
        }
    }

};



class Mat
{
    public:
    f32 data[4][4];
    Mat(b8 t)
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

    Mat(PV c0, PV c1, PV c2, PV c3)
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

    PV times(PV& that);
    Mat times(Mat& that);


    f32* operator[](i32 row )
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





    Mat transpose();

    static Mat rotation(i32 axes, f32 angle);
    static Mat translation(PV &v);
    static Mat scale(PV& v);
    static Mat scale(f32 s);
}; // end of mat class



#endif // PVMAT_H_
