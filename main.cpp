#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "MyTypes.h"

class World;
class Player;
class Enemy
{
private:
    EntityType type;
    int id;
public:
    float posx;
    float posy;
    float health;
    Enemy(){}
    Enemy(EntityType typ, float hlt, float xpos, float ypos): type(typ),health(hlt),posx(xpos),posy(ypos) {}
    void printInfo() const {
        printf("Enemy [%d] is a Soldier with %f health",id, health);
    }
    virtual void takeDamage(const float d_amount){
        if (health>0){
            health -= d_amount;
            if (health<0){
            health = 0;
            }
        }
        
    }
    bool isDead(){
        if (health==0){return true;}
        return false;
    }
};
class World {
private:
Enemy* the_enemy;
Player* player;
int numEnemies;
const int max_e;

public:
World(const int max_e) : max_e(max_e) {
    the_enemy = new Enemy[max_e];
    numEnemies = 0;
}

~World() {
    delete[] the_enemy;
}

int getNumEnemies() {
    return numEnemies;
}

void addEnemy(Enemy* x) {
    if (numEnemies < max_e) {
        the_enemy[numEnemies] = *x;
        numEnemies++;
    }
}

Enemy* getEnemy(int x) {
    return &the_enemy[x];
}

void setPlayer(Player* p) {
    player = p;
}

Player* getPlayer() {
    return player;
}
};
class Player {
private:
    float health;
public:
    float posx;
    float posy;
Player(int hlt, float xpos, float ypos): health(hlt), posx(xpos), posy(ypos) {}
void update(World* w) {
        for (int i = 0; i < w->getNumEnemies(); i++) {
            Enemy en = *w->getEnemy(i);
            if (!en.isDead()) {
                float x = (en.posx * en.posy) - (posx * posy);
                en.takeDamage(100 / x);
                en.printInfo();
            }
        }
        for (int i = 0; i < w->getNumEnemies(); i++) {
            Enemy en = *w->getEnemy(i);
            if (!en.isDead()) {
                // Continue to the next iteration of the loop
                continue;
            }
            if (i == w->getNumEnemies() - 1) {
                if (en.isDead()) {
                    printf("My work here is done");
                }
            }
        }
    }
};

class Soldier: public Enemy
{
private:
    /* data */
public:
    Soldier (int hlt,float xpos,float ypos) : Enemy(EntityType::Soldier,hlt,xpos,ypos) {}
    virtual void takeDamage(const float d_amount){
        Enemy::takeDamage(d_amount);
        printf("Ouch!");
        if (health<=0){
            health = 0;
            printf("I lose");
        }
    }
};

class Ninja: public Enemy
{
private:
    /* data */
public:
    Ninja (int hlt,float xpos,float ypos) : Enemy(EntityType::Soldier,hlt,xpos,ypos){}
    virtual void takeDamage(const float d_amount){
        Enemy::takeDamage(d_amount);
        printf("Mada Mada!");
        if (health<=0){
            health = 0;
            printf("Watashi wa haiboku shita(I am defeated)");
        }
    }
};

class Pirate: public Enemy
{
private:
    /* data */
public:
    Pirate (int hlt,float xpos,float ypos) : Enemy(EntityType::Soldier,hlt,xpos,ypos){}
    virtual void takeDamage(const float d_amount){
        Enemy::takeDamage(d_amount);
        printf("arrrrr!");
        if (health<=0){
            health = 0;
            printf("arrrrr! I lost");
        }
    }
};



int main(){
    const int maxe = 50;
    World theWorld(maxe);

    for (int i = 0; i < maxe; i++)
    {
        Enemy* pEnemy = nullptr;
        switch (rand()%3)
        {
        case 0:
            pEnemy = new class Soldier(200,rand()%100,rand()%100);
            break;
        case 1:
            pEnemy = new class Ninja(200,rand()%100,rand()%100);
            break;
        case 2:
            pEnemy = new class Pirate(200,rand()%100,rand()%100);
            break;
        }
        theWorld.addEnemy(pEnemy);
    };
    Player player(500,0,0);
    theWorld.setPlayer(&player);
    while (true)
    {
        player.update(&theWorld);
        if (theWorld.getNumEnemies() == 0) {
            printf("You won! The battle is over!");
            break;
        }
    }
    for (int i = 0; i < maxe; i++) {
        delete theWorld.getEnemy(i);
    }
    return 0; 
}