#include <state_identifiers.hpp>
#include <resource_identifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

class State {
    public:
        typedef std::unique_ptr<State> Ptr;
        struct Context { };

        State(StateStack& stack, Context context);
        virtual ~State();
        virtual void Draw() = 0;
        virtual bool Update(sf::Time dt) = 0;
        virtual bool HandleEvent(const sf::Event& event) = 0;

    protected:
        void RequestStackPush(States::ID stateID);
        void RequestStackPop();
        void RequestStateClear();
        Context GetContext() const;

    private:
        StateStack* stack_;
        Context context_;
};