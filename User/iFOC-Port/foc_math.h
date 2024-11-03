#ifndef _FOC_MATH_H
#define _FOC_MATH_H

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
#include "math.h"
// Constant defines
#ifndef PI
#define PI 3.141592653589793238462643383279f
#endif
#define _PI_3 1.0471975511965977461542144610932f
#define _3PI_2 4.7123889803846898576939650749193f
#define PI2 6.283185307179586476925286766559f
#define SQRT_3 1.7320508075688772935274463415059f
#define SQRT_3div2 0.86602540378443864676372317075294f
#define divSQRT_3 0.57735026918962576450914878050195f
#define div2SQRT_3 1.15470053838f
// Macro defines
#define DEG2RAD(degree) ((float)(degree) * 0.01745329251994329576923690768489f)
#define RAD2DEG(radian) ((float)(radian) * 57.295779513082320876798154814105f)
#define _constrain(v,low,high) ((v)<(low)?(low):((v)>(high)?(high):(v)))
#define SQ(x) ((x) * (x))
#define SIGN(x)	(((x) < 0.0f) ? -1.0f : 1.0f)
#define NORM2_f(x,y) (sqrtf(SQ(x) + SQ(y)))
#define ABS(x) (((x) < 0.0f) ? -(x) : (x))
template<typename T>
static inline bool equal(T a, T b)
{
    return ABS(a - b) < std::numeric_limits<T>::epsilon();
}
#endif