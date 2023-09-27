#include <ParticleSystem.h>
#include <Physics.h>
#include <OpenGLObjects.h>



extern ParticleSystem particleSystem;

Particle::Particle(){
    object = OpenGLObject({ 1,1,1 });
    velocity = Vector2D(1, 1);
	alpha = 1;
    lifespan = 1;
    object.interactable = false;
    particleSystem.particles.emplace_back(*this);
}

void Particle::init(int userInput_x, int userInput_y, float userInput_sizeX,
					float userInput_sizeY, float userInput_angleDisplacement,
					float userInput_angleSpeed) {
    object.InitObjects(userInput_x, userInput_y, userInput_sizeX, userInput_sizeY, userInput_angleDisplacement, userInput_angleSpeed);
}

void Particle::update() {
    //std::cout << "VX : " << velocity.x << std::endl;
    //std::cout << "VY : " << velocity.y << std::endl;
    //std::cout << "XB : " << object.position.x << std::endl;
    //std::cout << "YB : " << object.position.y << std::endl;
    //object.position += glm::vec2{ 5, 5 };

    
    object.Update(0, 0, 100000, 0, false);
    
    std::cout << "XA : " << object.position.x << std::endl;
    std::cout << "YA : " << object.position.y << std::endl;
}

void Particle::draw() {
	object.Draw();
}









void ParticleSystem::update() {
    for (Particle particle : particles)
        particle.update();
}

void ParticleSystem::draw() {
#ifdef _DEBUG
		//std::cout << "Particle Storage Size:" << particles.size() << '\n';
#endif

		for (Particle particle : particles)
			particle.draw();
}