#pragma once

#include "component.hpp"
#include "states/state.hpp"
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
							Container(State::Context context);

        void				Pack(Component::Ptr component);

        virtual bool		IsSelectable() const;
        virtual void		HandleEvent(const sf::Event& event);

        virtual void        Update(sf::Time dt) override;

        void                SetVelocity(sf::Vector2f velocity);
        void                SetVelocity(float vx, float vy);
        sf::Vector2f        GetVelocity() const;

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
        State::Context                  context_;
        sf::Vector2f                    velocity_;
};

}