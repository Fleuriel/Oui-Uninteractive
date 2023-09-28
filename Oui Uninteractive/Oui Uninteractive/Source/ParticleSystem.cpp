#include <ParticleSystem.h>
#include <Physics.h>
#include <OpenGLObjects.h>
#include <chrono>
#include "Editor.h"


extern ParticleSystem particleSystem;



Particle::Particle(){
    object = OpenGLObject({ 1,1,1 });
    object.TagID = 0;
    velocity = Vector2D(1, 1);
	alpha = 1;
    lifespan = 1;
    object.interactable = false;
}

void Particle::init(int userInput_x, int userInput_y, float userInput_sizeX,
					float userInput_sizeY, float userInput_angleDisplacement,
					float userInput_angleSpeed) {
    object.InitObjects(userInput_x, userInput_y, userInput_sizeX, userInput_sizeY, userInput_angleDisplacement, userInput_angleSpeed);
}

void Particle::update() {

    
//    object.Update(0, 0, 100000, 0, false);
    
    object.Update(object.position.x + velocity.x, object.position.y + velocity.y, 1000, 1000, 0, false);
    
    //std::cout << object.scaleModel.x << object.scaleModel.y << '\n';

 //   std::cout << "XA : " << object.position.x << std::endl;
 //   std::cout << "YA : " << object.position.y << std::endl;
}

void Particle::draw() {
	object.Draw();
}


void ParticleSystem::update() {
    std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    // i starts at 1 to skip updating the background
    for (size_t i = 1; i<particles.size();++i)
    {
        std::cout << i << "update " << particles[i].object.position.x << " " << particles[i].object.position.y << "\n";
        particles[i].update();
    }
    std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = timeEnd - timeStart;
    Editor::timeRecorder.particlesTime = duration.count();
}

void ParticleSystem::draw() {

		//std::cout << "Particle Storage Size:" << particles.size() << '\n';


        for (size_t i = 1; i < particles.size(); ++i)
        {
            std::cout << i << "Draw\n";
            particles[i].draw();
           // std::cout << particle.object.scaleModel.x << '\t' << particle.object.scaleModel.y << '\n';
        }

}