#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"

const char* VERTEX_SOURCE = R"DELIM(
#version 330 
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Color;

out vec3 f_Color; 

void main(void)
{
  f_Color = a_Color;
  gl_Position = vec4(a_Pos, 1.0);
}
)DELIM";

const char* GEOMETRY_SOURCE = R"DELIM(
#version 330 
layout(triangles) in;
layout(line_strip, max_vertices=32) out;

#define PI 3.14159265358979323846

in vec3 v_Color[]; 
out vec3 f_Color; 

void drawCircle(int index, int count, float radius, vec3 color)
{
  float step = 2 * PI / count;
  f_Color = color; 
  vec4 position = gl_in[index].gl_Position;
  for (int i = 0; i <= count; ++i)
  {
    float x = position.x + radius * cos(step*i);
    float y = position.y + radius * sin(step*i);
    vec4 newPosition = vec4(x, y, 0.0, 1.0);
    gl_Position = position + newPosition;
    EmitVertex(); 
  }
  EndPrimitive();
}

void main(void)
{
  float radius = 0.5;
  drawCircle(0, 5, radius, vec3(1.0, 0.0, 0.0));
  drawCircle(1, 8, radius, vec3(0.0, 0.0, 1.0));
  drawCircle(2, 16, radius, vec3(0.0, 1.0, 0.0));
}
)DELIM";

const char* FRAGMENT_SOURCE = R"DELIM(
#version 330 

in vec3 f_Color; 

out vec4 out_color; 

void main(void)
{
  out_color = vec4(f_Color, 1.0); 
}
)DELIM";

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void check_compile_errors(unsigned int shader, const char* type);

int main(void)
{
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW !" << std::endl;
    return EXIT_FAILURE;
  } 

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Frisen", nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  // Loading GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();  
    return EXIT_FAILURE;
  }    

  std::cout << glGetString(GL_VENDOR) << ": " << glGetString(GL_RENDERER) << '\n';
  std::cout << "GLFW\t " << glfwGetVersionString() << '\n';
  std::cout << "OpenGL\t " << glGetString(GL_VERSION) << '\n';
  std::cout << "GLSL\t " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n\n";

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

  float vertices[24] = {
    /* POSITION */  0.5,  0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15, 
    /* POSITION */  0.5, -0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15, 
    /* POSITION */ -0.5, -0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15, 
    /* POSITION */ -0.5,  0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15 
  };

  unsigned int indices[6] = {
    0, 1, 2, 
    0, 2, 3
  };

  /*************** SHADER ***************/
  const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &VERTEX_SOURCE, nullptr);
  glCompileShader(vertexShader);
  check_compile_errors(vertexShader, "GL_VERTEX_SHADER");

  // const unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
  // glShaderSource(geometryShader, 1, &GEOMETRY_SOURCE, nullptr);
  // glCompileShader(geometryShader);
  // check_compile_errors(geometryShader, "GL_GEOMETRY_SHADER");

  const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &FRAGMENT_SOURCE, nullptr);
  glCompileShader(fragmentShader);
  check_compile_errors(fragmentShader, "GL_FRAGMENT_SHADER");

  const unsigned int program = glCreateProgram();
  glAttachShader(program, vertexShader);
  // glAttachShader(program, geometryShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  /*************** BUFFERS ***************/


  Frisen::VAO vao;
  
  Frisen::VBO vbo(vertices, sizeof(vertices));
  vbo.SetLayout({
    {Frisen::ShaderDataType::FLOAT3}, // a_Pos
    {Frisen::ShaderDataType::FLOAT3}, // a_Color
  });
  
  vao.AddVBO(vbo);

  Frisen::EBO ebo(indices, 6);
  vao.Unbind();
  ebo.Unbind();
  vbo.Unbind();
  // Main LOOP 
  while(!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    vao.Bind(); 

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(program);
  // vao.Destroy();
  // vbo.Destroy();
  // ebo.Destroy();
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}  

void check_compile_errors(unsigned int shader, const char* type)
{
  int success;
  char infoLog[1024];

  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}
