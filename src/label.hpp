#pragma once
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
                            Label(); // Not sure if needed?
							Label(const std::string& text, const FontHolder& fonts);
                            Label(const std::string& text, const FontHolder& fonts, unsigned int fontSize = 16, Fonts::ID fontType = Fonts::ID::Main);

		void				SetText(const std::string& text, bool center=true);
        //void				SetText(const std::string& text);
        void                SetColor(const sf::Color color, bool outline = false);
        virtual bool		IsSelectable() const override;
        void                CenterTextOrigin();

        virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const override 
                            { Draw(target, states); }


        virtual sf::FloatRect       GetGlobalBounds() const override;

        virtual bool		HandleEvent(const sf::Event& event) override;


    private:
        void				Draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			text_;
};

}