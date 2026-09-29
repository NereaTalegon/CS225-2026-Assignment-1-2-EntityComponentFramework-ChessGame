#include "framework.hh"
#include <cstring>
#include <iostream>

Component::Component(const char* name){
    this->name = name;
}

const char* Component::getName(){
    return this->name;
}

Component::~Component() {

}

// sets the dafult name of the components as 'Position' and assigns the coordinates (x,y)
PositionComponent::PositionComponent(int x, int y):Component("Position")
{
    this->_x = x;
    this->_y = y;
}

int PositionComponent::getX() const
{
    return _x;
}

int PositionComponent::getY() const
{
    return _y;
}

void PositionComponent::setPosition(int x, int y){
    this->_x = x;
    this->_y = y;
}

PositionComponent::~PositionComponent(){

}

// sets the dafult name of the component as 'Visual' and assigns the letter to print
VisualComponent::VisualComponent(const char letter):Component("Visual")
{
    this->_letter = letter;
}

void VisualComponent::Draw()
{
    std::cout << _letter << ' ';
}

VisualComponent::~VisualComponent(){

}

// gets the component by name, returns null if a component is not found
Component* Entity::getComponent(const char* name){
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
    {   
        Component* component = *(it);
        if(strcmp(component->getName(), name) == 0)
            return component;
    }

    printf("No existe un componente con nombre %s!", name);
    return nullptr;
}

void Entity::attach(Component *component)
{
    components.push_back(component);
}

// releases all the moery allocated for the components on the entity
Entity::~Entity(){
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
        delete *(it);        

    components.clear();
}