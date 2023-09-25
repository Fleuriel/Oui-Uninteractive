#include <ParticleSystem.h>
#include <Physics.h>

extern std::list<OpenGLObject> objects;

extern ParticleSystem particleSystem;

Particle::Particle(){
    object = OpenGLObject({ 1,1,1 });
    velocity = Vector2D(1, 1);
    lifespan = 1;
    object.particlechecker = true;
    particleSystem.particles.emplace_back(*this);
}

void Particle::update() {
    //std::cout << "VX : " << velocity.x << std::endl;
    //std::cout << "VY : " << velocity.y << std::endl;
    //std::cout << "XB : " << object.position.x << std::endl;
    //std::cout << "YB : " << object.position.y << std::endl;
    //object.position += glm::vec2{ 5, 5 };
    object.position.y -= 0.001;
    
    std::cout << "XA : " << object.position.x << std::endl;
    std::cout << "YA : " << object.position.y << std::endl;
}

void ParticleSystem::update() {
    for (Particle particle : particles)
        particle.update();
}