#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MMeter.h"

using namespace juce;

class VSTCrackTutorial001AudioProcessorEditor : public AudioProcessorEditor, Timer
{
public:
    VSTCrackTutorial001AudioProcessorEditor (VSTCrackTutorial001AudioProcessor&);
    ~VSTCrackTutorial001AudioProcessorEditor() override;

    void paint (Graphics&) override;
    void resized() override;

private:
    VSTCrackTutorial001AudioProcessor& audioProcessor;
    MMeter MeterL, MeterR;
    ImageComponent ImgBackground;
    void ShowUI();
    void ShowRegWindow();
    void timerCallback() override;

    TextEditor InputName;
    TextEditor InputSerial;
    TextButton ButtonRegister;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VSTCrackTutorial001AudioProcessorEditor)
};
