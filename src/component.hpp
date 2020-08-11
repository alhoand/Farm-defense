#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace GUI
{
class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
    public:
        typedef std::shared_ptr<Component> Ptr;


	public:
							Component();
        virtual				~Component();

        virtual bool		IsSelectable() const = 0;
		bool				IsSelected() const;
        virtual void		Select();
        virtual void		Deselect();

        virtual bool		IsActive() const;
        virtual void		Activate();
        virtual void		Deactivate();
                            // Sets the parent of the component
        void                ChildOf(Component* parent);

        virtual void        Update(sf::Time dt);
        sf::Transform       GetWorldTransform() const;

        sf::Vector2f        GetWorldPosition() const;

        virtual sf::FloatRect GetGlobalBounds(){return sf::FloatRect();}
        virtual void		  HandleEvent(const sf::Event& event) = 0;


    private:
        bool				isSelected_;
        bool				isActive_;
        Component*          parent_;
};

}
