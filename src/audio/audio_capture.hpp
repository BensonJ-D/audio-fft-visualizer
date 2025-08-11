// audio_capture.hpp
#pragma once
#include <AudioToolbox/AudioToolbox.h>
#include <vector>
#include <functional>
#include <mutex>

namespace audio {
    class AudioCapture {
    public:
        AudioCapture();
        ~AudioCapture();

        bool initialize(int sampleRate = 44100, int framesPerBuffer = 1024);
        bool start();
        bool stop();
        
        using AudioCallback = std::function<void(const float* data, size_t numFrames)>;
        void setCallback(AudioCallback callback) { mAudioProcCallback = callback; }
        
        // Getters
        int getSampleRate() const { return mSampleRate; }
        int getFramesPerBuffer() const { return mFramesPerBuffer; }
        bool isRunning() const { return mIsRunning; }

    private:
        static const int cNumberBuffers = 3;
        AudioQueueRef mQueue;
        AudioQueueBufferRef mBuffers[cNumberBuffers];
        
        int mSampleRate;
        int mFramesPerBuffer;
        bool mIsRunning;
        AudioCallback mAudioProcCallback;
        std::mutex mThreadMutex;

        static void audioCallback(
            void* userData,
            AudioQueueRef queue,
            AudioQueueBufferRef buffer,
            const AudioTimeStamp* startTime,
            UInt32 numPackets,
            const AudioStreamPacketDescription* packetDesc);
    };
}