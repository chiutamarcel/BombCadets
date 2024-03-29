#pragma once
#include "Entity.h"
#include "Character.h"
#include "BreakableBlock.h"
#include "Bomb.h"
#include "Explosion.h"

class Entities {
public:
    static Entities& getInstance() {
        static Entities instance;
        return instance;
    }

    std::vector<Block*>& getWalls() {
		return walls;
    }
    
    std::vector<Character*>& getCharacters() {
        return characters;
    }
    void removeCharacter(Character* character);
    
    std::vector<BreakableBlock*>& getBreakableBlocks() {
        return breakableBlocks;
    }
	void removeBreakableBlock(BreakableBlock* block);
    
    std::vector<Bomb*>& getBombs() {
        return bombs;
    }
	void removeBomb(Bomb* bomb);

    std::vector<Explosion*>& getExplosions() {
        return explosions;
    }
	void removeExplosion(Explosion* explosion);
    
private:
    Entities() {}
    ~Entities(){}

    std::vector<Block*> walls;
    std::vector<Character*> characters;
    std::vector<BreakableBlock*> breakableBlocks;
    std::vector<Bomb*> bombs;
	std::vector<Explosion*> explosions;
};