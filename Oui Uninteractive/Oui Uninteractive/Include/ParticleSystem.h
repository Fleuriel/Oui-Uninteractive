#include <CoordinateSystem.h>
#include <vector>
#include <OpenGLObjects.h>
#include <list>



class Particle {
public:
    Particle() :object(OpenGLObject({ 1,1,1 })), velocity(Vector2D(1, 1)), lifespan(1) { object.particlechecker = true; }
    OpenGLObject object;
private:
    Vector2D velocity;
    int lifespan;
    int alpha;
    
};

class ParticleSystem {
public:


private:
    std::vector<Particle> particles;
};