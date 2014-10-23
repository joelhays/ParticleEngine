#include "glextensions.h"

namespace GLEXT
{

    void setBlendEquation(GLuint func)
    {
        static PFNGLBLENDEQUATIONPROC glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
        glBlendEquation(func);
    }

    void setBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        static PFNGLBLENDCOLORPROC glBlendColor = (PFNGLBLENDCOLORPROC)wglGetProcAddress("glBlendColor");
        glBlendColor(red, green, blue, alpha);
    }

    void setSecondaryColor(GLfloat red, GLfloat green, GLfloat blue)
    {
        static PFNGLSECONDARYCOLOR3FEXTPROC glSecondaryColor3fEXT = (PFNGLSECONDARYCOLOR3FEXTPROC)wglGetProcAddress("glSecondaryColor3fEXT");
        glSecondaryColor3fEXT(red, green, blue);
    }

}
