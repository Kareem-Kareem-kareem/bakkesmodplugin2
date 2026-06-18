#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <string>
#include <vector>

class TeleportPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override
    {
        // Register a console command called "teleportme"
        cvarManager->registerCommand("teleportme", "Teleports you to a specific spot",
            [this](const std::vector<std::string>&) {
                // Execute the two commands
                cvarManager->executeCommand("player location 0, -4607, 17.01");
                cvarManager->executeCommand("player rotation -100, 16384, 0");
                cvarManager->log("Teleported to (0, -4607, 17.01) with rotation (-100, 16384, 0)");
            });

        cvarManager->log("TeleportPlugin loaded. Type 'teleportme' in console.");
    }

    void onUnload() override
    {
        cvarManager->log("TeleportPlugin unloaded.");
    }
};

// Manual exports – no macro headaches
extern "C" __declspec(dllexport) BakkesMod::Plugin::BakkesModPlugin* CreatePlugin()
{
    return new TeleportPlugin();
}

extern "C" __declspec(dllexport) const char* GetPluginName()
{
    return "TeleportPlugin";
}

extern "C" __declspec(dllexport) unsigned long GetPluginVersion()
{
    return 1UL;
}

extern "C" __declspec(dllexport) const char* GetPluginAuthor()
{
    return "YourName";
}
