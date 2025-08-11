#pragma once
#include <vector>
#include <mutex>

namespace audio {
    class RingBuffer {
    public:
        explicit RingBuffer(size_t size);
        
        bool write(const float* data, size_t size);
        bool read(float* data, size_t size);
        
        size_t getAvailableRead() const;
        size_t getAvailableWrite() const;

    private:
        std::vector<float> mBuffer;
        size_t mWritePosition;
        size_t mReadPosition;
        mutable std::mutex mThreadMutex;
    };
}