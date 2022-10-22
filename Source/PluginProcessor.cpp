#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
VSTCrackTutorial001AudioProcessor::VSTCrackTutorial001AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

VSTCrackTutorial001AudioProcessor::~VSTCrackTutorial001AudioProcessor()
{
}

//==============================================================================
const String VSTCrackTutorial001AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VSTCrackTutorial001AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VSTCrackTutorial001AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VSTCrackTutorial001AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VSTCrackTutorial001AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VSTCrackTutorial001AudioProcessor::getNumPrograms()
{
    return 1;
}

int VSTCrackTutorial001AudioProcessor::getCurrentProgram()
{
    return 0;
}

void VSTCrackTutorial001AudioProcessor::setCurrentProgram (int index)
{
}

const String VSTCrackTutorial001AudioProcessor::getProgramName (int index)
{
    return {};
}

void VSTCrackTutorial001AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VSTCrackTutorial001AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void VSTCrackTutorial001AudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VSTCrackTutorial001AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else

    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VSTCrackTutorial001AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto totalNumSamples = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    GainL.skip(totalNumSamples);
    GainR.skip(totalNumSamples);

    auto LevelL = buffer.getRMSLevel(0, 0, totalNumSamples);
    auto LevelR = buffer.getRMSLevel(1, 0, totalNumSamples);

    if (LevelL < GainL.getCurrentValue())
        GainL.setTargetValue(LevelL);
    else
        GainL.setCurrentAndTargetValue(LevelL);

    if (LevelR < GainR.getCurrentValue())
        GainR.setTargetValue(LevelR);
    else
        GainR.setCurrentAndTargetValue(LevelR);
}

//==============================================================================
bool VSTCrackTutorial001AudioProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* VSTCrackTutorial001AudioProcessor::createEditor()
{
    return new VSTCrackTutorial001AudioProcessorEditor (*this);
}

//==============================================================================
void VSTCrackTutorial001AudioProcessor::getStateInformation (MemoryBlock& destData)
{
 }

void VSTCrackTutorial001AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VSTCrackTutorial001AudioProcessor();
}
