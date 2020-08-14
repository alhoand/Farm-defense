
#include "game_field.hpp"

#include <iostream> // for debugging
#include <limits>

#include <SFML/System/Time.hpp>
#include <cassert>


GameField::GameField(sf::RenderWindow& window, sf::Vector2f viewOffset)
	: window_(window),
	viewOffset_(viewOffset), 
	 gameFieldView_(window.getDefaultView()),
	 sceneGraph_(),
	 gameFieldBounds_(0.f, 0.f, // x and y of the game field
	 				gameFieldView_.getSize().x + viewOffset_.x, //world width is a bit bigger than the view's width
					gameFieldView_.getSize().y + viewOffset_.y), // world height is same as view's height
	 spawnPosition_(gameFieldBounds_.left + 100,
	 				 (gameFieldBounds_.top + gameFieldBounds_.height)/3.f),
	commandQueue_(),
	enemySpeed_(50.f),
	firstEnemy_(),
	firstTower_(),
	spawnCountdown_(sf::seconds(2)),
	spawnInterval_(2), //this should maybe be a parameter
	leftToSpawn_(5),
    activeEnemies_(),
	difficultyLevel_(0), //0 is the first level and increases by 1 by each wave
	levelCount_(5), // can be added to parameter list or askef for player, but for now it's just harcoded to be 5
	levelBreakTimer_(sf::seconds(15))
	{ 
		LoadTextures();
		BuildScene();
		gameFieldView_.setCenter(gameFieldBounds_.left + (gameFieldBounds_.width + viewOffset_.x)/2.f, gameFieldBounds_.top + (gameFieldBounds_.height + viewOffset_.y)/2.f);
	}

void GameField::AddTower(Tower::Type type, sf::Vector2f pos)
{
	//std::cout << "Here we are!" << pos.x <<", " << pos.y << std::endl;
	std::unique_ptr<Tower> newTower(new Tower(type, textures_));
	newTower->setPosition(pos);
	newTower->SetMovePermission(true);
	sceneLayers_[Field]->AttachChild(std::move(newTower));

}

void GameField::Update(sf::Time dt) {

	DestroyEntitiesOutsideView();

	//makes towers shoot
	MakeTowersShoot();
	
	// Forwards the commands to self or the scene graph
	while(!commandQueue_.IsEmpty()) {
		Command next = commandQueue_.Pop();
		if (next.category_ == Category::GameField)
		{
			OnCommand(next, dt);
		}
		else 
		{
			sceneGraph_.OnCommand(next, dt);
		}
	}

	HandleCollisions();

	sceneGraph_.RemoveWrecks();
	SpawnEnemies(dt);
	sceneGraph_.Update(dt, commandQueue_);
}

void GameField::LoadTextures() {
	
	textures_.Load(Textures::ID::Fire, "../media/textures/Doge.png");
	textures_.Load(Textures::ID::Leaf, "../media/textures/cat.png");
	textures_.Load(Textures::ID::Grass, "../media/textures/grass.jpg");
	textures_.Load(Textures::ID::FireTower, "../media/textures/tower.png");
	textures_.Load(Textures::ID::FireBullet, "../media/textures/bullet.png");
	textures_.Load(Textures::ID::NoTexture,      "../media/textures/noTexture.png");
	textures_.Load(Textures::ID::DeathAnimation,      "../media/textures/deathAnimation.png");
	textures_.Load(Textures::ID::Leppis,      "../media/textures/leppakerttu.png");
}

