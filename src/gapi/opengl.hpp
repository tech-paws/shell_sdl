#pragma once

#include <vector>
#include <GL/glew.h>
#include "memory.hpp"
#include "shell_config.hpp"
#include "vm_math.hpp"

enum class ShaderType {
    vertex,
    fragment,
};

struct Shader {
    GLuint id;
    const char* name;
};

struct ShaderProgram {
    GLuint id;
    const char* name;
};

struct Texture2D {
    GLuint id = 0;
    u32 width;
    u32 height;
};

struct TextParams {
    u64 text_size;
    Font* font;
    const char* text;
};

static const size_t GAPI_SHADER_FRAGMENT_COLOR_ID = 0;
static const size_t GAPI_SHADER_FRAGMENT_TEXTURE_ID = 1;
static const size_t GAPI_SHADER_VERTEX_TRANSFORM_ID = 2;

static const size_t GAPI_SHADER_LOCATION_TEXTURE_SHADER_MVP_ID = 0;
static const size_t GAPI_SHADER_LOCATION_TEXTURE_SHADER_TEXTURE_ID = 1;
static const size_t GAPI_SHADER_LOCATION_COLOR_SHADER_MVP_ID = 2;
static const size_t GAPI_SHADER_LOCATION_COLOR_SHADER_COLOR_ID = 3;

struct GApi {
    ShellConfig config;
    RegionMemoryBuffer memory;

    Shader shaders[3];
    ShaderProgram shader_programs[2];
    u32 shader_uniform_locations[4];
    GLuint buffers[8];

    Font* debug_font;

    ShaderProgram shader_program_texture;
    ShaderProgram shader_program_color;

    GLuint quad_indices_buffer;
    GLuint quad_vertices_buffer;
    GLuint quad_tex_coords_buffer;
    GLuint quad_vao;

    GLuint centered_quad_indices_buffer;
    GLuint centered_quad_vertices_buffer;
    GLuint centered_quad_tex_coords_buffer;
    GLuint centered_quad_vao;

    GLuint lines_indices_buffer;
    GLuint lines_vertices_buffer;
    GLuint lines_vao;

    std::vector<Vec2f> lines_vertices;
    std::vector<i32> lines_indices;

    size_t mvp_uniform_location_id;
};
