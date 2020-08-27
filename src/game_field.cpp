
#include "game_field.hpp"

#include <iostream> // for debugging
#include <limits>

#include <SFML/System/Time.hpp>
#include <cassert>
#include "data_tables.hpp"
#include "utility.hpp"

namespace
{
    const std::vector<TowerData> towerTable = InitializeTowerData();
}


GameField::GameField(sf::RenderWindow& window, sf::Vector2f viewOffset)
	: window_(window),
	viewOffset_(viewOffset), 
	 gameFieldView_(window.getDefaultView()),
	 textures_(),
	 sceneGraph_(),
	 sceneLayers_(),
	 gameFieldBounds_(0.f, 0.f, // x and y of the game field
	 				gameFieldView_.getSize().x + viewOffset_.x, //world width is a bit bigger than the view's width
					gameFieldView_.getSize().y + viewOffset_.y), // world height is same as view's height
	 spawnPosition_(gameFieldBounds_.left + 10.f,
	 				 (gameFieldBounds_.top + gameFieldBounds_.height)/3.f),
	commandQueue_(),
	spawnCountdown_(sf::seconds(2)),
	spawnInterval_(2), //this should maybe be a parameter
	leftToSpawn_(0),
    activeEnemies_(),
	difficultyLevel_(0), //0 is the first level and increases by 1 by each wave
	levelCount_(5), // can be added to parameter list or askef for player, but for now it's just harcoded to be 5
	newEnemiesReachedEnd_(0),
	roundMoney_(0),
	hasActiveEnemies_(false),
	newLevelStarted_(false)
	{ 
		LoadTextures();
		BuildScene();
		gameFieldView_.setCenter(gameFieldBounds_.left + (gameFieldBounds_.width + viewOffset_.x)/2.f, gameFieldBounds_.top + (gameFieldBounds_.height + viewOffset_.y)/2.f);
		std::cout << "End of game field constructor" << std::endl;
	}


void GameField::Update(sf::Time dt) {
	newEnemiesReachedEnd_ = 0; // new enemies have not reached end at the beginning of an update
	roundMoney_ = 0; // set round score to zero 

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

	sceneGraph_.RemoveDestroyedNodes();
	SpawnEnemies(dt);
	sceneGraph_.Update(dt, commandQueue_);
}

void GameField::LoadTextures() {
	
	textures_.Load(Textures::ID::Fire, "../media/textures/Doge.png");
	textures_.Load(Textures::ID::Leaf, "../media/textures/cat.png");
	textures_.Load(Textures::ID::Grass, "../media/textures/grass.jpg");
	textures_.Load(Textures::ID::Path, "../media/textures/path.png");
	textures_.Load(Textures::ID::BasicTower, "../media/textures/tractor.png");
	textures_.Load(Textures::ID::SuperTower, "../media/textures/harvester.png");
	textures_.Load(Textures::ID::SlowingTower, "../media/textures/tower.png");
	textures_.Load(Textures::ID::BombingTower, "../media/textures/tower.png");
	textures_.Load(Textures::ID::BasicBullet, "../media/textures/bullet.png");
	textures_.Load(Textures::ID::SuperBullet, "../media/textures/bullet.png");
	textures_.Load(Textures::ID::Bomb, "../media/textures/bullet.png");
	textures_.Load(Textures::ID::NoTexture,      "../media/textures/noTexture.png");
	textures_.Load(Textures::ID::DeathAnimation,      "../media/textures/deathAnimation.png");
	textures_.Load(Textures::ID::Leppis,      "../media/textures/leppakerttu.png");
	textures_.Load(Textures::ID::Koppis,      "../media/textures/koppakuoriainen.png");
	textures_.Load(Textures::ID::HamahakkiIso,      "../media/textures/hamahakki.png");
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
	sf::Texture& grass = textures_.Get(Textures::ID::Grass);
	sf::IntRect textureRect(gameFieldBounds_);
	grass.setRepeated(true);

	std::unique_ptr<SpriteNode> grassSprite(new SpriteNode(grass, textureRect));
	grassSprite->setPosition(gameFieldBounds_.left, gameFieldBounds_.top);
	sceneLayers_[Background]->AttachChild(std::move(grassSprite));

	// Make path visible
	BuildPath();
}

