#include "emitter.h"

Emitter::Emitter()
{
    emissionRate = 100.0f;
    emissionRadius = 0.0f;
    life = 2.0f;
    lifeRange = 0.5f;
    size = 0.5f;
    sizeRange = 0.25f;
    saturation = 0.0f;
    alpha = 0.5f;
    spread = 0.5f;
    gravity = 0.22f;
    texture = NULL;
    textureBlendMode = Emitter::BLEND_NORMAL;
    active = true;
    elapsedTime = 0;
}

Emitter::~Emitter() {
    for (int p = particles.length()-1; p >= 0; p--) {
        delete particles[p];
        particles.removeAt(p);
    }
}

void Emitter::setTexture(Texture* texture) {
    this->texture = texture;
}

void Emitter::Update(float time) {    
    if (!texture || !active) return;

    elapsedTime += time;

    int numEmissions = (int)(elapsedTime * emissionRate);

    for (int emitted = 0; emitted < numEmissions; emitted++)
        addParticle();

    if (numEmissions > 0)
        elapsedTime = 0;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //move to emitter location
    glTranslatef(position.x(), position.y(), position.z());

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glEnable(GL_BLEND);

    switch(textureBlendMode)
    {
    case Emitter::BLEND_NORMAL:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        break;
    case Emitter::BLEND_NOCOLOR:
        /*
         source = incoming pixel
         destination = pixel already drawn to frame buffer

         new color = source_color * <factor> + destination_color * <factor>
            c = sc * GL_ZERO + dc * GL_ONE_MINUS_SRC_ALPHA
            c = dc * GL_ONE_MINUS_SRC_ALPHA

         Alpha is 1 for all colored areas in the particle image so the equation becomes:
            c = dc * 0
            c = 0 -> Black
        */
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
        break;
    case Emitter::BLEND_SUBTRACT:
        //subtract this emitter's particle color from the previously rendered emitter's particle color
        //c = dc * df - sc * sf
        GLEXT::setBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        break;
    }

    //update and draw particles
    for (int p = particles.length()-1; p >= 0; p--) {
        particles[p]->acceleration.setY(-gravity);
        particles[p]->acceleration += wind;
        particles[p]->alpha = alpha;
        particles[p]->rotation = rotation;
        particles[p]->Update(time);

        if (particles[p]->active == false) {
            delete particles[p];
            particles.removeAt(p);
        }
    }

    //Set the blend function back to the default
    GLEXT::setBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Emitter::addParticle() {
    Particle *particle = new Particle(particles.length());

    //generate random color for particle
    float r = frand(0, 1) * saturation + (1 - saturation);
    float g = frand(0, 1) * saturation + (1 - saturation);
    float b = frand(0, 1) * saturation + (1 - saturation);

    particle->color = QVector3D(r,g,b);
    particle->life = frand(life - lifeRange, life + lifeRange);
    particle->totalLife = particle->life;
    particle->velocity = QVector3D(frand(-spread, spread), frand(1, 2), frand(-spread, spread));
    particle->acceleration = QVector3D(0, -gravity, 0);
    particle->size = frand(size - sizeRange, size + sizeRange);
    particle->position.setX(frand(-emissionRadius, emissionRadius));
    particle->position.setZ(frand(-emissionRadius, emissionRadius));

    particles.append(particle);
}

float Emitter::frand(float start, float end) {
    //generate between 0 and 1
    float num = (float)rand() / (float)RAND_MAX;
    return start + (end - start) * num;
}
