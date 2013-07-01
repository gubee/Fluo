/*
 * Matrix4x4.h
 *
 *  Created on: 2013. 6. 27.
 *      Author: impaulkim
 */

#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

struct Matrix4x4 {
    float m[4][4];
    int flagBits;           // Flag bits from the enum below.

    // When matrices are multiplied, the flag bits are or-ed together.
    enum {
        Identity        = 0x0000, // Identity matrix
        Translation     = 0x0001, // Contains a translation
        Scale           = 0x0002, // Contains a scale
        Rotation2D      = 0x0004, // Contains a rotation about the Z axis
        Rotation        = 0x0008, // Contains an arbitrary rotation
        Perspective     = 0x0010, // Last row is different from (0, 0, 0, 1)
        General         = 0x001f  // General matrix, unknown contents
    };

    inline Matrix4x4() { setToIdentity(); }

    inline const float& operator()(int row, int column) const;
    inline float& operator()(int row, int column);

    inline bool isIdentity() const;
    inline void setToIdentity();
};

inline const float& Matrix4x4::operator()(int aRow, int aColumn) const
{
    //Q_ASSERT(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
    return m[aColumn][aRow];
}

inline float& Matrix4x4::operator()(int aRow, int aColumn)
{
    //Q_ASSERT(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
    flagBits = General;
    return m[aColumn][aRow];
}

inline bool Matrix4x4::isIdentity() const {
    if (flagBits == Identity)
        return true;
    if (m[0][0] != 1.0f || m[0][1] != 0.0f || m[0][2] != 0.0f)
        return false;
    if (m[0][3] != 0.0f || m[1][0] != 0.0f || m[1][1] != 1.0f)
        return false;
    if (m[1][2] != 0.0f || m[1][3] != 0.0f || m[2][0] != 0.0f)
        return false;
    if (m[2][1] != 0.0f || m[2][2] != 1.0f || m[2][3] != 0.0f)
        return false;
    if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f)
        return false;
    return (m[3][3] == 1.0f);
}

inline void Matrix4x4::setToIdentity() {
    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    flagBits = Identity;
}

#endif /* MATRIX4X4_H_ */
