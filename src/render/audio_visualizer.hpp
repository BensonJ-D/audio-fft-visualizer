#include "core/globals.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace render {
    class AudioVisualizer {
    public:        
        static void update(const std::vector<float>& audioInput, std::vector<float>* visualizerOutput);
    };
}