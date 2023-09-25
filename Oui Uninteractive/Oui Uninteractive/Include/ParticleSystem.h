#include <CoordinateSystem.h>
#include <vector>
#include <OpenGLObjects.h>
#include <list>

class Particle {

public:
    Particle();
    void update();
    OpenGLObject object;

private:
    Vector2D velocity;
    int lifespan;
    int alpha;
    
};

class ParticleSystem {
public:
    void update();
    std::vector<Particle> particles;

private:
};