#include "bakkesmod/plugin/bakkesmodplugin.h"

class UltraSimple : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override
    {
        cvarManager->log("UltraSimple plugin loaded!");
    }
    void onUnload() override
    {
        cvarManager->log("UltraSimple plugin unloaded.");
    }
};

extern "C" __declspec(dllexport) BakkesMod::Plugin::BakkesModPlugin* CreatePlugin()
{
    return new UltraSimple();
}

extern "C" __declspec(dllexport) const char* GetPluginName()
{
    return "UltraSimple";
}

extern "C" __declspec(dllexport) unsigned long GetPluginVersion()
{
    return 1UL;
}

extern "C" __declspec(dllexport) const char* GetPluginAuthor()
{
    return "YourName";
}
