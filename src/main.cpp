#include <string>
#include "bakkesmod/plugin/bakkesmodplugin.h"

class SimpleGreeter : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override
    {
        // Register a CVar to store a custom greeting message
        cvarManager->registerCvar("greeter_message", "Hello, BakkesMod!",
            "The message to print when you type 'greet'");

        // Register a console command
        cvarManager->registerCommand("greet", "Prints the greeting message",
            [this](const std::vector<std::string>& args) {
                std::string msg = cvarManager->getCvar("greeter_message").getStringValue();
                cvarManager->log("GREETER: " + msg);
            });

        // Log a welcome message when the plugin loads
        cvarManager->log("SimpleGreeter loaded! Type 'greet' to see a message.");
    }

    void onUnload() override
    {
        cvarManager->log("SimpleGreeter unloaded.");
    }
};

// Manual exports (no macro, no version mismatches)
extern "C" __declspec(dllexport) BakkesMod::Plugin::BakkesModPlugin* CreatePlugin()
{
    return new SimpleGreeter();
}

extern "C" __declspec(dllexport) const char* GetPluginName()
{
    return "SimpleGreeter";
}

extern "C" __declspec(dllexport) unsigned long GetPluginVersion()
{
    return 1UL;
}

extern "C" __declspec(dllexport) const char* GetPluginAuthor()
{
    return "YourName";
}
