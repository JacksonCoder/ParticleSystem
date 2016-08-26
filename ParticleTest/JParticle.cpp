//
//  JParticle.cpp
//  ParticleTest
//
//  Created by Jackson Lewis on 8/16/16.
//  Copyright © 2016 Jackson Lewis. All rights reserved.
//

#include "JParticle.hpp"
//#define COLLISIONS_ENABLED
JParticle::JParticle(sf::Vector2i loc) : location(loc)
{
    lifespan = 0;
}
sf::Vector2f& JParticle::getLocation()
{
    return location;
}
void JParticle::updatePosition()
{
    location += velocity;
    particle.setPosition(location);
}
sf::Vector2f& JParticle::getVelocity(){
    return velocity;
}
sf::Sprite& JParticle::getPSprite(){
    return particle;
}
float& JParticle::getLifespan(){
    return lifespan;
}
float& JParticle::getMaxLifespan(){
    return maxlifespan;
}

void JParticleController::setParticleTexture(sf::Texture t){
    particleTexture = t;
}
void JParticleController::spawnParticles(int amount, sf::Vector2i location)
{
    //add particle to the particles container
    particles.reserve(amount + particles.size());
    while(amount-- > 0){
        particles.push_back(JParticle(location));//allocate particles
        particles.back().getPSprite().setTexture(particleTexture);
        for(int i =0; i<intmods.size();i++){
        intmods[i](particles.back());
        }
    }
    
}
void JParticleController::setParticleConstraints(sf::Vector2f v){
    particleConstraits = v;
}
void JParticleController::handleCollisions(JParticle& p1,JParticle & p2){
    if(p1.getLocation().x < p2.getLocation().x && p1.getLocation().y < p2.getLocation().y && p2.getLocation().x < (p1.getLocation() + particleConstraits).x && p2.getLocation().y < (p1.getLocation() + particleConstraits).y){
        //std::cout<<"collided!";
        p2.getVelocity().x = p2.getVelocity().x * -1;
        p2.getVelocity().y = p2.getVelocity().y * -1;
    }
}
void JParticleController::frameRun(sf::RenderWindow& w){
#ifdef COLLISIONS_ENABLED
    for(int i = 0; i < particles.size();i++){
        for(int a = 0; a < particles.size();a++){
        if(a!=i)
        handleCollisions(particles[i],particles[a]);
        }
    }
#endif
    for(int i = 0; i < particles.size();i++){
        particles[i].updatePosition(); //change position
        w.draw(particles[i].getPSprite()); //finally draw them!
        if(particles[i].getLifespan() > 1500){ particles.erase(particles.begin() + i);}//std::cout<<particles.size()<<std::endl;}
        particles[i].getLifespan()++;
    }
    
}
