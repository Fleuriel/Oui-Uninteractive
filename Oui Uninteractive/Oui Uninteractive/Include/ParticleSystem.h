/**************************************************************************
 * @file ParticleSystem.h
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

#include <CoordinateSystem.h>
#include <vector>
#include <OpenGLObjects.h>
#include <list>


class Particle {

public:
    /*************************************************************************
     * @brief Constructor for the Particle class.
     *
     * This constructor initializes a Particle object with default values.
     * The Particle consists of an OpenGLObject, velocity, alpha (transparency),
     * lifespan, and an interactability flag.
     *************************************************************************/
    Particle();

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
    void Init(int userInput_x, int userInput_y, float userInput_sizeX,
              float userInput_sizeY, float userInput_angleDisplacement,
              float userInput_angleSpeed);

    /*************************************************************************
     * @brief Update the state of the Particle.
     *
     * This function updates the state of the Particle object, typically called once per frame
     * to modify its properties. It updates the position of the Particle's OpenGLObject based on
     * its velocity and performs other necessary updates.
     *************************************************************************/
    void Update();

    /*************************************************************************
     * @brief Draw the Particle on the screen.
     *
     * This function is responsible for drawing the Particle on the screen. It delegates the
     * drawing task to the `Draw` method of the Particle's OpenGLObject, which handles rendering
     * the visual representation of the Particle.
     *************************************************************************/
    void Draw();

    /*************************************************************************
     * @brief Destructor for the Particle class.
     *************************************************************************/
    ~Particle() {};

    OpenGLObject object;
private:
    Vector2D velocity;  //stores the speed and direction of particle movement
    int lifespan;       //determines how long the particle exists
    int alpha;          //determines the opacity of the particle
    
};

class ParticleSystem {
public:
    /*************************************************************************
     * @brief Update the Particle System.
     *
     * This function updates the state of the Particle System, including all the individual
     * particles it contains. It iterates through the particles and calls the `update` function
     * on each of them to modify their properties.
     *************************************************************************/
    void Update();

    /*************************************************************************
     * @brief Draw the Particle System.
     *
     * This function is responsible for rendering the visual representation of the Particle System,
     * including all the individual particles it contains. It iterates through the particles and calls
     * the `draw` function on each of them to display their graphical representation on the screen.
     *************************************************************************/
    void Draw();

    std::vector<Particle> particles; //container storing all particles

    /*************************************************************************
     * @brief Destructor for the ParticleSystem class.
     *************************************************************************/
    ~ParticleSystem() {};

private:
};