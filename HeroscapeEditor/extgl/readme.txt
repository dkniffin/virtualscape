extgl Copyright (c) 2001-2002 Lev Povalahev (levp@gmx.net)

--------------------------------------------------
How to setup your project to use extgl
--------------------------------------------------

Add extgl.h and extgl.c to you project

In your program replace

#include <GL/gl.h>

with

#include <extgl.h>

--important-- extgl.h must be included before glu.h/gl.h

Then, after initializing OpenGL rendering context, call extgl_Initialize(). If the functions returned 0 everything is OK and you can use the available extensions and core OpenGL 1.2, 1.3 and 1.4 functions (of course only if the driver supports that).

--------------------------------------------------
Querying extensions
--------------------------------------------------

To find out if a particular extension or OpenGL 1.2/1.3/1.4 is supported you can use the structure

extgl_Extensions

For example to check if OpenGL 1.3 is supported you can use this piece of code:

if (extgl_Extensions.OpenGL13)
  puts("OpenGL 1.3 is supported");

The same for OpenGL 1.2 and 1.4 (i.e. the names are extgl_Extensions.OpenGL12 and extgl_Extensions.OpenGL14)

To check if an extension is available this can be done:

if (extgl_Extensions.ARB_vertex_program)
  puts("ARB_vertex_program is supported");

or generically

extgl_Extensions.'extension_name_without_the "GL_"'

Additionally, there is a function that will take extension name (char*) as a parameter and check
if extgl supports it or not.

prototype:
int extgl_ExtensionSupported(const char *name)

example:

if (extgl_ExtensionSupported("GL_ARB_multitexture"))
  printf("multitexturing supported\n");

--------------------------------------------------
WGL Extensions:
--------------------------------------------------

To query if a given WGL extension is supported the extgl_Extensions.wgl structure can be used:

extgl_Extensions.wgl.ARB_buffer_region, or generically

extgl_Extensions.wgl.'extension_name_without_the "WGL_"'

--------------------------------------------------
24 February 2003: Addition regarding NV_half_float
--------------------------------------------------

NV_half_float uses a 16 bit floaing point type, which isn't supported natively
I made the datatype (GLhalf defined as unsigned short) and basic conversion functions:

float htof(GLhalf value)
GLhalf ftoh(float value)

Please remember that arithmetic don't work with GLhalf, you'll have to convert them to float first to
do anything with them.