#pragma once
// Represents groups that are likely to receive similar commands
// e.g. towers receive shoot-commands and enemies move-commands
// c. f. Command and CommandQueue classes for more info
namespace Category {
    enum Type {
        None = 0,
        Scene = 1 << 0,
        Tower = 1 << 1,
        Enemy = 1 << 2,   
    };
}

