#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


class Animation : public sf::Drawable, public sf::Transformable
{
	public:
								Animation();
		explicit 				Animation(const sf::Texture& texture);

		void 					SetTexture(const sf::Texture& texture);
		const sf::Texture* 		GetTexture() const;

		void 					SetFrameSize(sf::Vector2i frameSize);
		sf::Vector2i		 	GetFrameSize() const;

		void 					SetNumFrames(std::size_t numFrames);
		std::size_t 			GetNumFrames() const;

		void 					SetDuration(sf::Time duration);
		sf::Time 				GetDuration() const;

		void 					SetRepeating(bool flag);
		bool 					IsRepeating() const;

		void 					Restart();
		bool 					IsFinished() const;

		sf::FloatRect 			GetLocalBounds() const;
		sf::FloatRect 			GetGlobalBounds() const;

		void 					Update(sf::Time dt);

        void                    Draw(sf::RenderTarget& target, sf::RenderStates states) {draw(target,states);}


	private:
		

	private:
        void 					draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
        sf::Sprite 				sprite_;
		sf::Vector2i 			frameSize_;
		std::size_t 			numFrames_;
		std::size_t 			currentFrame_;
		sf::Time 				duration_;
		sf::Time 				elapsedTime_;
		bool 					repeat_;
};
