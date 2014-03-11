#ifndef NVIDIA_PNG_CODE
#define NVIDIA_PNG_CODE

#include <glh/glh_linear.h>
#include <glh/glh_array.h>
#include <shared/data_path.h>

data_path get_png_path();
void set_png_path(const data_path & newpath);
#ifdef WIN32
void set_png_module_handle(unsigned long hM);
void set_png_module_restypename(const char * tname);
#endif

void read_png_rgba(const char * filename, glh::array2<glh::vec4ub> & image);
void read_png_rgb(const char * filename, glh::array2<glh::vec3ub> & image);
void read_png_grey(const char * filename, glh::array2<unsigned char> & image);

#endif
