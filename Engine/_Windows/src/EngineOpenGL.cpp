#include <stdexcept>
#include "../include/EngineOpenGL.h"
#include "../include/glad/glad.h"

void Initialize()
{
    if(!gladLoadGL())
        throw std::runtime_error("Cannot initialize Glad");
}