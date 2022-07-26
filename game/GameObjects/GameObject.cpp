#include "GameObject.h"
#include "BodyComponent.h"

GameObject& GameObject::createCircle(World& world, uint32_t color, BodyData data, Vec2 pos, float r, Body::BodyType type){
    Body* b = world.createBody(new ShapeCircle(r), data, type);
    b->position = pos;
    GameObject& go = GameObject::addObject(GameObject(std::make_unique<CircleRenderer>(r, color)));
    go.addComponent<BodyComponent>(b);
    return go;
}

GameObject& GameObject::createRect(World& world, uint32_t color, BodyData data, Vec2 pos, float hextx, float hexty, Body::BodyType type){
    Body* b = world.createBody(new ShapePoly(hextx, hexty), data, type);
    b->position = pos;
    ShapePoly* sp = (ShapePoly*)b->shape;

    GameObject& go = GameObject::addObject(GameObject(std::make_unique<PolyRenderer>(sp->points, color)));
    go.addComponent<BodyComponent>(b);

    return go;
}

GameObject::GameObject(std::unique_ptr<Renderer> renderer_) : 
    renderer(std::move(renderer_)){
}

GameObject::GameObject(const GameObject& other){
    renderer = std::unique_ptr<Renderer>(other.renderer->clone());

    for(const std::unique_ptr<Component>& component : other.components){
        components.emplace_back(component->clone(this));
    }
}

GameObject::GameObject(GameObject&& other){
    renderer = std::move(other.renderer);

    for(std::unique_ptr<Component>& component : other.components){
        auto& c = components.emplace_back(std::move(component));
        c->setGameObject(this);
    }
}

GameObject& GameObject::operator=(const GameObject& other){
    renderer = std::unique_ptr<Renderer>(other.renderer->clone());

    components.clear();
    for(const std::unique_ptr<Component>& component : other.components){
        components.emplace_back(component->clone(this));
    }

    return *this;
}

GameObject& GameObject::addObject(GameObject&& go){

    GameObject& obj = objects.emplace_back(std::move(go));
    obj.setup();
    obj.isActive = true;
    return obj;
}

void GameObject::setup(){
    for(int i = 0; i < components.size(); i++){
        components[i]->setup();
    }

    for(int i = 0; i < components.size(); i++){
        components[i]->start();
    }
}

void GameObject::tick(float dt, sf::RenderWindow& window){

    renderer->render({getPosition(), getRotation()}, window);

    for(std::unique_ptr<Component>& component : components){
        component->update(dt);
    }
}

Vec2 GameObject::getPosition(){
    BodyComponent* bc = getComponent<BodyComponent>();
    if(bc){
        return bc->body->position;
    }

    return Vec2(0,0);
}

Vec2 GameObject::getVelocity(){
     BodyComponent* bc = getComponent<BodyComponent>();
    if(bc){
        return bc->body->velocity;
    }

    return Vec2(0,0);
}

float GameObject::getRotation(){
     BodyComponent* bc = getComponent<BodyComponent>();
    if(bc){
        return bc->body->rotation;
    }
    
    return 0;
}

void GameObject::destroy(){
    doDestroy = true;
}

std::list<GameObject> GameObject::objects;