#ifndef PARTICLE_H
#define PARTICLE_H

#include <qgl.h>
#include <QVector3D>
#include <QMatrix4x4>

class Particle
{
public:
    Particle(int id);

    void Update(float time);

public:
    int id;

    QVector3D
        color,
        position,
        velocity,
        acceleration,
        rotation;

    float
        totalLife,
        life,
        alpha,
        size;

    bool active;
};

#endif // PARTICLE_H
