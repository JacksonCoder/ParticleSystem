//
//  JParticle.cpp
//  ParticleTest
//
//  Created by Jackson Lewis on 8/16/16.
//  Copyright © 2016 Jackson Lewis. All rights reserved.
//

#include "Particle.hpp"
//#define COLLISIONS_ENABLED
Particle::Particle(sf::Vector2i loc) : location(loc)
{
    lifespan = 0;
}
sf::Vector2f& Particle::getLocation()
{
    return location;
}
void Particle::updatePosition()
{
    location += velocity;
    particle.setPosition(location);
}
sf::Vector2f& Particle::getVelocity(){
    return velocity;
}
sf::Sprite& Particle::getPSprite(){
    return particle;
}
float& Particle::getLifespan(){
    return lifespan;
}
float& Particle::getMaxLifespan(){
    return maxlifespan;
}

void ParticleController::setParticleTexture(sf::Texture t){
    particleTexture = t;
}
void ParticleController::spawnParticles(int amount, sf::Vector2i location)
{
    //add particle to the particles container
    particles.reserve(amount + particles.size());
    while(amount-- > 0){
        particles.push_back(Particle(location));//allocate particles
        particles.back().getPSprite().setTexture(particleTexture);
        for(int i =0; i<intmods.size();i++){
        intmods[i](particles.back());
        }
    }
    
}
void ParticleController::setParticleConstraints(sf::Vector2f v){
    particleConstraits = v;
}
void ParticleController::handleCollisions(Particle& p1,Particle & p2){
    if(p1.getLocation().x < p2.getLocation().x && p1.getLocation().y < p2.getLocation().y && p2.getLocation().x < (p1.getLocation() + particleConstraits).x && p2.getLocation().y < (p1.getLocation() + particleConstraits).y){
        //std::cout<<"collided!";
        p2.getVelocity().x = p2.getVelocity().x * -1;
        p2.getVelocity().y = p2.getVelocity().y * -1;
    }
}
void ParticleController::frameRun(sf::RenderWindow& w){
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
