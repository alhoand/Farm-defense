
#include "game_field.hpp"
#include <iostream> // for debugging


GameField::GameField(sf::RenderWindow& window, sf::Vector2f viewOffset)
	: window_(window),
	viewOffset_(viewOffset), 
	 gameFieldView_(window.getDefaultView()),
	 
	 gameFieldBounds_(0.f, 0.f, // x and y of the game field
	 				gameFieldView_.getSize().x + viewOffset_.x, //world width is a bit bigger than the view's width
					gameFieldView_.getSize().y + viewOffset_.y), // world height is same as view's height
	 spawnPosition_(gameFieldBounds_.left,
	 				 (gameFieldBounds_.top + gameFieldBounds_.height)/3.f),
	enemySpeed_(50.f),
	firstEnemy_(),
	firstTower_()
	{ 
		LoadTextures();
		BuildScene();
		gameFieldView_.setCenter(gameFieldBounds_.left + (gameFieldBounds_.width + viewOffset_.x)/2.f, gameFieldBounds_.top + (gameFieldBounds_.height + viewOffset_.y)/2.f);
	}


void GameField::Update(sf::Time dt) {
	//std::cout << "updating game field" << std::endl;

	// Forwards the commands to the scene graph
	while(!commandQueue_.IsEmpty()) {
		sceneGraph_.OnCommand(commandQueue_.Pop(), dt);
	}


	sceneGraph_.Update(dt);
}

void GameField::LoadTextures() {
	
	textures_.Load(Textures::ID::Fire, "../media/textures/Doge.png");
	textures_.Load(Textures::ID::Leaf, "../media/textures/cat.png");
	textures_.Load(Textures::ID::Grass, "../media/textures/grass.jpg");
	textures_.Load(Textures::ID::FireTower, "../media/textures/tower.png");
	
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
	firstEnemy_->setPosition(spawnPosition_);
	firstEnemy_->SetVelocity(enemySpeed_, 0.f);
	sceneLayers_[Ground] -> AttachChild(std::move(firstEnemy));

	std::unique_ptr<Enemy> secondEnemy(new Enemy(Enemy::Type::Leaf, textures_, 50, enemySpeed_));
	secondEnemy->setPosition(-300.f, 0.f); // position relative to the first enemy
	firstEnemy_ -> AttachChild(std::move(secondEnemy));

	//Initialize a tower that can be moved
	std::unique_ptr<Tower> firstTower(new Tower(Tower::Type::Fire, textures_, Position(0,0)));
	firstTower_ = firstTower.get();
	firstTower->setOrigin(firstTower->GetBoundingRect().width/2, firstTower->GetBoundingRect().height/2);
	firstTower_->setPosition((gameFieldBounds_.left + gameFieldBounds_.width)/2.f, (gameFieldBounds_.top + gameFieldBounds_.height)/2.f);
	sceneLayers_[Ground] -> AttachChild(std::move(firstTower));


}

void GameField::Draw() {
	window_.setView(gameFieldView_);
	window_.draw(sceneGraph_);

}

CommandQueue& GameField::GetCommandQueue() {
	return commandQueue_;
}

/*void GameField::AddTower(Tower* t){
	towers_.push_back(t);
}*/
