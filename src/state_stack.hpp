#include <state.hpp>
#include <state_identifiers.hpp>
#include <resource_identifiers.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf {
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable {
    public:
        enum Action {
            Push,
            Pop,
            Clear,
        };

        explicit StateStack(State::Context context);

        template <typename T>
        void RegisterState(States::ID stateID);
        void Update(sf::Time dt);
        void Draw();
        void HandleEvent(const sf::Event& event);
        void PushState(States::ID stateID);
        void PopState();
        void ClearStates();
        bool IsEmpty() const;

    private:
        State::Ptr CreateState(States::ID stateID);
        void ApplyPendingChanges();

        struct PendingChange {
            explicit PendingChange(Action action, States::ID stateID = States::None);
            Action action;
            States::ID stateID;
        };

        std::vector<State::Ptr> stack_;
        std::vector<PendingChange> pendingList_;
        State::Context context_;
        std::map<States::ID, std::function<State::Ptr()>> factories_;
};

template <typename T>
void StateStack::RegisterState(States::ID stateID) {
	factories_[stateID] = [this] () {
		return State::Ptr(new T(*this, context_));
	};
}