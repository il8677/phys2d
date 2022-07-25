#pragma once

class GameObject;

class Component{
    public:
    Component(GameObject& gameObject);

    virtual void setup();
    virtual void start();
    virtual void update(float dt)=0;

    GameObject& gameObject;

    virtual int getID()=0;

    template<typename T>
    static int getID(){
        static int componentID = componentCounter++;
        return componentID;
    }
    
    private:
    static int componentCounter;
};