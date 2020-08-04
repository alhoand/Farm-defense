#include <state_stack.hpp>
#include <cassert>
template <typename T>
void StateStack::RegisterState(States::ID stateID) {
    factories_[stateID] = [this] () {
        return State::Ptr(new T(*this, context_));
    };
}

void StateStack::Update(sf::Time dt) {
    for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr) {
        if (!(*itr)->Update(dt))
        return;
    }
    ApplyPendingChanges();
}

void StateStack::Draw() {
    for (State::Ptr& state : stack_) {
        state->Draw();
    }
}

void StateStack::HandleEvent(const sf::Event& event) {
    for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr) {
        if (!(*itr)->HandleEvent(event))
        return;
    }
    ApplyPendingChanges();
}

State::Ptr StateStack::CreateState(States::ID stateID) {
    auto found = factories_.find(stateID);
    assert(found != factories_.end());
    return found->second();
}

void StateStack::ApplyPendingChanges() {
    for (PendingChange change : pendingList_) {
        switch (change.action) {
        case Push:
            stack_.push_back(CreateState(change.stateID));
            break;
        case Pop:
            stack_.pop_back();
            break;
        case Clear:
            stack_.clear();
            break;
        }
    }
    pendingList_.clear();
}