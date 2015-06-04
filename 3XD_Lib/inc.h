
#ifndef X3Dlib_INC
#define X3Dlib_INC

// mathematics
#define PI 3.14159265358979323846


// distance for camera to perspective projection plane
#define VIEWPORT_DISTANCE	5
#define SCALE_PROPORTION	100.0

// vector operations
#define PRO_DOT %
#define PRO_CROSS |
#define PRO_PARALLEL ||
#define PRO_UPRIGHT &&

#define EPSINON 0.0000000000000001
#define DOUBLE_EQ( x, y ) (((x) - (y) >= -EPSINON) && ((x) - (y) <= EPSINON))

#endif