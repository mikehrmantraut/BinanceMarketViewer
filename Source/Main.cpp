#include <JuceHeader.h>
#include "MainComponent.h"
#include "MyModel.h"
// global static
MyWebSocketSession* g_ws = nullptr;

class BinanceMarketViewerApplication  : public juce::JUCEApplication
{
public:

    BinanceMarketViewerApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
       
        mainWindow = nullptr; // (deletes our window)
        ::g_ws = nullptr;
        delete ::g_ws;
    }

    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {


            if (::g_ws == nullptr)
            {
                ::g_ws = new MyWebSocketSession();
                //ws.addListener(mainCompModel.get());
                ::g_ws->run([](const std::string& message) {});
            }

            auto mainCompModel = std::make_shared<MyModel>();
            MainComponent* mainComp = new MainComponent(mainCompModel);
            mainCompModel->setView(mainComp);
            setUsingNativeTitleBar(true);
            setContentOwned(mainComp, true);
           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};


START_JUCE_APPLICATION (BinanceMarketViewerApplication)
