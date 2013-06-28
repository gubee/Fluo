/*
 * Matrix4x4.h
 *
 *  Created on: 2013. 6. 27.
 *      Author: impaulkim
 */

#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

class Matrix4x4 {
public:
    QMatrix4x4::QMatrix4x4(const float* values)
    {
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col)
                m[col][row] = values[row * 4 + col];
        flagBits = General;
    }

private:
    float m[4][4];
};

#endif /* MATRIX4X4_H_ */
