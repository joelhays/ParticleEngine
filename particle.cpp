#include "particle.h"

Particle::Particle(int id) :
    id(id), totalLife(1), life(1), alpha(.1), size(1),
    active(true) {}

void Particle::Update(float elapsedTime) {
    if (!active) return;

    velocity += acceleration * elapsedTime;
    position += velocity * elapsedTime;

    QMatrix4x4 rot;
    rot.rotate(rotation.x() * elapsedTime, 1, 0, 0);
    rot.rotate(rotation.y() * elapsedTime, 0, 1, 0);
    rot.rotate(rotation.z() * elapsedTime, 0, 0, 1);

    position = rot * position;
    float px = position.x(), py = position.y(), pz = position.z();

    const float fadeTime = 0.2f;
    if (totalLife - life < fadeTime) {
        glColor4f(color.x(), color.y(), color.z(), (totalLife - life) / fadeTime * alpha);
    }
    else if (life < 1.0f) {
        glColor4f(color.x(), color.y(), color.z(), life * alpha);
    }
    else {
        glColor4f(color.x(), color.y(), color.z(), alpha);
    }



    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(px, py, pz);

    //want particle to always face camera, so need to reset rotation
    //values of the modelview matrix to identity

    //retrieve OpenGL modelview matrix
    float modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            modelview[i * 4 + j] = (i == j ? 1.0f : 0.0f);
        }
    }

    glLoadMatrixf(modelview);

    if (id % 5 == 0) {
        glRotatef(life * 100.0f, 0, 0, 1);
    }
    else {
        glRotatef(life * -100.0f, 0, 0, 1);
    }

    //draw particle
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(1,1); glVertex3f(size, size, 0);
        glTexCoord2f(1,0); glVertex3f(-size, size, 0);
        glTexCoord2f(0,1); glVertex3f(size, -size, 0);
        glTexCoord2f(0,0); glVertex3f(-size, -size, 0);
    glEnd();

    glPopMatrix();

    life -= elapsedTime;

    if (life <= 0.0f) {
        active = false;
    }
}
