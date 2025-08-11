#include "audio_capture.hpp"
#include <iostream>

namespace audio {
    AudioCapture::AudioCapture(): mQueue(nullptr), mSampleRate(44100), mFramesPerBuffer(1024), mIsRunning(false) { }

    AudioCapture::~AudioCapture() {
        stop();
        if (mQueue) {
            AudioQueueDispose(mQueue, true);
        }
    }

    bool AudioCapture::initialize(int sampleRate, int framesPerBuffer) {
        mSampleRate = sampleRate;
        mFramesPerBuffer = framesPerBuffer;

        AudioStreamBasicDescription format {
            (Float64)mSampleRate, // mSampleRate will be set later
            kAudioFormatLinearPCM, // mFormatID
            kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked, // mFormatFlags
            sizeof(float), // mBytesPerPacket
            1, // mFramesPerPacket
            sizeof(float), // mBytesPerFrame
            1, // mChannelsPerFrame
            32, // mBitsPerChannel
            0 // mReserved
        };
        
        OSStatus status = AudioQueueNewInput(
            &format,
            audioCallback,
            this,
            nullptr,
            nullptr,
            0,
            &mQueue
        );
        
        if (status != noErr) {
            std::cerr << "Failed to create audio queue: " << status << std::endl;
            return false;
        }
        
        // Create and allocate buffers
        for (int i = 0; i < cNumberBuffers; ++i) {
            status = AudioQueueAllocateBuffer(mQueue, mFramesPerBuffer * sizeof(float), &mBuffers[i]);
            if (status != noErr) {
                std::cerr << "Failed to allocate buffer " << i << ": " << status << std::endl;
                return false;
            }
            status = AudioQueueEnqueueBuffer(mQueue, mBuffers[i], 0, nullptr);
            if (status != noErr) {
                std::cerr << "Failed to enqueue buffer " << i << ": " << status << std::endl;
                return false;
            }
        }
        
        return true;
    }

    bool AudioCapture::start() {
        OSStatus status = AudioQueueStart(mQueue, nullptr);
        if (status == noErr) {
            mIsRunning = true;
            return true;
        }
        std::cerr << "Failed to start audio queue: " << status << std::endl;
        return false;
    }

    bool AudioCapture::stop() {
        if (!mIsRunning) return true;
        
        OSStatus status = AudioQueueStop(mQueue, true);
        if (status == noErr) {
            mIsRunning = false;
            return true;
        }
        std::cerr << "Failed to stop audio queue: " << status << std::endl;
        return false;
    }

    void AudioCapture::audioCallback(
        void* userData,
        AudioQueueRef audioQueue,
        AudioQueueBufferRef buffer,
        const AudioTimeStamp* startTime,
        UInt32 numberPacketDescriptions,
        const AudioStreamPacketDescription* packetDescs)
    {
        AudioCapture* audio = static_cast<AudioCapture*>(userData);
        std::lock_guard<std::mutex> lock(audio->mThreadMutex);
        
        if (audio->mAudioProcCallback) {
            const float* samples = static_cast<const float*>(buffer->mAudioData);
            size_t numFrames = buffer->mAudioDataByteSize / sizeof(float);
            audio->mAudioProcCallback(samples, numFrames);
        }
        
        // Re-enqueue the buffer
        AudioQueueEnqueueBuffer(audioQueue, buffer, 0, nullptr);
    }
}