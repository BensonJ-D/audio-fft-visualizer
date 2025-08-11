#include "audio_visualizer.hpp"
#include <iostream>

namespace render {
    void AudioVisualizer::update(const std::vector<float>& audioInput, std::vector<float>* visualizerOutput) {
        visualizerOutput->clear();
        
        for (size_t i = 0; i < audioInput.size(); ++i) {
            float x = (float)i / audioInput.size() * 2.0f - 1.0f;
            float y = audioInput[i];
            visualizerOutput->push_back(x);
            visualizerOutput->push_back(y);
        }
    }
};