#include "component.hpp"
#include "resource_identifiers.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;
            

	public:
							Label(const std::string& text, const FontHolder& fonts);

        virtual bool		IsSelectable() const;
		void				SetText(const std::string& text);
        virtual sf::FloatRect       GetGlobalBounds() override;

        virtual void		HandleEvent(const sf::Event& event);


    private:
        void				Draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			text_;
};

}