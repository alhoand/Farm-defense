#include "state_stack.hpp"

template <typename T>
void StateStack::RegisterState(States::ID stateID) {
    factories_[stateID] = [this] () {
        return State::Ptr(new T(*this, context_));
    };
}

 State::Ptr StateStack::CreateState(States::ID stateID) {
     auto found = factories_.find(stateID);
     assert(found != factories_.end());
     return found->second(); // invokes the stored std::function factory 
     // which returns the std::unique_ptr to the State base class
 }

 // From the SFML-game-dev-book:
 //Every polled event is fed to the state stack. 
 //Then, internally, the stack will deliver that event to the active states:
 /*In this for loop, you can verify that we iterate the active stack from the end to the beginning,
  in other words, from the highest state to the lowest.
   And, if any of the states returns false in its handleEvent() method,
    the loop is immediately ended.
    This gives the control to the states that may not want to let input flow to other states than itself!*/

 void StateStack::HandleEvent(const sf::Event& event) {
     for (auto it = stack_.rbegin(); it != stack_.rend(); it++) {
         if (!(*it)->HandleEvent(event)) { // The ()-marks are because of the "->"-expression being evaluated before "*"-expression
             break;
         }
     }
 }
/*
// From the SFML-game-dev-book:
The updating happens under the same guidelines of event handling,
 both the delivery order and the stopping of update propagation to lower states,
  if desired.*/
 void StateStack::Update(sf::Time dt) {
     for (auto it = stack_.rbegin(); it != stack_.rend(); it++) {
         if(!(*it)->Update(dt))
            break;
     }
 }

/*
// From the SFML-game-dev-book:
Drawing is straightforward; the StateStack class will order every active state to render itself.
The first state to be drawn is the lowest and oldest on the stack,
 and only then come the others, in order. 
 This grants that the states are transparent, 
 and you will be able to see the underlying screens. 
 Anyway, if you don't desire to see pixels from the lower states, 
 you can use sf::RectangleShape to draw a colored rectangle over the whole screen, 
 blocking the undesired graphics, as you will see later in this chapte*/

 void StateStack::Draw() {
     for (State::Ptr& state : stack_) {
         state->Draw();
     }
 }

 void StateStack::ApplyPendingChanges() {
     for (PendingChange change : pendingList_) {
         switch (change.action_) {
             case Action::Push:
                stack_.push_back(CreateState(change.stateID_));
                break;
            case Action::Pop:
                stack_.pop_back();
                break;
            case Action::Clear:
                stack_.clear();
                break;
         }
     }
     pendingList_.clear();
 }

