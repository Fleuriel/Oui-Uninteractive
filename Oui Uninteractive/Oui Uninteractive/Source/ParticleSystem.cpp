/**************************************************************************
 * @file ParticleSystem.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of Particle and ParticleSystem classes.
 *
 * This file contains the implementation of the Particle and ParticleSystem
 * classes for a software engineering project. These classes are part of a
 * particle system simulation, where particles are represented using OpenGL
 * objects and are updated and drawn on the screen. This file defines the
 * constructors, initialization, update, and draw functions for both the
 * Particle and ParticleSystem classes.
 *
 * The Particle class represents individual particles in the system, each
 * with its own properties such as position, size, velocity, transparency,
 * and lifespan. The ParticleSystem class manages a collection of particles,
 * updating and rendering them as a group.
 *
 * @see Particle
 * @see ParticleSystem
 *************************************************************************/

#include <ParticleSystem.h>
#include <Physics.h>
#include <OpenGLObjects.h>
#include "Editor.h"
#include "GameStateManager.h"


extern ParticleSystem particleSystem;


/*************************************************************************
 * @brief Constructor for the Particle class.
 *
 * This constructor initializes a Particle object with default values.
 * The Particle consists of an OpenGLObject, velocity, alpha (transparency),
 * lifespan, and an interactability flag.
 *************************************************************************/
Particle::Particle(int userInput_x, int userInput_y, float userInput_sizeX,
    float userInput_sizeY, float userInput_angleDisplacement,
    float userInput_angleSpeed, float userInput_lifespan) {
    // Initialize the OpenGLObject with a default color of {1, 1, 1}.
    object = OpenGLObject({ 1,1,1 });
    // Set the TagID for the Particle to 0.
    object.TagID = 0;
    // Initialize the velocity of the Particle to (1, 1).
    velocity = Vector2D(1, 1);
    // Set the initial alpha (transparency) value to 1 (fully opaque).
	alpha = 1;
    // Set the initial lifespan of the Particle to 1 unit of time.
    lifespan = userInput_lifespan;

    // Set the interactability flag to false, indicating that
    // the Particle is not initially interactable.
    object.interactable = false;

    Init(userInput_x, userInput_y, userInput_sizeX,
        userInput_sizeY, userInput_angleDisplacement,
        userInput_angleSpeed);

    ID = particleSystem.particles.size()+1;
    particleSystem.particles.push_back(*this);
    
}

void Particle::RemoveParticle() {
    particleSystem.particles.erase(particleSystem.particles.begin() + ID-1);
    UpdateIDs();
}

void Particle::UpdateIDs() {
    for (size_t i = 0; i < particleSystem.particles.size(); ++i)
        particleSystem.particles[i].ID = i+1;
}

/*************************************************************************
 * @brief Initialize a Particle object with user-provided parameters.
 *
 * This function initializes a Particle object with the specified parameters, setting
 * its position, size, angle displacement, and angle speed.
 *
 * @param userInput_x The x-coordinate of the Particle's position.
 * @param userInput_y The y-coordinate of the Particle's position.
 * @param userInput_sizeX The width (size along the x-axis) of the Particle.
 * @param userInput_sizeY The height (size along the y-axis) of the Particle.
 * @param userInput_angleDisplacement The initial angle displacement of the Particle.
 * @param userInput_angleSpeed The angular speed of the Particle.
 *************************************************************************/
void Particle::Init(int userInput_x, int userInput_y, float userInput_sizeX,
					float userInput_sizeY, float userInput_angleDisplacement,
					float userInput_angleSpeed) {
    // Initialize the Particle's OpenGLObject with the provided parameters.
    object.InitObjects(static_cast<float>(userInput_x), static_cast<float>(userInput_y), userInput_sizeX, userInput_sizeY, userInput_angleDisplacement, userInput_angleSpeed);
}

/*************************************************************************
 * @brief Update the state of the Particle.
 *
 * This function updates the state of the Particle object, typically called once per frame
 * to modify its properties. It updates the position of the Particle's OpenGLObject based on
 * its velocity and performs other necessary updates.
 *************************************************************************/
void Particle::Update() {

    
    // Update the position of the Particle's OpenGLObject based on its velocity.
   // object.Update(GetDT());
    

    // Uncommenting the following lines would print the scaleModel and position
    // of the Particle's OpenGLObject for debugging purposes.

    //std::cout << object.scaleModel.x << object.scaleModel.y << '\n';
    //std::cout << "XA : " << object.position.x << std::endl;
    //std::cout << "YA : " << object.position.y << std::endl;

    if ((lifespan -= GetDT())<0)
        RemoveParticle();
    std::cout << lifespan;
}


/*************************************************************************
 * @brief Draw the Particle on the screen.
 *
 * This function is responsible for drawing the Particle on the screen. It delegates the
 * drawing task to the `Draw` method of the Particle's OpenGLObject, which handles rendering
 * the visual representation of the Particle.
 *************************************************************************/
void Particle::Draw() {
    // Delegate the drawing task to the OpenGLObject associated with this Particle.
	object.Draw();
}

/*************************************************************************
 * @brief Update the Particle System.
 *
 * This function updates the state of the Particle System, including all the individual
 * particles it contains. It iterates through the particles and calls the `update` function
 * on each of them to modify their properties.
 *************************************************************************/
void ParticleSystem::Update() {
    // Start time profiling for particle system
    TimeProfiler profiler(Editor::timeRecorder.particlesTime);
    // Iterate through the particles
    for (size_t i = 0; i<particles.size();++i){
        // Print debug information about the current particle's position.
        //std::cout << particles[i].ID << "update " << particles[i].object.position.x << " " << particles[i].object.position.y << "\n";
        // Update the current particle's state.
        particles[i].Update();
    }
}

/*************************************************************************
 * @brief Draw the Particle System.
 *
 * This function is responsible for rendering the visual representation of the Particle System,
 * including all the individual particles it contains. It iterates through the particles and calls
 * the `draw` function on each of them to display their graphical representation on the screen.
 *************************************************************************/
void ParticleSystem::Draw() {

		std::cout << "Particle Storage Size:" << particles.size() << '\n';

        // Iterate through the particles
        for (size_t i = 0; i < particles.size(); ++i){   
            // Print debug information to indicate that the current particle is being drawn.
            // std::cout << i << "Draw\n";
            // Call the `draw` function on the current particle to render it.

            particles[i].Draw();

            // std::cout << particle.object.scaleModel.x << '\t' << particle.object.scaleModel.y << '\n';
        }

}

void ParticleSystem::EmptyParticleSystem() {
    particles.clear();
}