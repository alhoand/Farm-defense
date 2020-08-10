
#include "game_field.hpp"
#include <iostream> // for debugging
#include <SFML/System/Time.hpp>
#include <cassert>


GameField::GameField(sf::RenderWindow& window, sf::Vector2f viewOffset)
	: window_(window),
	viewOffset_(viewOffset), 
	 gameFieldView_(window.getDefaultView()),
	 
	 gameFieldBounds_(0.f, 0.f, // x and y of the game field
	 				gameFieldView_.getSize().x + viewOffset_.x, //world width is a bit bigger than the view's width
					gameFieldView_.getSize().y + viewOffset_.y), // world height is same as view's height
	 spawnPosition_(gameFieldBounds_.left + 100,
	 				 (gameFieldBounds_.top + gameFieldBounds_.height)/3.f),
	commandQueue_(),
	enemySpeed_(50.f),
	firstEnemy_(),
	firstTower_(),
	spawnCountdown_(sf::Time::Zero),
	spawnInterval_(5),
	leftToSpawn_(15)
	{ 
		LoadTextures();
		BuildScene();
		gameFieldView_.setCenter(gameFieldBounds_.left + (gameFieldBounds_.width + viewOffset_.x)/2.f, gameFieldBounds_.top + (gameFieldBounds_.height + viewOffset_.y)/2.f);
	}


void GameField::Update(sf::Time dt) {
	
	// Forwards the commands to the scene graph
	while(!commandQueue_.IsEmpty()) {
		sceneGraph_.OnCommand(commandQueue_.Pop(), dt);
	}

	HandleCollisions();
	sceneGraph_.RemoveWrecks();
	SpawnEnemies(dt);

	sceneGraph_.Update(dt);
}

void GameField::LoadTextures() {
	
	textures_.Load(Textures::ID::Fire, "../media/textures/Doge.png");
	textures_.Load(Textures::ID::Leaf, "../media/textures/cat.png");
	textures_.Load(Textures::ID::Grass, "../media/textures/grass.jpg");
	textures_.Load(Textures::ID::FireTower, "../media/textures/tower.png");
	textures_.Load(Textures::ID::FireBullet, "../media/textures/bullet.png");
	
}

void GameField::BuildScene() {
	// Initialize all the scene layers, i.e., the SceneNodes that are rendered together
	for (std::size_t i = 0; i < LayerCount; i++) {
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers_[i] = layer.get();
		sceneGraph_.AttachChild(std::move(layer));
	}

	//Make the background
	sf::Texture& texture = textures_.Get(Textures::ID::Grass);
	sf::IntRect textureRect(gameFieldBounds_);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(gameFieldBounds_.left, gameFieldBounds_.top);
	sceneLayers_[Background]->AttachChild(std::move(backgroundSprite));


	//Initialize two enemies
	std::unique_ptr<Enemy> firstEnemy(new Enemy(Enemy::Type::Fire, textures_, 50, enemySpeed_));
	firstEnemy_ = firstEnemy.get();
	firstEnemy_->setOrigin(firstEnemy_->GetBoundingRect().width/2, firstEnemy_->GetBoundingRect().height/2);
	firstEnemy_->setPosition(spawnPosition_);
	firstEnemy_->setScale(0.5f, 0.5f);

	std::cout << "DEBUG: spawn position:" << firstEnemy_->getPosition().x << "," << firstEnemy_->getPosition().y << std::endl;

	firstEnemy_->SetVelocity(enemySpeed_, 0.f);
	std::cout << "DEBUG: initial velocity: " << firstEnemy_->GetVelocity().x << "," << firstEnemy_->GetVelocity().y << std::endl;
 
	sceneLayers_[Ground] -> AttachChild(std::move(firstEnemy));
// This is secon enemy is unnecessary at the moment. The wild behaviour of the second enemy may have been caused by
// it being a child of the first enemy.
//	std::unique_ptr<Enemy> secondEnemy(new Enemy(Enemy::Type::Leaf, textures_, 50, enemySpeed_));
//	secondEnemy->setPosition(-20.f, 0.f); // position relative to the first enemy
//	sceneLayers_[Ground] -> AttachChild(std::move(secondEnemy));

	//Initialize a tower that can be moved with hard-coded bullet
	// TODO: make bullets work
	std::unique_ptr<Tower> firstTower(new Tower(Tower::Type::Fire, textures_, 50, 5, Bullet::Type::FireBullet, commandQueue_));
	firstTower_ = firstTower.get();
	firstTower->setOrigin(firstTower->GetBoundingRect().width/2, firstTower->GetBoundingRect().height/2);
	firstTower_->setPosition((gameFieldBounds_.left + gameFieldBounds_.width)/2.f, (gameFieldBounds_.top + gameFieldBounds_.height)/2.f);
	sceneLayers_[Ground] -> AttachChild(std::move(firstTower));


}

bool MatchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->GetCategory();
	unsigned int category2 = colliders.second->GetCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void GameField::HandleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph_.CheckSceneCollision(sceneGraph_, collisionPairs);

	for(SceneNode::Pair pair : collisionPairs)
	{
		if (MatchesCategories(pair, Category::Enemy, Category::Bullet))
		{
			auto& enemy = static_cast<Enemy&>(*pair.first);
			auto& bullet = static_cast<Bullet&>(*pair.second);

			// Apply bullet damage to enemy, destroy bullet
			enemy.Damage(bullet.GetDamage());
			std::cout << "HP now: " << enemy.GetHitpoints() << std::endl;
			bullet.Destroy();

			//std::cout << "Collision occurred on enemy: " << enemy.Get<< std::endl;
		}
	}
}

// Does not handle nullptr so the caller should handle it.
Tower* GameField::GetActiveTower() const {
	//assert(Tower::ActiveTower() != nullptr); 
	return Tower::ActiveTower();
}

//Spawns only one type of enemies and spawnInterval is constant
void GameField::SpawnEnemies(sf::Time dt) {

	if (spawnCountdown_ <= sf::Time::Zero && leftToSpawn_ > 0) //TODO leftToSpawn someway better
    {
        spawnCountdown_ += sf::seconds(spawnInterval_);
		//alternative way and probably better in actual game, change spawnInterval to spawnRate to make spawnrate under 1 sec
		//spawnCountdown_ += sf::seconds(1.f / (spawnRate_+1));
		leftToSpawn_--;
	
		std::unique_ptr<Enemy> newEnemy(new Enemy(Enemy::Type::Fire, textures_, 50, enemySpeed_));
		newEnemy->setOrigin(newEnemy->GetBoundingRect().width/2, newEnemy->GetBoundingRect().height/2);
		newEnemy->setPosition(spawnPosition_);
		newEnemy->setScale(0.5f, 0.5f);
		newEnemy->SetVelocity(enemySpeed_, 0.f);
		sceneLayers_[Ground] -> AttachChild(std::move(newEnemy));
    }
    else if (leftToSpawn_ > 0)
    {
        spawnCountdown_ -= dt;
    }

}


void GameField::Draw() {
	window_.setView(gameFieldView_);
	window_.draw(sceneGraph_);

}

CommandQueue& GameField::GetCommandQueue() {
	return commandQueue_;
}


