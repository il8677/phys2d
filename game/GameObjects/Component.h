#pragma once

class GameObject;

class Component{
    public:
    virtual ~Component();
    Component(GameObject* gameObject);

    virtual void setup();
    virtual void start();
    virtual void update(float dt)=0;
    virtual void destroy();

    virtual int getID()=0;
    virtual Component* clone(GameObject* newObj) const=0;
    
    template<typename T>
    static int getID(){
        static int componentID = componentCounter++;
        return componentID;
    }

    virtual void setGameObject(GameObject* obj);
    GameObject* getGo();

    protected:
    GameObject* gameObject;

    private:
    static int componentCounter;
};

// A templated version which automatically overrides getID and clone() 
//  polymorphic components should derive from Component and override manually
template<class Derived>
class ComponentParent : public Component{
    public:

    ComponentParent(GameObject* obj) : Component(obj){

    }

    virtual void update(float dt) override =0;


    virtual int getID() override{
        return Component::getID<Derived>();
    }

    virtual Component* clone(GameObject* newObj) const override{
        Component* c = new Derived(*((Derived*)this));
        c->setGameObject(newObj);
        return c;
    }
    
    private:
};