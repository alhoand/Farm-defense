#include "command_queue.hpp"

void CommandQueue::Push(const Command &command) {
    queue_.push(command);
}

Command CommandQueue::Pop() {
    Command cmd = queue_.front();
    queue_.pop();
    return cmd;
}

bool CommandQueue::IsEmpty() const {
    return queue_.empty();
}