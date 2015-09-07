#ifndef SHADER_HELPER_HPP
#define SHADER_HELPER_HPP

#include <string>

#include <GLFW/glfw3.h>

using gl_string = std::basic_string<GLchar>;

GLuint create_shader(const gl_string& source, GLenum type);
GLuint create_program_from_source(const gl_string& vertex_shader_source,
                                  const gl_string& fragment_shader_source);

#endif // SHADER_HELPER_HPP
