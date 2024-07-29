#pragma once

#include <glad/glad.h>

namespace Frisen 
{
  class EBO
  {
    public:
      EBO()=default; 
      EBO(const void* indices, unsigned int count);
      ~EBO(); 
      // ~EBO()=default; 

      void SetData(const void* indices, unsigned int count);

      inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id); } 
      inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); } 
      inline void Destroy() { glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_Id); } 

      inline unsigned int GetCount() const { return m_Count; }

    private:
      unsigned int m_Id;
      unsigned int m_Count; 
  };
} // namespace Frisen 
