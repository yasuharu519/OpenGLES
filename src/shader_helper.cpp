#include <cassert>

#include <iostream>

#include "shader_helper.hpp"

GLuint create_shader(const gl_string& source, GLenum type) {
  auto source_char = source.c_str();
  GLuint id = glCreateShader(type);
  assert(glGetError() == GL_NO_ERROR);
  assert(id != 0);

  glShaderSource(id, 1, &source_char, NULL);
  glCompileShader(id);

  {
    GLint compileSuccess = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE) {
      GLint infoLen = 0;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLen);

      if (infoLen > 1) {
        GLchar *message = (GLchar *)calloc(infoLen, sizeof(GLchar));
        glGetShaderInfoLog(id, infoLen, NULL, message);

        free((void *)message);
      } else {
        // エラー
      }
    }

    assert(compileSuccess == GL_TRUE);
  }

  return id;
}

GLuint create_program_from_source(const gl_string& vertex_shader_source,
                                  const gl_string& fragment_shader_source)
{
  const auto vertex_shader = create_shader(vertex_shader_source, GL_VERTEX_SHADER);
  const auto fragment_shader = create_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

  GLuint shader_program = glCreateProgram();
  assert(glGetError() == GL_NO_ERROR);
  assert(shader_program != 0);

  glAttachShader(shader_program, vertex_shader);
  assert(glGetError() == GL_NO_ERROR);
  glAttachShader(shader_program, fragment_shader);
  assert(glGetError() == GL_NO_ERROR);

  glLinkProgram(shader_program);

  {
    GLint linkSuccess = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &linkSuccess);

    if (linkSuccess == GL_FALSE) {
      GLint infoLen = 0;
      glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &infoLen);

      if (infoLen > 1) {
        GLchar *message = (GLchar *)calloc(infoLen, sizeof(GLchar));
        glGetProgramInfoLog(shader_program, infoLen, NULL, message);
        free((void *)message);
      }
    }

    assert(linkSuccess == GL_TRUE);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}
