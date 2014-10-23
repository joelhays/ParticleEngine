#ifndef GLEXTENSIONS_H
#define GLEXTENSIONS_H

#include <qgl.h>
#include <GL/glext.h>


namespace GLEXT
{
    extern void setBlendEquation(GLuint func);
    extern void setBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    extern void setSecondaryColor(GLfloat red, GLfloat green, GLfloat blue);
}



#endif
