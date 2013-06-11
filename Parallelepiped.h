#pragma once

#ifdef __linux
    #ifndef __gl_h_
        #include <GL/gl.h>
    #endif
#elif __APPLE__ && __MACH__
    #ifndef __gl_h_
        #include <OpenGL/GL.h>
    #endif
#endif

class Parallelepiped
{
public:
    static void draw(float width, float height, float depth);
};
