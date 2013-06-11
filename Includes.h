#ifndef INCLUDES
#define INCLUDES

#ifdef __linux
    #ifndef __gl_h_
        #include <GL/gl.h>
    #endif
    #ifndef __glu_h_
        #include <GL/glu.h>
    #endif
    #ifndef __GLUT_H__
        #include <GL/glut.h>
    #endif
#elif __APPLE__ && __MACH__
    #ifndef __gl_h_
        #include <OpenGL/GL.h>
    #endif
    #ifndef __glu_h_
        #include <OpenGL/GLU.h>
    #endif
    #ifndef __GLUT_H__
        #include <GLUT/GLUT.h>
    #endif
#endif

#endif