add_executable(Renderer main.cpp 
                        VertexArray.cpp
                        VertexBuffer.cpp
                        IndexBuffer.cpp
                        BufferLayout.cpp)

target_link_libraries(Renderer PRIVATE 
                               glad 
                               glfw
                               glm)