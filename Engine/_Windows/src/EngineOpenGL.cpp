#include <stdexcept>
#include "EngineOpenGL.h"

#include "glad/glad.h"
namespace Platform::Win
{

    void Initialize()
    {
        if (int result = gladLoadGL(); result<=0)
        {
            auto errorCode = glGetError();
            throw std::runtime_error("Cannot initialize Glad");
        }
    }
}