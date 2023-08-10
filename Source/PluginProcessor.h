/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class PhaseAnalyzerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PhaseAnalyzerAudioProcessor();
    ~PhaseAnalyzerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;
    
    int getNumParameters() override;
    float getParameter(int index) override;
    void setParameter(int index, float newValue) override;
    
    const String getParameterName(int index) override;
    const String getParameterText(int index) override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // My functions
    //==============================================================================
    int gccPHAT(int frame);
    void applyWindow(AudioSampleBuffer& gccData);
    void resetBuffer();
    void correctDelay(AudioSampleBuffer& buffer);
    
    //==============================================================================
    juce::dsp::FFT fft[7]  {{6}, {7}, {8}, {9}, {10}, {11}, {12}};
    juce::dsp::FFT ifft[7] {{6},  {7},  {8},  {9},  {10},  {11},  {12}};
    juce::dsp::Complex<float> L_td[4096], R_td[4096], L_fd[4096], R_fd[4096], S_td[4096], S_fd[4096];
    //==============================================================================
    
    enum Parameters
    {
        kframeSize = 0,
        khopSizeDivisor,
        ksilenceThreshold,
        kwindowType,
        kdelayCorrection,
        ktemperature,
        kNumParmeters
    };
    
    int sampleDelay;
    int frameSize;
    float accuracy;
    int framesAnalyzed;
    bool delayedChannel;
    float pathLength;
    float latency;
    
    float temp;
    double sampleRate;
    double speedOfSound;
    
    int hopSizeDivisor;
    int hopSize;
    int rmsLevel;
    float silenceThreshold;
    int windowType;
    
    int numCalculations;
    int frameSizeIndex;
    
    bool delayCorrection;
    bool resetMeter;
    int wptr, rptr;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaseAnalyzerAudioProcessor)
    AudioSampleBuffer analysisBuffer_, gccBuffer, delayBuffer;
    int analysisBufferLength_, gccBufferLength;
    int samplesAdded;
};