bool MatchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->GetCategory();
	unsigned int category2 = colliders.second->GetCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		//std::cout << "matching category found" << std::endl;
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		//std::cout << "matching category found" << std::endl;
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}


void GameField::AddTower(Tower::Type type, sf::Vector2f pos)
{
	std::cout << "Here we are!" << std::endl;

	std::unique_ptr<Tower> newTower;
	switch (type)
	{
	case Tower::Type::Super:
		newTower.reset(new SuperTower(textures_));
		break;
	case Tower::Type::Bombing:
		newTower.reset(new BombingTower(textures_));
		break;
	case Tower::Type::Slowing:
		newTower.reset(new SlowingTower(textures_));
		break;
	default:
		newTower.reset(new BasicTower(textures_));
		break;
	}

	newTower->setPosition(pos);
	newTower->AllowMoving();
	newTower->Move();
	newTower->Activate();
	
	sceneLayers_[Field]->AttachChild(std::move(newTower));
	//Tower::ActiveTower(newTower, commandQueue_);
	std::cout << "Tower pos: " << pos.x <<", " << pos.y << std::endl;
}

void GameField::HandleCollisions()
{
	
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph_.CheckSceneCollision(sceneGraph_, collisionPairs);
	bool towerCollideCalled = false;
	//std::cout << "Hello frmo her " << std::endl;
	for(SceneNode::Pair pair : collisionPairs)
	{
		//std::cout << pair.first->GetCategory() << "," << pair.second->GetCategory() << std::endl;
		if (MatchesCategories(pair, Category::Enemy, Category::Bullet))
		{
			//std::cout << "Collision happened!!!" << std::endl;
			auto& enemy = static_cast<Enemy&>(*pair.first);
			auto& bullet = static_cast<Bullet&>(*pair.second);
			if(bullet.IsDestroyed() || enemy.IsDestroyed())
			{
				continue;
			}
			// Apply bullet damage to enemy, destroy bullet
			enemy.TakeHit(bullet.GetDamage(), bullet.GetCategory());
			if (enemy.IsDestroyed())
			{
				AddRounMoney(enemy.GetMoney());
			}
			std::cout << "HP now: " << enemy.GetHitpoints() << std::endl;
			bullet.Destroy();

		}
		if (MatchesCategories(pair, Category::Tower, Category::Active))
		{
			auto& tower = static_cast<Tower&>(*pair.first);
			auto& activeTower = static_cast<Tower&>(*pair.second);
			//if (tower.IsMoving())
			//{
				tower.Collides(true);
				towerCollideCalled = true;
			//}
			if (activeTower.IsMoving())
			{
				activeTower.Collides(true);
				towerCollideCalled = true;
			}
				
		}
		if (MatchesCategories(pair, Category::Tower, Category::Path))
		{
			//std::cout << "Path recognized" << std::endl;
			auto& activeTower = static_cast<Tower&>(*pair.first);
			//auto& path = pair.second->GetCategory();
			if (activeTower.IsMoving())
			{
				activeTower.Collides(true);
				towerCollideCalled = true;
			}
		}


		
	}
	if (!towerCollideCalled)
		{
			Command command;
			command.category_ = Category::Tower;
			command.action_ = DerivedAction<Tower>([=](Tower& t, sf::Time)
			{
				t.Collides(false);
				//std::cout << "Collide called" << std::endl;
			});
			commandQueue_.Push(command);

		}
}
void GameField::BuildPath()
{
	std::vector<Direction> path = InitializeEnemyPath();

	// Path begins from spawnPosition_ with 25 pixels of offset
	sf::Vector2f c = spawnPosition_;
	c.x -= 25;
	c.y -= 25;

	sf::Texture& p = textures_.Get(Textures::ID::Path);
	std::unique_ptr<SpriteNode> pathSprite(new SpriteNode(p));
	pathSprite->setPosition(c);
	pathSprite->SetCategory(Category::Path);
	sceneLayers_[Background]->AttachChild(std::move(pathSprite));

	for (auto i : path) {
		int dist = 0;
		while (dist < i.distance) {
			dist += 50;
			if (i.angle == 0) {
				c.x += 50;
			} else if (i.angle == +90) {
				c.y += 50;
			} else if (i.angle == -90) {
				c.y -= 50;
			} else {
				c.x -= 50;
			}

			sf::Texture& p = textures_.Get(Textures::ID::Path);
			std::unique_ptr<SpriteNode> pathSprite(new SpriteNode(p));
			pathSprite->setPosition(c);
			pathSprite->SetCategory(Category::Path);
			sceneLayers_[Background]->AttachChild(std::move(pathSprite));
		}
	}
}

