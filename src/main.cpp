#include <string>
#include <functional>
#include "bakkesmod/plugin/bakkesmodplugin.h"

using namespace std;
using namespace std::placeholders;

class SpawnMiddle : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override;
    void onUnload() override;
    void onEvent(const std::string& eventName, void* params);
};

void SpawnMiddle::onLoad()
{
    cvarManager->registerCvar("spawnmiddle_enabled", "1",
        "Enable or disable forcing spawn", true, true, 0, true, 1);
    cvarManager->registerCvar("spawnmiddle_spawn_index", "3",
        "Spawn index: 0=Center,1=Left,2=Right,3=Goal (middle near net)",
        true, true, 0, true, 3);

    gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.OnCarSpawned",
        bind(&SpawnMiddle::onEvent, this, _1, _2));

    if (cvarManager->getCvar("spawnmiddle_enabled").getBoolValue())
    {
        int idx = cvarManager->getCvar("spawnmiddle_spawn_index").getIntValue();
        cvarManager->executeCommand("sv_freeplay_spawn " + to_string(idx));
    }
}

void SpawnMiddle::onUnload()
{
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.OnCarSpawned");
    cvarManager->executeCommand("sv_freeplay_spawn -1");
}

void SpawnMiddle::onEvent(const std::string& eventName, void* params)
{
    if (!gameWrapper->IsInFreeplay()) return;
    if (!cvarManager->getCvar("spawnmiddle_enabled").getBoolValue()) return;

    int idx = cvarManager->getCvar("spawnmiddle_spawn_index").getIntValue();
    cvarManager->executeCommand("sv_freeplay_spawn " + to_string(idx));
}

BAKKESMOD_PLUGIN(SpawnMiddle, "Spawn in middle (near goal)", "1.0", "YourName")
