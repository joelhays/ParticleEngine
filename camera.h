#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QQuaternion>
#include <qmath.h>

class Camera
{
public:
    Camera();

    float distance;
    QVector3D lookAt,
        Up, //viewplane for Y screen axis
        Right; //viewplane for X screen axis
    QQuaternion rotationX, rotationY;

    void rotate(float xdelta, float ydelta);
    void pan(float xdelta, float ydelta);
    void zoom(float xdelta);

    void reset();

    void saveStateAsDefaults();

private:
    void setViewVectors();

private:
    float default_distance;
    QVector3D default_lookAt;
    QQuaternion default_rotationX, default_rotationY;

};

#endif // CAMERA_H