void GameField::BuildScene() {
	// Initialize all the scene layers, i.e., the SceneNodes that are rendered together
	for (std::size_t i = 0; i < LayerCount; i++) {
		Category::Type category = (i == Field) ? Category::Scene : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
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
	std::unique_ptr<Enemy> firstEnemy(new BasicEnemy(textures_));
	firstEnemy_ = firstEnemy.get();
	//firstEnemy_->setOrigin(firstEnemy_->GetBoundingRect().width/2, firstEnemy_->GetBoundingRect().height/2);
	firstEnemy_->setPosition(spawnPosition_);
	//firstEnemy_->setScale(0.5f, 0.5f);

	std::cout << "DEBUG: spawn position:" << firstEnemy_->getPosition().x << "," << firstEnemy_->getPosition().y << std::endl;

	firstEnemy_->SetVelocity(enemySpeed_, 0.f);
	std::cout << "DEBUG: initial velocity: " << firstEnemy_->GetVelocity().x << "," << firstEnemy_->GetVelocity().y << std::endl;
 
	sceneLayers_[Field] -> AttachChild(std::move(firstEnemy));

	//Initialize a tower that can be moved with hard-coded bullet
	// TODO: make bullets work
	std::unique_ptr<Tower> firstTower(new Tower(Tower::Type::Fire, textures_));
	firstTower_ = firstTower.get();
	//firstTower->setOrigin(firstTower->GetBoundingRect().width/2, firstTower->GetBoundingRect().height/2);
	firstTower_->setPosition((gameFieldBounds_.left + gameFieldBounds_.width)/2.f, (gameFieldBounds_.top + gameFieldBounds_.height)/2.f);
	sceneLayers_[Field] -> AttachChild(std::move(firstTower));


}

bool MatchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->GetCategory();
	unsigned int category2 = colliders.second->GetCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		std::cout << "matching category found" << std::endl;
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::cout << "matching category found" << std::endl;
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
		//std::cout << pair.first->GetCategory() << "," << pair.second->GetCategory() << std::endl;
		if (MatchesCategories(pair, Category::Enemy, Category::Bullet))
		{
			std::cout << "Collision happened!!!" << std::endl;
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
std::pair<SceneNode*, bool> GameField::GetActiveNode() const {
	//assert(Tower::ActiveTower() != nullptr); 
	//std::cout << "Active returned" << std::endl;
	if(Tower::ActiveTower())
	{
		//std::cout << "Active tower hp: " << Tower::ActiveTower()->GetHitpoints() << std::endl;
		return { Tower::ActiveTower(), false };
	}else 
	{
		if (Tower::TowerCount() > 0)
		{
			return { Tower::ActiveTower(), false };
		}else
		{
			return { Tower::ActiveTower(), true };
		}
	}


	
}

void GameField::OnCommand(Command command, sf::Time dt) 
{
	command.gameFieldAction_(*this, dt);
}

//Spawns only one type of enemies and spawnInterval is constant
void GameField::SpawnEnemies(sf::Time dt) {

	if (spawnCountdown_ <= sf::Time::Zero && leftToSpawn_ > 0) //TODO leftToSpawn someway better
    {
        spawnCountdown_ += sf::seconds(spawnInterval_);
		//alternative way and probably better in actual game, change spawnInterval to spawnRate to make spawnrate <= 1 sec
		//spawnCountdown_ += sf::seconds(1.f / (spawnRate_+1));

		if (leftToSpawn_-- % 2)
		{
 			std::unique_ptr<TestEnemy> newEnemy(new TestEnemy(textures_, difficultyLevel_));
			//newEnemy->setOrigin(newEnemy->GetBoundingRect().width/2, newEnemy->GetBoundingRect().height/2);
			newEnemy->setPosition(spawnPosition_);
			//newEnemy->setScale(2.f, 2.f);
			newEnemy->SetVelocity(enemySpeed_, 0.f);
			sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
		} else
		{
			std::unique_ptr<Enemy> newEnemy(new BasicEnemy(textures_, difficultyLevel_));
			//newEnemy->setOrigin(newEnemy->GetBoundingRect().width/2, newEnemy->GetBoundingRect().height/2);
			newEnemy->setPosition(spawnPosition_);
			//newEnemy->setScale(0.5f, 0.5f);
			newEnemy->SetVelocity(enemySpeed_, 0.f); //this need to be tought again if we have multiple paths
			sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
		}
    }
    else if (leftToSpawn_ > 0)
    {
        spawnCountdown_ -= dt;
    }
	else if (difficultyLevel_ < levelCount_ )
	{
		if (levelBreakTimer_ <= sf::Time::Zero)
		{
			difficultyLevel_++;
			leftToSpawn_ = 5;
			levelBreakTimer_ = sf::seconds(10); // should this timer max value be parameter also?
		} else
		{
			levelBreakTimer_ -= dt;
		}
	}

}


void GameField::Draw() {
	window_.setView(gameFieldView_);
	window_.draw(sceneGraph_);

}

CommandQueue& GameField::GetCommandQueue() {
	return commandQueue_;
}

void GameField::DestroyEntitiesOutsideView()
{
	Command command;
	command.category_ = Category::Bullet | Category::Enemy;
	command.action_ = DerivedAction<Entity>([this] (Entity& e, sf::Time)
	{
		if (!GetGamefieldBounds().intersects(e.GetBoundingRect()))
		{
			std::cout << "destroying enemy or bullet outside gamefield" << std::endl;
			e.Destroy();
		}	
	});

	commandQueue_.Push(command);
}

sf::FloatRect GameField::GetViewBounds() const
{
	return sf::FloatRect(gameFieldView_.getCenter() - gameFieldView_.getSize() / 2.f, gameFieldView_.getSize());
}

sf::FloatRect GameField::GetGamefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = GetViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

void GameField::MakeTowersShoot()
{
	// Setup command that stores all active enemies to activeEnemies_
	Command enemyCollector;
	enemyCollector.category_ = Category::Enemy;
	enemyCollector.action_ = DerivedAction<Enemy>([this] (Enemy& enemy, sf::Time)
	{
		if (!enemy.IsDestroyed())
			activeEnemies_.push_back(&enemy);
	});

	Command shootBullets;
	shootBullets.category_ = Category::Tower; 
	shootBullets.action_ = DerivedAction<Tower>([this] (Tower& tower, sf::Time)
	{
		// Ignore towers that can't shoot right now
		if (!tower.CanShoot())
			return;

		float minDistance = std::numeric_limits<float>::max();
		Enemy* closestEnemy = nullptr;

		// Find closest enemy
		for(Enemy* enemy : activeEnemies_)
		{
			float enemyDistance = Distance(tower, *enemy);

			if (enemyDistance <= tower.GetRange())
			{
				// Does not work yet, but should be sufficient to slow enemies if tower is certain type
				/* if (tower.GetType() == Tower::IceTower)
				{
					enemy.SlowDown();
					continue;
				} */
				if (enemyDistance < minDistance)
				{
					closestEnemy = enemy;
					minDistance = enemyDistance;
				}
			}
			
		}

		if (closestEnemy)
		{
			sf::Vector2f direction(closestEnemy->GetWorldPosition() - tower.GetWorldPosition());
			std::cout << "shooting direction: " << direction.x << ", " << direction.y << std::endl;
			tower.Shoot(commandQueue_, direction);
		}
			
	});

	// Push commands, reset active enemies
	commandQueue_.Push(enemyCollector);
	commandQueue_.Push(shootBullets);

	activeEnemies_.clear();

}
