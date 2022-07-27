#include <Engine/Component.h>

#include <Engine/Prefab.h>

class LootDropper : public ComponentParent<LootDropper>{
    public:
    LootDropper(GameObject* obj, Prefab* lootPrefab, float probability);

    void destroy() override;

    private:
    Prefab* prefab;
    float prob;
};