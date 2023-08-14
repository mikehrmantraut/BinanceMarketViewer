#include "CryptoDetailWindow.h"

CryptoDetailWindow::CryptoDetailWindow(const juce::String& cryptoName, const juce::String& cryptoPrice)
    : juce::DocumentWindow(cryptoName, juce::Colours::white, juce::DocumentWindow::allButtons)
{
    setContentOwned(new juce::Label("CryptoDetailLabel", "Crypto Name: " + cryptoName + "\nPrice: " + cryptoPrice), true);
    setResizable(true, true);
    centreWithSize(400,400);
    setVisible(true);
}

void CryptoDetailWindow::closeButtonPressed()
{
    delete this;
}