#include "state.hpp"
#include "../container.hpp"
#include <SFML/Graphics.hpp>
#include "../label.hpp"
class SidebarState : public State {
    public:
        SidebarState(StateStack& stateStack, Context context);
        ~SidebarState() {std::cout << "Sidebar deleted" <<std::endl; }
        virtual void Draw();
        virtual bool Update(sf::Time dt);
        virtual bool HandleEvent(const sf::Event& event);
    private:
        void UpdateGUI(sf::Time dt);
        SceneNode* GetActiveNode(GUI::ID type) const;
        sf::Sprite backgroundSprite_;
        sf::RectangleShape backgroundShape_;
        GUI::Label::Ptr titleText_;
        GUI::Label::Ptr descriptionText_;
        sf::Vector2f viewSize_;
        GUI::Container  GUIContainer_;
        GUI::Controller& GUIController_;
};