/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WiggleScopeAudioProcessor::WiggleScopeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

WiggleScopeAudioProcessor::~WiggleScopeAudioProcessor()
{
}

//==============================================================================
const juce::String WiggleScopeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WiggleScopeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WiggleScopeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WiggleScopeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WiggleScopeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WiggleScopeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WiggleScopeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WiggleScopeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WiggleScopeAudioProcessor::getProgramName (int index)
{
    return {};
}

void WiggleScopeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WiggleScopeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    latestBuffer.setSize(getMainBusNumInputChannels(), ((latestBufferSize > samplesPerBlock)? latestBufferSize : samplesPerBlock));
}

void WiggleScopeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WiggleScopeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    return true;
}
#endif

void WiggleScopeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int channel = 0; channel < 1; ++channel)
    {
        auto* input  = buffer.getReadPointer(channel);
        auto* latestBufferOut = latestBuffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            latestBufferOut[currentLatestIndex + i] = input[i];
        }
    }
    currentLatestIndex += buffer.getNumSamples();
    currentLatestIndex %= latestBufferSize;
}

//==============================================================================
bool WiggleScopeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WiggleScopeAudioProcessor::createEditor()
{
    return new WiggleScopeAudioProcessorEditor (*this);
}

//==============================================================================
void WiggleScopeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WiggleScopeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WiggleScopeAudioProcessor();
}
