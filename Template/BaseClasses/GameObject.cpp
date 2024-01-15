#include "GameObject.h"

using namespace baseclass;

GameObject::GameObject(std::string name)
{
    this->name = name;
	this->sprite = new sf::Sprite();
    this->sprite->setOrigin(0.0f, 0.0f);
    this->sprite->setPosition(0.0f, 0.0f);
	this->componentList = {};
}

void GameObject::processInput(sf::Event event)
{
    std::vector<Component*> inputComponentList = this->getComponents(ComponentType::INPUT);
    GeneralInput* generalInput;

    for(Component* component : inputComponentList) 
    {
        if(component->GetOwner()->getEnabledStatus()) 
        {
            generalInput = (GeneralInput*)component;
            generalInput->AssignEvent(event);
            generalInput->Perform();
        }
    }
}

void GameObject::update(sf::Time deltaTime)
{
    std::vector<Component*> scriptComponentList = this->getComponents(ComponentType::SCRIPT);
    
    for(Component* component : scriptComponentList) 
    {
        if(component->GetOwner()->getEnabledStatus()) 
        {
            component->SetDeltaTime(deltaTime);
            component->Perform();
        }
    }
}

void GameObject::physicsUpdate(sf::Time deltaTime) 
{
    std::vector<Component*> physicsComponentList = this->getComponents(ComponentType::PHYSICS);
    
    for(Component* component : physicsComponentList) 
    {
        if(component->GetOwner()->getEnabledStatus()) 
        {
            component->SetDeltaTime(deltaTime);
            component->Perform();
        }
    }
}

void GameObject::draw(sf::RenderWindow* window, sf::RenderStates renderStates)
{
    sf::RenderStates transformedRenderStates(renderStates);
    transformedRenderStates.transform = this->sprite->getTransform() * transformedRenderStates.transform;

    std::vector<Component*> rendererComponentList = this->getComponents(ComponentType::RENDERER);
    Renderer* renderer;

    for(Component* component : rendererComponentList) 
    {
        renderer = (Renderer*)component;
        renderer->AssignTargetWindow(window);
        renderer->SetRenderStates(renderStates);
        renderer->Perform();
    }
}

void GameObject::attachComponent(Component* component)
{
    this->componentList.push_back(component);
    component->AttachOwner(this);
}

void GameObject::detachComponent(Component* component)
{
    int index = -1;
    for(int i = 0; i < this->componentList.size() && index == -1; i++) 
    {
        if(this->componentList[i] == component) 
        {
            index = i;
        }
    }

    if(index != -1) 
    {
        this->componentList[index]->DetachOwner();
        this->componentList.erase(this->componentList.begin() + index);
    }
}

Component* GameObject::findComponentByName(std::string name)
{
    for(Component* component : this->componentList) 
    {
        if(component->GetName() == name)
        {
             return component;
        }
    }
    
    std::cout << "[ERROR] : Component [" << name << "] NOT found." << std::endl;
    return NULL;
}

std::vector<Component*> GameObject::getComponents(ComponentType componentType)
{
    std::vector<Component*> found = {};

    for(Component* component : this->componentList) 
    {
        if(component->GetType() == componentType)
        {
            found.push_back(component);
        }
    }

    return found;
}

sf::Vector2f GameObject::getPosition()
{
    sf::Vector2f position2D = this->sprite->getPosition();
    return position2D;
}

void GameObject::setPosition(sf::Vector2f position)
{
    this->sprite->setPosition(position);
}

void GameObject::setPosition(float x, float y)
{
    this->sprite->setPosition(sf::Vector2f(x, y));
}

void GameObject::move(sf::Vector2f displacement)
{
    sf::Vector2f position2D = this->sprite->getPosition();
    position2D += displacement;

    this->setPosition(displacement);
}

std::string GameObject::getName()
{
	return this->name;
}

sf::Sprite* GameObject::getSprite()
{
	return this->sprite;
}

bool GameObject::getEnabledStatus()
{
	return this->isEnabled;
}

void GameObject::setEnabledStatus(bool status)
{
	this->isEnabled = status;
}