void GameField::OnCommand(Command command, sf::Time dt) 
{
	command.gameFieldAction_(*this, dt);
}


void GameField::NextEnemyWave()
{
	difficultyLevel_++;
	std::cout << "trying to start new enemy wave" << std::endl;
	newLevelStarted_ = true;
	if (difficultyLevel_ <= levelCount_)
	{
		std::cout << "Creating new enemy wave!!" << std::endl;
		switch (difficultyLevel_) {
			case 1:
				leftToSpawn_ = 10;
				break;
			case 2:
				leftToSpawn_ = 15;
				break;
			case 3:
				leftToSpawn_ = 20;
				break;
			case 4:
				leftToSpawn_ = 25;
				break;
			case 5:
				leftToSpawn_ = 35;
				break;
			default:
			break;
		}
	}
}

void GameField::NextLevel()
{
	newLevelStarted_ = false;
}


//Spawns only one type of enemies and spawnInterval is constant
void GameField::SpawnEnemies(sf::Time dt) {
	
	if (leftToSpawn_ > 0 && difficultyLevel_ <= levelCount_)//TODO leftToSpawn someway better?
	{
		if (spawnCountdown_ <= sf::Time::Zero) 
    	{
			spawnCountdown_ += sf::seconds(spawnInterval_);
			//alternative way and probably better in actual game, change spawnInterval to spawnRate to make spawnrate <= 1 sec
			//spawnCountdown_ += sf::seconds(1.f / (spawnRate_+1));
			RandomEnemySpawner(difficultyLevel_);
			leftToSpawn_--;

		} else 
		{
			spawnCountdown_ -= dt;
		}
	} 
}

