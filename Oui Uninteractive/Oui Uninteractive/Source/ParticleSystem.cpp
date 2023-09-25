#include <ParticleSystem.h>
#include <Physics.h>
#include <OpenGLObjects.h>



extern ParticleSystem particleSystem;

Particle::Particle(){
    object = OpenGLObject({ 1,1,1 });
    velocity = Vector2D(1, 1);
	alpha = 1;
    lifespan = 1;
    object.particlechecker = true;
    particleSystem.particles.emplace_back(*this);
}

void Particle::init(int userInput_x, int userInput_y, float userInput_sizeX,
					float userInput_sizeY, float userInput_angleDisplacement,
					float userInput_angleSpeed) {
	object.mdl_ref = 0;
	object.shd_ref = 0;


	object.position.x = userInput_x;
	object.position.y = userInput_y;
	using glm::radians;

	object.scaleModel.x = userInput_sizeX;
	object.scaleModel.y = userInput_sizeY;

	object.angleDisplacment = userInput_angleDisplacement;
	object.angleSpeed = userInput_angleSpeed;

	glm::mat3 Translate = glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		 object.position.x, object.position.y, 1
	};

	glm::mat3 Rotation = glm::mat3
	{
		cosf(radians(object.angleDisplacment)), sinf(radians(object.angleDisplacment)) , 0,
		-sinf(radians(object.angleDisplacment)),  cosf(radians(object.angleDisplacment)) , 0,
		0, 0, 1
	};

	glm::mat3 Scale = glm::mat3
	{
		object.scaleModel.x, 0, 0,
		0, object.scaleModel.y, 0,
		0, 0, 1
	};

	glm::mat3 ScaleToWorldToNDC = glm::mat3
	{
		1 / (10000 / 2), 0, 0,
		0, 1 / (10000 / 2), 0,
		0, 0, 1
	};
	// Instead of doing transpose, you can do what OpenGL matrix does:
	// Row-Major Order:				Column Major Order;
	//	   x0 y0 z0						 x0 x1 x2
	//	   x1 y1 z1						 y0 y1 y2
	//	   x2 y2 z2						 z0 z1 z2
	object.model_To_NDC_xform = ScaleToWorldToNDC * Translate * Rotation * Scale;
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

void Particle::draw() {
	object.shdrpgms[object.shd_ref].Use(); // Install the shader program

	// Part 2: Bind object's VAO handle
	glBindVertexArray(object.models[object.mdl_ref].vaoid); // Bind object's VAO handle

	glDrawElements(
		GL_TRIANGLES, // Use GL_TRIANGLES for filled rendering
		object.models[object.mdl_ref].draw_cnt,
		GL_UNSIGNED_SHORT,
		nullptr
	);

	glBindVertexArray(0); // Unbind the VAO
	object.shdrpgms[object.shd_ref].UnUse(); // Uninstall the shader program
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