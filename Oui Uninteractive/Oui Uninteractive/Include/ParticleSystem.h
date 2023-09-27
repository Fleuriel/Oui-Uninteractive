#include <CoordinateSystem.h>
#include <vector>
#include <OpenGLObjects.h>
#include <list>

class Particle {

public:
    Particle();
    void init(int userInput_x, int userInput_y, float userInput_sizeX,
              float userInput_sizeY, float userInput_angleDisplacement,
              float userInput_angleSpeed);
    void update();
    void draw();
    OpenGLObject object;

private:
    Vector2D velocity;
    int lifespan;
    int alpha;
    
};

class ParticleSystem {
public:
    void update();
    void draw();
    std::vector<Particle> particles;

private:
};