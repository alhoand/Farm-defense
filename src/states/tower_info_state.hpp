#include "state.hpp"
#include "../container.hpp"
#include <SFML/Graphics.hpp>
#include "../label.hpp"

class TowerInfoState : public State {
    public:
        TowerInfoState(StateStack& stack, Context context);
        ~TowerInfoState(); //{std::cout << "U deleted" <<std::endl; }
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);

    private:
        void UpdateGUI(sf::Time dt);
        void UpdateTowerInfo();
        //SceneNode* GetActiveNode(GUI::ID type) const;
        sf::Sprite backgroundSprite_;
        sf::RectangleShape backgroundShape_;
        GUI::Label::Ptr titleText_;
        GUI::Label::Ptr descriptionText_;
        GUI::Button::Ptr sellButton_;
        sf::Vector2f viewSize_;
        GUI::Container  GUIContainer_;
        GUI::Controller& GUIController_;
};