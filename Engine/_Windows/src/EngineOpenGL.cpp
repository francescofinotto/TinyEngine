#include <stdexcept>
#include "EngineOpenGL.h"
#include "glad/glad.h"
namespace Platform::Win
{

    void Initialize()
    {
        if (!gladLoadGL())
            throw std::runtime_error("Cannot initialize Glad");
    }
}