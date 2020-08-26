#pragma once
#include "state.hpp"
#include "../container.hpp"
#include <SFML/Graphics.hpp>
#include "../label.hpp"
#include "../sidebar_world.hpp"
#include "../towers/tower.hpp"


class SidebarState : public State {
    public:
        SidebarState(StateStack& stateStack, Context context);
        ~SidebarState() {std::cout << "Sidebar deleted" <<std::endl; }
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);
    private:
        void UpdateGUI(sf::Time dt);
        void AddTowerButton(Tower::Type type, float relaltiveX, float relativeY, sf::IntRect normalTexture, sf::IntRect selectedTexture);
        //SceneNode* GetActiveNode(GUI::ID type) const;
        sf::Sprite backgroundSprite_;
        sf::RectangleShape backgroundShape_;
        GUI::Label::Ptr titleText_;
        GUI::Label::Ptr descriptionText_;
        GUI::Label::Ptr infoText_;
        sf::Vector2f viewSize_;
        GUI::Container  GUIContainer_;
        GUI::Controller& GUIController_;
        sf::Vector2f towerPosition_;
        GUI::SidebarWorld 
        sidebarWorld_;
        int currentLevel_;
        bool showInfotext_;
        sf::Time elapsedTime_;
        
};