#include <string>
#include <functional>
#include <sstream>
#include "bakkesmod/plugin/bakkesmodplugin.h"

class SpawnMiddle : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override;
    void onUnload() override;
    void onEvent(std::string eventName);
};

void SpawnMiddle::onLoad()
{
    cvarManager->registerCvar("spawnmiddle_enabled", "1",
        "Enable or disable forcing spawn", true, true, 0, true, 1);
    cvarManager->registerCvar("spawnmiddle_spawn_index", "3",
        "Spawn index: 0=Center,1=Left,2=Right,3=Goal (middle near net)",
        true, true, 0, true, 3);

    gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.OnCarSpawned",
        std::function<void(std::string)>(
            [this](std::string eventName) { this->onEvent(eventName); }
        )
    );

    if (cvarManager->getCvar("spawnmiddle_enabled").getBoolValue())
    {
        int idx = cvarManager->getCvar("spawnmiddle_spawn_index").getIntValue();
        cvarManager->executeCommand("sv_freeplay_spawn " + std::to_string(idx));
    }
}

void SpawnMiddle::onUnload()
{
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.OnCarSpawned");
    cvarManager->executeCommand("sv_freeplay_spawn -1");
}

void SpawnMiddle::onEvent(std::string eventName)
{
    if (!gameWrapper->IsInFreeplay()) return;
    if (!cvarManager->getCvar("spawnmiddle_enabled").getBoolValue()) return;

    int idx = cvarManager->getCvar("spawnmiddle_spawn_index").getIntValue();
    cvarManager->executeCommand("sv_freeplay_spawn " + std::to_string(idx));
}

// ✅ CORRECT ORDER: class, plugin name (string), version (unsigned long), author (string)
BAKKESMOD_PLUGIN(SpawnMiddle, "Spawn in middle (near goal)", 1UL, "YourName")
