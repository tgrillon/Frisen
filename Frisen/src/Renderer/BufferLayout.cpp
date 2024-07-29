#include "BufferLayout.h"

namespace Frisen 
{
  BufferElement::BufferElement(ShaderDataType type) : Type(type)
  {
    Size = GetShaderDataTypeByteCount(type);
  }

  BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements)
  {
    ComputeStrideAndOffset(); 
  }

  void BufferLayout::ComputeStrideAndOffset()
  {
    int offset = 0; 
    m_Stride = 0; 
    for (auto& element : m_Elements)
    {
      element.Offset = offset;
      m_Stride += element.Size; 
      offset += element.Size;
    }
  }
} // namespace Frisen 