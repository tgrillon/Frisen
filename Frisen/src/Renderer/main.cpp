#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

const char* VERTEX_SOURCE = R"DELIM(
#version 330 
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Color;

out vec3 v_Color; 

void main(void)
{
  v_Color = a_Color;
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

  float vertices[18] = {
    /* POSITION */ -0.5, -0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15, 
    /* POSITION */ 0.0, 0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15, 
    /* POSITION */ 0.5, -0.5, 0.0, /* COLOR */ 0.86, 0.24, 0.15 
  };

  unsigned int indices[3] = {
    0, 1, 2
  };

  /*************** SHADER ***************/
  const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &VERTEX_SOURCE, nullptr);
  glCompileShader(vertexShader);
  check_compile_errors(vertexShader, "GL_VERTEX_SHADER");

  const unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(geometryShader, 1, &GEOMETRY_SOURCE, nullptr);
  glCompileShader(geometryShader);
  check_compile_errors(geometryShader, "GL_GEOMETRY_SHADER");

  const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &FRAGMENT_SOURCE, nullptr);
  glCompileShader(fragmentShader);
  check_compile_errors(fragmentShader, "GL_FRAGMENT_SHADER");

  const unsigned int program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, geometryShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  /*************** BUFFERS ***************/
  unsigned int vbo, vao, ebo;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

  // a_Pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * 4, (const void*) 0); 

  // a_Color
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * 4, (const void*) (3 * 4)); 

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Main LOOP 
  while(!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const void*)0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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
