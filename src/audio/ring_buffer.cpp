#include "ring_buffer.hpp"
#include <algorithm>

namespace audio {
    RingBuffer::RingBuffer(size_t size) : mBuffer(size), mWritePosition(0), mReadPosition(0) {}

    bool RingBuffer::write(const float* data, size_t size) {
        std::lock_guard<std::mutex> lock(mThreadMutex);
        
        if(size > getAvailableWrite()) {
            return false;
        }

        size_t firstWrite = std::min(size, mBuffer.size() - mWritePosition);
        std::copy(data, data + firstWrite, mBuffer.begin() + mWritePosition);

        if (firstWrite < size) {
            std::copy(data + firstWrite, data + size, mBuffer.begin());
        }

        mWritePosition = (mWritePosition + size) % mBuffer.size();
        return true;
    }

    bool RingBuffer::read(float* data, size_t size) {
        std::lock_guard<std::mutex> lock(mThreadMutex);
        
        if (size > getAvailableRead()) {
            return false;
        }

        size_t firstRead = std::min(size, mBuffer.size() - mReadPosition);
        std::copy(mBuffer.begin() + mReadPosition, mBuffer.begin() + mReadPosition + firstRead, data);

        if (firstRead < size) {
            std::copy(mBuffer.begin(), mBuffer.begin() + (size - firstRead), data + firstRead);
        }

        mReadPosition = (mReadPosition + size) % mBuffer.size();
        return true;
    }

    inline size_t RingBuffer::getAvailableRead() const {
        if (mWritePosition >= mReadPosition) {
            return mWritePosition - mReadPosition;
        } else {
            return mBuffer.size() - (mReadPosition - mWritePosition);
        }
    }

    inline size_t RingBuffer::getAvailableWrite() const {
        std::lock_guard<std::mutex> lock(mThreadMutex);
        return mBuffer.size() - getAvailableRead() - 1;
    }
}