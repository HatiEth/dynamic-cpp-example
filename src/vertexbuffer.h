#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>
#include <vector>

namespace eth {
namespace gl {

/**
 * @brief Creates an OpenGL buffer containing data of std::vector
 * Note: will not unbind generated buffer
 */
template<typename VectorType>
inline GLuint createBufferFromVector(GLenum target, GLenum usage, const std::vector<VectorType>& v)
{
    GLuint glBufferId;
    glGenBuffers(1, &glBufferId); 
    glBindBuffer(target, glBufferId); 
    glBufferData(target, sizeof(VectorType) * v.size(), &v[0], usage); 
    return glBufferId;
}

/**
 * @brief Allocates Buffer with memory for @param count times T
 * Note: will not unbind generated buffer
 */
template<typename T>
inline GLuint allocateBuffer(GLenum target, GLenum usage, uint32_t count) {
    GLuint glBufferId;
    glGenBuffers(1, &glBufferId); 
    glBindBuffer(target, glBufferId); 
    glBufferData(target, sizeof(T) * count, (GLvoid*)0, usage); 
    return glBufferId;
}

} // namespace gl
} // namespace eth


#endif // VERTEXBUFFER_H
