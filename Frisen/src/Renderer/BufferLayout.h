#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

namespace Frisen 
{
  enum class ShaderDataType
  {
    BOOL, INT, INT2, INT3, INT4, UINT, UINT2, UINT3, UINT4, FLOAT, FLOAT2, FLOAT3, FLOAT4, MAT3, MAT4, NONE 
  };

  static int GetShaderDataTypeByteCount(ShaderDataType type)
  {
    switch(type)
    {
      case ShaderDataType::BOOL:   return 1;
      case ShaderDataType::INT:    return 4 * 1;
      case ShaderDataType::INT2:   return 4 * 2;
      case ShaderDataType::INT3:   return 4 * 3;
      case ShaderDataType::INT4:   return 4 * 4;
      case ShaderDataType::UINT:   return 4 * 1;
      case ShaderDataType::UINT2:  return 4 * 2;
      case ShaderDataType::UINT3:  return 4 * 3;
      case ShaderDataType::UINT4:  return 4 * 4;
      case ShaderDataType::FLOAT:  return 4;
      case ShaderDataType::FLOAT2: return 4 * 2;
      case ShaderDataType::FLOAT3: return 4 * 3;
      case ShaderDataType::FLOAT4: return 4 * 4;
      case ShaderDataType::MAT3:   return 4 * 3; // * 3
      case ShaderDataType::MAT4:   return 4 * 4; // * 4
      default: 
        std::cerr << "Unsupported shader data type!" << std::endl; 
        exit(-1);
    }
  }

  static int GetShaderDataTypeComponentCount(ShaderDataType type)
  {
    switch(type)
    {
      case ShaderDataType::BOOL:   return 1;
      case ShaderDataType::INT:    return 1;
      case ShaderDataType::INT2:   return 2;
      case ShaderDataType::INT3:   return 3;
      case ShaderDataType::INT4:   return 4;
      case ShaderDataType::UINT:   return 1;
      case ShaderDataType::UINT2:  return 2;
      case ShaderDataType::UINT3:  return 3;
      case ShaderDataType::UINT4:  return 4;
      case ShaderDataType::FLOAT:  return 1;
      case ShaderDataType::FLOAT2: return 2;
      case ShaderDataType::FLOAT3: return 3;
      case ShaderDataType::FLOAT4: return 4;
      case ShaderDataType::MAT3:   return 3 * 3;
      case ShaderDataType::MAT4:   return 4 * 4;
      default: 
        std::cerr << "Unsupported shader data type!" << std::endl; 
        exit(-1);
    }
  }

  static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type)
  {
    switch(type)
    {
      case ShaderDataType::BOOL:   return GL_BOOL;
      case ShaderDataType::INT:    return GL_INT;
      case ShaderDataType::INT2:   return GL_INT;
      case ShaderDataType::INT3:   return GL_INT;
      case ShaderDataType::INT4:   return GL_INT;
      case ShaderDataType::UINT:   return GL_UNSIGNED_INT;
      case ShaderDataType::UINT2:  return GL_UNSIGNED_INT;
      case ShaderDataType::UINT3:  return GL_UNSIGNED_INT;
      case ShaderDataType::UINT4:  return GL_UNSIGNED_INT;
      case ShaderDataType::FLOAT:  return GL_FLOAT;
      case ShaderDataType::FLOAT2: return GL_FLOAT;
      case ShaderDataType::FLOAT3: return GL_FLOAT;
      case ShaderDataType::FLOAT4: return GL_FLOAT;
      case ShaderDataType::MAT3:   return GL_FLOAT;
      case ShaderDataType::MAT4:   return GL_FLOAT;
      default: 
        std::cerr << "Unsupported shader data type!" << std::endl; 
        exit(-1);
    }
  }

  struct BufferElement 
  {
    ShaderDataType Type; 
    int Size;  
    int Offset; 
    bool Normalized; 

    BufferElement(ShaderDataType type);

  };

  class BufferLayout
  {
    public: 
      BufferLayout()=default;
      BufferLayout(std::initializer_list<BufferElement> elements);

      inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
      inline int GetStride() const { return m_Stride; }

    private: 
      void ComputeStrideAndOffset();
      
    private:
      std::vector<BufferElement> m_Elements; 
      int m_Stride; 
  };
} // namespace Frisen 
