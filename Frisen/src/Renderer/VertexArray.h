#pragma once

#include <vector>

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Frisen 
{
  class VAO
  {
    public:
      VAO();
      ~VAO(); 
      // ~VAO()=default; 

      void AddVBO(const VBO& vbo);
      void SetEBO(const EBO& ebo);

      inline const std::vector<VBO>& GetVBOs() const { return m_VBOs; }
      inline const EBO& GetEBO() const { return m_EBO; }

      inline void Bind() const { glBindVertexArray(m_Id); }
      inline void Unbind() const { glBindVertexArray(0); }
      inline void Destroy() { glDeleteVertexArrays(1, &m_Id); }
  
    private: 
      unsigned int m_Id; 
      unsigned int m_VBOIndex;
      std::vector<VBO> m_VBOs; 
      EBO m_EBO; 
  };
} // namespace Frisen 
