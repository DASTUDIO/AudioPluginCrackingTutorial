#ifndef MMeter_h
#define MMeter_h
#endif
#include <JuceHeader.h>

using namespace juce;

class MMeter : public Component
{
public:
    void paint(Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        g.setColour(Colours::white.withBrightness(0.4f));
        g.fillRoundedRectangle(bounds, 5.f);
        g.setColour(Colours::white);

        const auto scaleX = jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getWidth()));
        g.fillRoundedRectangle(bounds.removeFromLeft(scaleX), 5.f);
    }

    void setLevel(const float value) { level = value; }
private:
    float level = -60.f;
};
