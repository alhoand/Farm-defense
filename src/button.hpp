#include "component.hpp"
#include "resource_identifiers.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;


	public:
								Button(const FontHolder& fonts, const TextureHolder& textures);
                                Button(const FontHolder& fonts, const TextureHolder& textures, sf::IntRect normalTexturePos, sf::IntRect selectedTexturePos);
                                //Button(const FontHolder& fonts, const TextureHolder& textures, Textures::ID normal, Textures::ID selected, Textures::ID pressed);

        void					SetCallback(Callback callback);
        void					SetText(const std::string& text);
        void					SetToggle(bool flag);
        virtual sf::FloatRect           GetGlobalBounds() override;


        virtual bool			IsSelectable() const override;
        virtual void			Select() override;
        virtual void			Deselect() override;

        virtual void			Activate() override;
        virtual void			Deactivate() override;

        virtual void			HandleEvent(const sf::Event& event) override;


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            Draw(target,states);
            }
        virtual void			Draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Callback				callback_;
        const sf::Texture&		texture_;
        sf::IntRect             normalTextureRect_;
        sf::IntRect             selectedTextureRect_;
        sf::IntRect             pressedTextureRect_;
        sf::Sprite				sprite_;
        sf::Text				text_;
        bool					isToggle_;
};

}