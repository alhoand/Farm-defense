#include "../resource_holder.hpp"
#include "../button.hpp"
#include <cmath>
#include "upgrade_tower_state.hpp"
#include "../utility.hpp"
#include <memory>

UpgradeTowerState::UpgradeTowerState(StateStack& stack, Context context) :
    State(stack, context),
    backgroundSprite_(),
    titleText_(),
    descriptionText_(),
    viewSize_(context.window_->getView().getSize().x/4.f, context.window_->getView().getSize().y),
    GUIContainer_(context)
    {
        sf::Font& font = context.fonts_->Get(Fonts::Main);
        titleText_.setFont(font);
        descriptionText_.setFont(font);
        descriptionText_.setCharacterSize(12);
        titleText_.setCharacterSize(16);
        CenterOrigin(titleText_);
        CenterOrigin(descriptionText_);
        titleText_.setPosition(20.f, 30.f);
        descriptionText_.setPosition(20.f, 50.f);

        auto upgradeButton = std::make_shared<GUI::Button>>(*context.fonts_, *context.textures_);
        upgradeButton->setPosition(20.f, 100.f);

        
    }