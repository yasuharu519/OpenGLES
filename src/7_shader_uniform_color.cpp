#include <memory>
#include <cassert>
#include <vector>
#include <utility>

#include <GLFW/glfw3.h>

#include "shader_helper.hpp"

struct Extension {
  GLuint shader_program;
  GLint attr_pos;
};

static std::shared_ptr<Extension> extension = std::make_shared<Extension>();

void initialize() {}

void render_func() {}

void destroy() {}
