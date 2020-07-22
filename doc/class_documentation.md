# Class documentation for testing and TODO list

## Enemy class

Enemies move through game field along predefined path and towers try to destroy them. If any enemy reaches to the end of the path, game is lost or player loses one life.

### Functions

**Constructor** `Enemy(hitpoints, speed, path)`
Abstract class constructor takes three parameters: hitpoints, speed and path. Position is initialized as the first position of the path.

Derived class enemies take the path as a constructor parameter, hitpoints and speed are initially same for same type of enemies, so they are defined in each derived class. 

- Do we need more construction parameters?

**Destructor** `~Enemy()`
The path vector needs to be deleted correctly.

**Update** `Update()`
Function to update the state of the enemy. Takes no parameters and returns ***????***. Update function is the *same* for all enemy classes.

Basic (abstract?) update cases:
1. **enemy is alive** (hp > 0) 
    1. and **not at the end of the path**
        => move enemy forward (change position), return something to indicate everything is ok
    2. and **enemy reached goal** (i.e. it is at the end of the path)
        => game lost, return something to indicate that
2. **enemy is dead** (hp <= 0)
    => return something to indicate enemy should be deleted from the game field


*Feature to be added*
Update function should also check if enemy has some long lasting damage (slow down or burning for multiple ticks etc). Some indicator that tells how long the effect is and reduce this indicator's value by one at the end of each update.

- What is the return value of the funtion? *Depends on how game field handles update functions*
    - Boolean to indicate if enemy is still on the game field?
    - e.g. -1 for lost game, 0 for death, 1 for enemy being alive?
- Parameters?
- Two pairs of indicator attributes: slow down (duration, how much) and take damage (duration, how much/tick)
- 
 

### Protected attributes

***General questions***
- What is the return value of each (enemy, tower, bullet) update funtion? Should be same for all classes
- At which point towers shoot enemies? Towers are updated before enemies, so if enemy takes hit, its update function defines if it's dead or alive

