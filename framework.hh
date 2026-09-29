#pragma once
#include <vector>

//Abstract class Component, all specialized components must inherit from this class
class Component
{
    protected:
        const char *name;
    public:
        // Initializes the component with the given name
        Component(const char *name);
       
        // gets the name of the component
        const char* getName();
       
        // virtual destructor
        virtual ~Component() = 0; 
};

//Abstract class Entity, all specialized entities must inherit from this class
class Entity
{
    protected:
        // container with all components attached to the entity
        std::vector<Component*> components;
    public:
        // get a component by name
        Component* getComponent(const char *name);
        
        // attachs a component by pointer
        void attach(Component* component);
        
        // virtual destructor
        virtual ~Entity() = 0;
};

//class PositionComponent, a component specialized in storing 2D positions
class PositionComponent : public Component
{
    protected:
        int _x;
        int _y;
    public:
        public:

            // default constructor, receives as parameter the position coordinates
            PositionComponent(int x, int y);
        
            // gets the value of coordinate x
            int getX() const;
        
            // gets the value of coordinate y
            int getY() const;
        
            // updates the position coordinates
            void setPosition(int x, int y);
        
            //overriden destructor
            ~PositionComponent() override;
};

// class VisualComponent, a component specialized in presenting visually text information 
class VisualComponent : public Component
{
    protected:
        char _letter;
    public:
        // default constructor, receives as parameter the letter to draw
        VisualComponent(const char letter);
       
        // method that prints the letter
        void Draw(); 
       
        //overriden destructor
        ~VisualComponent() override;
};