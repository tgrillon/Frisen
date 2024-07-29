#include "VertexBuffer.h"

namespace Frisen 
{
  VBO::VBO(unsigned int size)
  {
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  }

  VBO::VBO(const void* data, unsigned int size)
  {
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  VBO::~VBO()
  {
    glDeleteBuffers(1, &m_Id);
  }

  void VBO::SetData(const void* data, unsigned int size)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

} // namespace Frisen 