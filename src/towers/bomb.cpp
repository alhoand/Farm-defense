#include "bomb.hpp"

Bomb::Bomb(const TextureHolder& textures) 
    : Bullet(Bullet::Type::Bomb, textures, 150, 10), 
      distance_(150), 
      range_(100), 
      travelledDistance_(0),
      canDetonate_(false),
      hasDetonated_(false),
      hitAnimation_(textures.Get(Textures::ID::Explosion))
        {
          //hitAnimation_.SetTexture((textures.Get(Textures::ID::Explosion)));
          hitAnimation_.SetFrameSize(sf::Vector2i(256, 256));
	      hitAnimation_.SetNumFrames(16);
	      hitAnimation_.SetDuration(sf::seconds(0.5));
        }

// Getter for bomb's range
int Bomb::GetRange() {
    return range_;
}

// Tells (i.e. for game field) if bomb can detonate of not
bool Bomb::CanDetonate(){
    return canDetonate_;
}

//checker wheather bomb has exploded or not to prevent several explosions from single bomb
bool Bomb::HasDetonated(){
    return hasDetonated_;
}

void Bomb::Detonate(){
    hasDetonated_ = true;
}

bool Bomb::AnimationFinished(){
    return hitAnimation_.IsFinished();
}

void Bomb::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	if(hasDetonated_){
		target.draw(hitAnimation_, states);
    }
    else
        target.draw(sprite_, states);
}   

void Bomb::UpdateCurrent(sf::Time dt, CommandQueue& commands) {
    if (travelledDistance_ >= distance_) {
        canDetonate_ = true;
        hitAnimation_.Update(dt);
        return;
    }
    //if(canDetonate_)
        
    
    double scale = 0.001*travelledDistance_* travelledDistance_ - 0.001*travelledDistance_ * distance_ + 0.5;
    sprite_.setScale(scale,scale);
    sprite_.rotate(5);
    travelledDistance_ += GetSpeed() * dt.asSeconds();
    Entity::UpdateCurrent(dt, commands);
}

