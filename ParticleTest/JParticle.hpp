//
//  JParticle.hpp
//  ParticleTest
//
//  Created by Jackson Lewis on 8/16/16.
//  Copyright © 2016 Jackson Lewis. All rights reserved.
//
// To do list: add multithreading for faster speed; also add other various features (physics)
#ifndef JParticle_hpp
#define JParticle_hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
class JParticle{
private:
    
    sf::Vector2f location;
    
    sf::Vector2f velocity;
    
    sf::Sprite particle;
    
    float lifespan;
    
    float maxlifespan;
    
protected:

public:
    JParticle(sf::Vector2i loc);
    
    sf::Vector2f& getLocation();
    
    sf::Vector2f& getVelocity();
    
    sf::Sprite& getPSprite();
    
    float& getLifespan();
    
    float& getMaxLifespan();
    
    //void setLocation(sf::Vector2f);
    
    //void setVelocity(sf::Vector2f);
    
    void updatePosition();
};

class JParticleController{
    sf::Vector2f particleConstraits;
    sf::Texture particleTexture;
    std::vector<JParticle> particles;
public:
    void setParticleTexture(sf::Texture t);
    void spawnParticles(int amount, sf::Vector2i location);
    std::vector<std::function<void(JParticle&)> > intmods;
    void frameRun(sf::RenderWindow& w);
    void handleCollisions(JParticle&,JParticle&);
    void setParticleConstraints(sf::Vector2f);
};


#endif /* JParticle_hpp */
