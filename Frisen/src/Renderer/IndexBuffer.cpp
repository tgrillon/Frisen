#include "IndexBuffer.h"

namespace Frisen 
{
  EBO::EBO(const void* indices, unsigned int count) : m_Count(count)
  {
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
  }

  EBO::~EBO()
  {
    glDeleteBuffers(1, &m_Id);
  }

  void EBO::SetData(const void* indices, unsigned int count)
  {
    m_Count = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
  }
} // namespace Frisen 
