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

        void					SetCallback(Callback callback);
        void					SetText(const std::string& text);
        void					SetToggle(bool flag);
        virtual sf::FloatRect           GetGlobalBounds() override;


        virtual bool			IsSelectable() const override;
        virtual void			Select();
        virtual void			Deselect();

        virtual void			Activate();
        virtual void			Deactivate();

        virtual void			HandleEvent(const sf::Event& event) override;


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            Draw(target,states);
            }
        virtual void			Draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Callback				callback_;
        const sf::Texture&		normalTexture_;
        const sf::Texture&		selectedTexture_;
        const sf::Texture&		pressedTexture_;
        sf::Sprite				sprite_;
        sf::Text				text_;
        bool					isToggle_;
};

}