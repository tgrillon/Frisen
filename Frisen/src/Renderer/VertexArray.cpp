#include "VertexArray.h"

namespace Frisen 
{
  VAO::VAO() : m_VBOIndex(0)
  {
    glGenVertexArrays(1, &m_Id);
  }

  VAO::~VAO()
  {
    glDeleteBuffers(1, &m_Id);
  }

  void VAO::AddVBO(const VBO& vbo)
  {
    const auto& layout = vbo.GetLayout();
    glBindVertexArray(m_Id);
    vbo.Bind();
    for(const auto& element : layout.GetElements())
    {
      switch(element.Type)
      {
        case ShaderDataType::BOOL: 
        case ShaderDataType::INT: 
        case ShaderDataType::INT2: 
        case ShaderDataType::INT3: 
        case ShaderDataType::INT4: 
        case ShaderDataType::UINT: 
        case ShaderDataType::UINT2: 
        case ShaderDataType::UINT3: 
        case ShaderDataType::UINT4:
          glEnableVertexAttribArray(m_VBOIndex);
          glVertexAttribIPointer(m_VBOIndex, 
                                 GetShaderDataTypeComponentCount(element.Type), 
                                 ShaderDataTypeToOpenGLDataType(element.Type), 
                                 layout.GetStride(), 
                                 (const void*)element.Offset); 
          m_VBOIndex++;
          break;
        case ShaderDataType::FLOAT: 
        case ShaderDataType::FLOAT2: 
        case ShaderDataType::FLOAT3: 
        case ShaderDataType::FLOAT4:
          glEnableVertexAttribArray(m_VBOIndex);
          glVertexAttribPointer(m_VBOIndex, 
                                 GetShaderDataTypeComponentCount(element.Type), 
                                 ShaderDataTypeToOpenGLDataType(element.Type),
                                 element.Normalized,  
                                 layout.GetStride(), 
                                 (const void*)element.Offset); 
          m_VBOIndex++;
          break;
        case ShaderDataType::MAT3: 
        case ShaderDataType::MAT4:
          unsigned int count = GetShaderDataTypeComponentCount(element.Type);
          for (int i = 0; i < count; ++i)
          {
            glEnableVertexAttribArray(m_VBOIndex);
            glVertexAttribPointer(m_VBOIndex, 
                                  GetShaderDataTypeComponentCount(element.Type), 
                                  ShaderDataTypeToOpenGLDataType(element.Type),
                                  element.Normalized,  
                                  layout.GetStride(), 
                                  (const void*) (element.Offset + sizeof(float) * count * i)); 
            glVertexAttribDivisor(m_VBOIndex, 1);
            m_VBOIndex++;
          }
          break;
      }
    }
    m_VBOs.push_back(vbo);
  }

  void VAO::SetEBO(const EBO& ebo)
  {
    glBindVertexArray(m_Id);
    ebo.Bind();
    
    m_EBO = ebo;
  }
} // namespace Frisen