void GameField::RandomEnemySpawner(unsigned int level)
{
	int num = RandomInt(level); //random int that is max level-1

		//this works only for current enemy types, probably cannot implemet for arbitrary count of enemy types
		switch(num)
		{
			case 0: 
			{
				std::unique_ptr<BasicEnemy> newEnemy(new BasicEnemy(textures_, difficultyLevel_));
				newEnemy->setPosition(spawnPosition_);
				newEnemy->SetVelocity(newEnemy->GetSpeed(), 0.f); //this need to be tought again if we have multiple paths
				sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
			}
				break;
			case 1:
			{
				std::unique_ptr<MultiEnemy> newEnemy(new MultiEnemy(textures_, difficultyLevel_));
				newEnemy->setPosition(spawnPosition_);
				newEnemy->SetVelocity(newEnemy->GetSpeed(), 0.f); //this need to be tought again if we have multiple paths
				sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
			}
				break;
			case 2:
			{
				std::unique_ptr<BulkEnemy> newEnemy(new BulkEnemy(textures_, difficultyLevel_));
				newEnemy->setPosition(spawnPosition_);
				newEnemy->SetVelocity(newEnemy->GetSpeed(), 0.f); //this need to be tought again if we have multiple paths
				sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
			}
				break;
			case 3:
			{
				std::unique_ptr<FastEnemy> newEnemy(new FastEnemy(textures_, difficultyLevel_));
				newEnemy->setPosition(spawnPosition_);
				newEnemy->SetVelocity(newEnemy->GetSpeed(), 0.f); //this need to be tought again if we have multiple paths
				sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
			}
				break;
			default:
			{
				std::unique_ptr<BulkEnemy> newEnemy(new BulkEnemy(textures_, difficultyLevel_));
				newEnemy->setPosition(spawnPosition_);
				newEnemy->SetVelocity(newEnemy->GetSpeed(), 0.f); //this need to be tought again if we have multiple paths
				sceneLayers_[Field] -> AttachChild(std::move(newEnemy));
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
/*
void GameField::HandleActiveTower()
{
	Command command;
	command.category_ = Category::ActiveTower;
	command.action_ = DerivedAction<Tower>([this] (Tower& t, sf::Time)
	{

	});
	commandQueue_.Push(command);
}*/

int GameField::NewEnemiesReachedEnd() {
	return newEnemiesReachedEnd_;
}

bool GameField::CanSpawnNewWave()
{
	return (!hasActiveEnemies_ && (leftToSpawn_ <= 0));
}
//can be used to determine when current wave is finished
bool GameField::IsEndOfLevel()
{
	return newLevelStarted_ && !hasActiveEnemies_ && leftToSpawn_ <= 0;
}

bool GameField::IsEndOfGame()
{
	return IsEndOfLevel() && difficultyLevel_ >= levelCount_;
}

int GameField::GetCurrentLevel()
{
	return difficultyLevel_;
}

int GameField::GetAddedMoney()
{
	return roundMoney_;
}

void GameField::AddRounMoney(int money)
{
	roundMoney_ += money;
}

void GameField::DestroyEntitiesOutsideView()
{
	Command bulletCommand;
	bulletCommand.category_ = Category::Bullet;
	bulletCommand.action_ = DerivedAction<Entity>([this] (Entity& e, sf::Time)
	{
		if (!GetGamefieldBounds().intersects(e.GetBoundingRect()))
		{
			std::cout << "destroying bullet outside gamefield" << std::endl;
			e.Destroy();
		}	
	});

	Command enemyCommand;
	enemyCommand.category_ = Category::Enemy;
	enemyCommand.action_ = DerivedAction<Enemy>([this] (Enemy& e, sf::Time)
	{
		if (!GetGamefieldBounds().intersects(e.GetBoundingRect()) && !e.IsDestroyed())
		{
			std::cout << "destroying enemy outside gamefield and also reduce player lives" << std::endl;
			e.Destroy();
			newEnemiesReachedEnd_++; 
		}	
	});

	commandQueue_.Push(bulletCommand);
	commandQueue_.Push(enemyCommand);
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

// Does both: shoots enemies or slows them down depending on tower category
void GameField::MakeTowersShoot()
{
	// Setup command that stores all active enemies to activeEnemies_
	Command enemyCollector;
	enemyCollector.category_ = Category::Enemy;
	enemyCollector.action_ = DerivedAction<Enemy>([this] (Enemy& enemy, sf::Time)
	{
		if (!enemy.IsDestroyed())
		{
			activeEnemies_.push_back(&enemy);
		}
		if (!enemy.IsMarkedForRemoval())
		{
			hasActiveEnemies_ = true;
		}

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
				// Does not work yet, but should be sufficient to slow enemies if tower is category SlowingTower
				if (tower.GetCategory() == Category::SlowingTower) {
					enemy->SlowDown(); //duration?
					continue;
				}
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
			//std::cout << "shooting direction: " << direction.x << ", " << direction.y << std::endl;
			tower.Shoot(commandQueue_, direction);
		}
			
	});

	Command detonateCommand;
	detonateCommand.category_ = Category::Bomb;
    detonateCommand.action_ = DerivedAction<Bomb>([this] (Bomb& bomb, sf::Time) 
	{
		//std::cout << "Here we aree at the bomb" << std::endl;
		if (!bomb.CanDetonate())
		{
			return;
		}
		for(Enemy* enemy : activeEnemies_)
		{
			if (Distance(bomb, *enemy) <= bomb.GetRange() && !enemy->IsDestroyed()) {
                enemy->TakeHit(bomb.GetDamage(), bomb.GetCategory());
            }
			if (enemy->IsDestroyed())
			{
				AddRounMoney(enemy->GetMoney());
			}
		}
		bomb.Destroy();
	});

	Command towerCommand;
	towerCommand.category_ = Category::Tower;
	towerCommand.action_ = DerivedAction<Tower>([this](Tower& tower, sf::Time)
	{
		std::cout << "Check" << std::endl;
		std::cout << "Sold:  " << tower.IsSold() << std::endl;
		if (tower.IsDestroyed()) // If the tower is not sold yet
		{
			AddRounMoney(towerTable[tower.GetType()].price);
			std::cout << "Money added" << std::endl;
			//tower.Sell();
		}
	});


	// Push commands, reset active enemies
	commandQueue_.Push(enemyCollector);
	commandQueue_.Push(shootBullets);
	commandQueue_.Push(detonateCommand);
	commandQueue_.Push(towerCommand);

	if (activeEnemies_.empty())
	{
		hasActiveEnemies_ = false;
	}
	activeEnemies_.clear();

}


