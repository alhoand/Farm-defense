#include "animation.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


Animation::Animation()
: sprite_()
, frameSize_()
, numFrames_(0)
, currentFrame_(0)
, duration_(sf::Time::Zero)
, elapsedTime_(sf::Time::Zero)
, repeat_(false)
{
}

Animation::Animation(const sf::Texture& texture)
: sprite_(texture)
, frameSize_()
, numFrames_(0)
, currentFrame_(0)
, duration_(sf::Time::Zero)
, elapsedTime_(sf::Time::Zero)
, repeat_(false)
{
}

void Animation::SetTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

const sf::Texture* Animation::GetTexture() const
{
	return sprite_.getTexture();
}

void Animation::SetFrameSize(sf::Vector2i frameSize)
{
	frameSize_ = frameSize;
}

sf::Vector2i Animation::GetFrameSize() const
{
	return frameSize_;
}

void Animation::SetNumFrames(std::size_t numFrames)
{
	numFrames_ = numFrames;
}

std::size_t Animation::GetNumFrames() const
{
	return numFrames_;
}

void Animation::SetDuration(sf::Time duration)
{
	duration_ = duration;
}

sf::Time Animation::GetDuration() const
{
	return duration_;
}

void Animation::SetRepeating(bool flag)
{
	repeat_ = flag;
}

bool Animation::IsRepeating() const
{
	return repeat_;
}

void Animation::Restart()
{
	currentFrame_ = 0;
}

bool Animation::IsFinished() const
{
	return currentFrame_ >= numFrames_;
}

sf::FloatRect Animation::GetLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(GetFrameSize()));
}

sf::FloatRect Animation::GetGlobalBounds() const
{
	return getTransform().transformRect(GetLocalBounds());
}

void Animation::Update(sf::Time dt)
{
	sf::Time timePerFrame = duration_ / static_cast<float>(numFrames_);
	elapsedTime_ += dt;

	sf::Vector2i textureBounds(sprite_.getTexture()->getSize());
	sf::IntRect textureRect = sprite_.getTextureRect();

	if (currentFrame_ == 0)
		textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);
	
	// While we have a frame to process
	while (elapsedTime_ >= timePerFrame && (currentFrame_ <= numFrames_ || repeat_))
	{
		// Move the texture rect left
		textureRect.left += textureRect.width;

		// If we reach the end of the texture
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			// Move it down one line
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		// And progress to next frame
		elapsedTime_ -= timePerFrame;
		if (repeat_)
		{
			currentFrame_ = (currentFrame_ + 1) % numFrames_;

			if (currentFrame_ == 0)
				textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);
		}
		else
		{
			currentFrame_++;
		}
	}

	sprite_.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}