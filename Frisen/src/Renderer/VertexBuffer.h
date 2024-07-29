#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

namespace Frisen 
{
  class VBO 
  {
    public:
      VBO()=default;
      VBO(unsigned int size);
      VBO(const void* data, unsigned int size);
      ~VBO();
      // ~VBO()=default;

      void SetData(const void* offset, unsigned int size);

      inline void SetLayout(const BufferLayout& layout) { m_Layout = layout; } 
      inline const BufferLayout& GetLayout() const { return m_Layout; }

      inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_Id); }
      inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
      inline void Destroy() { glDeleteBuffers(1, &m_Id); }

    private: 
      unsigned int m_Id; 
      BufferLayout m_Layout; 
  };
} // namespace Frisen 
