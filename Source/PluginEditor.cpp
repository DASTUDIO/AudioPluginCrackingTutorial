#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

VSTCrackTutorial001AudioProcessorEditor::VSTCrackTutorial001AudioProcessorEditor (VSTCrackTutorial001AudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    if (p.IsRegister) ShowUI(); else ShowRegWindow();
}
void VSTCrackTutorial001AudioProcessorEditor::ShowRegWindow() 
{
    setSize (400, 300);

    InputName.setBounds(180, 100, 150, 20); 
    InputName.setText("your name");
    InputName.setSize(150, 20);
    addAndMakeVisible(InputName);

    InputSerial.setBounds(180, 120, 150, 20); 
    InputSerial.setText("serial number");
    InputSerial.setSize(150, 20);
    addAndMakeVisible(InputSerial);

    ButtonRegister.setBounds(180, 140, 150, 20);
    ButtonRegister.setButtonText("Register");
    ButtonRegister.setSize(150, 20);
    addAndMakeVisible(ButtonRegister);

    ButtonRegister.onClick = [this]() {
        std::string name = InputName.getText().toStdString() + "sn";
        std::string snInput = InputSerial.getText().toStdString();
        auto sn = MD5(CharPointer_UTF8(name.c_str())).toHexString().toStdString();
        int comp = snInput.compare(sn);

        if (comp == 0) 
        {
            InputName.setVisible(false);
            InputSerial.setVisible(false);
            ButtonRegister.setVisible(false);
            audioProcessor.IsRegister = true;
            ShowUI();
            AlertWindow::showMessageBoxAsync(MessageBoxIconType::NoIcon, "Register", "You have successfully registered VSTCrackTutorial001", "OK");
        }
        else 
        {
            AlertWindow::showMessageBoxAsync(MessageBoxIconType::WarningIcon, "Register", "Invalid serial number", "Retry");
        }
    };
}

void VSTCrackTutorial001AudioProcessorEditor::ShowUI() 
{
    setSize(300, 485.4);

    addAndMakeVisible(MeterL);
    addAndMakeVisible(MeterR);
    startTimerHz(15);

    ImgBackground.setImage(ImageCache::getFromMemory(BinaryData::Congratulation_png, BinaryData::Congratulation_pngSize));
    ImgBackground.setImagePlacement(RectanglePlacement(RectanglePlacement::stretchToFit));
    ImgBackground.setBounds(50, 0, 200, 444.198f);
    addAndMakeVisible(ImgBackground);
}

void VSTCrackTutorial001AudioProcessorEditor::timerCallback() 
{
	MeterL.setLevel(juce::Decibels::gainToDecibels(fmax(0, audioProcessor.GainL.getCurrentValue()))); 
	MeterL.repaint();
	MeterR.setLevel(juce::Decibels::gainToDecibels(fmax(0, audioProcessor.GainR.getCurrentValue()))); 
	MeterR.repaint();
}

VSTCrackTutorial001AudioProcessorEditor::~VSTCrackTutorial001AudioProcessorEditor()
{
}

void VSTCrackTutorial001AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
}

void VSTCrackTutorial001AudioProcessorEditor::resized()
{
	MeterL.setBounds(2.5f, getHeight() - 10, getWidth() - 5, 10);
	MeterR.setBounds(2.5f, getHeight() - 10 - 12.5, getWidth() - 5, 10);
}
