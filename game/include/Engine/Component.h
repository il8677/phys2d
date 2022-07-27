#pragma once

class GameObject;

class Component{
    public:
    virtual ~Component();
    Component(GameObject* gameObject);

    virtual void setup();
    virtual void start();
    virtual void update(float dt);
    virtual void destroy();
    virtual void onClone(Component* clone);

    virtual int getID()=0;
    virtual Component* clone(GameObject* newObj)=0;
    
    template<typename T>
    static int getID(){
        static int componentID = componentCounter++;
        return componentID;
    }

    virtual void setGameObject(GameObject* obj);
    GameObject* getGo();

    protected:
    GameObject* gameObject=0;

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

    virtual int getID() override{
        return Component::getID<Derived>();
    }

    virtual Component* clone(GameObject* newObj) override{
        Component* c = new Derived(*((Derived*)this));
        c->setGameObject(newObj);
        onClone(c);
        return c;
    }
    
    private:
};