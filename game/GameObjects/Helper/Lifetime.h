#pragma once
#include <Engine/Component.h>

class Lifetime : public ComponentParent<Lifetime>{
    public:
    Lifetime(GameObject* obj, float lifetime=2.f);

    void update(float dt) override;

    private:
    float lifetime;
};