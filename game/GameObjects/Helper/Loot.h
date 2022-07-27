#pragma once
#include <Engine/Component.h>
#include <Engine/Prefab.h>

class Loot : public ComponentParent<Loot>{
    public:
    Loot(GameObject* obj, Prefab* bullet);

    void start() override;

    private:

    Prefab* bulletPrefab;
};