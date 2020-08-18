#pragma once

#include "component.hpp"
#include "button.hpp"
#include "node_component.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


namespace GUI
{

class Container : public Component
{
    public:
        typedef std::shared_ptr<Container> Ptr;
            

	public:
							Container();
                            //Set relativeTo=true to set component position in relative to container
        void				Pack(Component::Ptr component, bool relativeTo=false);

        virtual bool		IsSelectable() const;
        virtual void		HandleEvent(const sf::Event& event);

        virtual void        Update(sf::Time dt) override;

        void                SetVelocity(sf::Vector2f velocity);
        void                SetVelocity(float vx, float vy);
        sf::Vector2f        GetVelocity() const;

        //std::shared_ptr<GUI::Button>      GetButton(GUI::ID type);

        //std::shared_ptr<GUI::SceneNodeComponent> GetNodeComponent(GUI::ID type);

        //Component::Ptr GetChild(GUI::ID type);

    private:
        virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            Draw(target,states);
        }
        virtual void		Draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool				HasSelection() const;
        void				Select(std::size_t index);
        void				SelectNext();
        void				SelectPrevious();

        void                UpdateChildren(sf::Time dt);

        virtual void        UpdateCurrent(sf::Time dt);



    private:
        
        std::vector<Component::Ptr>		children_;
        int								selectedChild_;
        sf::Vector2f                    velocity_;
};

}