#include "bakkesmod/plugin/bakkesmodplugin.h"

class HelloPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override
    {
        cvarManager->log("HelloPlugin loaded!");
    }
    void onUnload() override
    {
        cvarManager->log("HelloPlugin unloaded.");
    }
};

extern "C" __declspec(dllexport) BakkesMod::Plugin::BakkesModPlugin* CreatePlugin()
{
    return new HelloPlugin();
}

extern "C" __declspec(dllexport) const char* GetPluginName()
{
    return "HelloPlugin";
}

extern "C" __declspec(dllexport) unsigned long GetPluginVersion()
{
    return 1UL;
}

extern "C" __declspec(dllexport) const char* GetPluginAuthor()
{
    return "YourName";
}
