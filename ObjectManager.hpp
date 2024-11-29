#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//As both GameObject and CharComponent have each other's objects
//to break circular dependency, forward declaration of GameObject
class GameObject;

//base class charComponent from which all other components inherit
class CharComponent{
    
    public:
        GameObject* gameObject;
        virtual void init(){}
        virtual void update(){}
        virtual void draw(){}
        
        virtual ~CharComponent() {}
};

class GameObject {
private:
    bool active = true;
    std::vector<std::unique_ptr<CharComponent>> components;

public:
    //called on component's update function
    void update() {
        for (auto& c : components) c->update();
    }

    //called on component's draw function
    void draw() {
        for (auto& c : components) c->draw();
    }

    bool isActive() const { return active; }
    void destroy() { active = false; }

    //adds a new component to the object
    //initializes and returns a reference to the component
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->gameObject = this;
        std::unique_ptr<CharComponent> uPtr{c};
        components.emplace_back(std::move(uPtr));

        c->init();
        return *c;
    }

    //to check if an object has a certain component
    template <typename T>
    bool hasComponent() const {
        for (const auto& comp : components) {
            if (dynamic_cast<T*>(comp.get()) != nullptr) {
                return true;
            }
        }
        return false;
    }

    //returns a reference to the object's T component
    template <typename T>
    T& getComponent() const {
        for (const auto& comp : components) {
            T* ptr = dynamic_cast<T*>(comp.get());
            if (ptr != nullptr) {
                return *ptr;
            }
        }
        throw std::runtime_error("Component not found");
    }
};


class ObjectManager {
private:
    //a vector to store all the game objects
    std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
    //calls update on each object
    void update() {
        for (auto& go : gameObjects) go->update();
    }

    //calls draw on each object
    void draw() {
        for (auto& go : gameObjects) go->draw();
    }

    //removing all the game objects which are not active
    void refresh() {
        gameObjects.erase(std::remove_if(std::begin(gameObjects), std::end(gameObjects),
                                         [](const std::unique_ptr<GameObject> &mObject) {
                                             return !mObject->isActive();
                                         }),
                          std::end(gameObjects));
    }

    //adds a new object and returns its reference
    GameObject& addObject() {
        GameObject *go = new GameObject();
        std::unique_ptr<GameObject> uPtr{go};
        gameObjects.emplace_back(std::move(uPtr));
        return *go;
    }
};
