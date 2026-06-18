#include <string>
#include <vector>
#include "bakkesmod/plugin/bakkesmodplugin.h"

class SimpleGreeter : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override
    {
        cvarManager->registerCvar("greeter_message", "Hello from BakkesMod!",
            "The message printed by the 'greet' command");

        cvarManager->registerCommand("greet", "Prints the greeting message",
            [this](const std::vector<std::string>& args) {
                std::string msg = cvarManager->getCvar("greeter_message").getStringValue();
                cvarManager->log("GREETER: " + msg);
            });

        cvarManager->log("SimpleGreeter loaded. Type 'greet' to test.");
    }

    void onUnload() override
    {
        cvarManager->log("SimpleGreeter unloaded.");
    }
};

// Manual exports – no macro, no order issues
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
