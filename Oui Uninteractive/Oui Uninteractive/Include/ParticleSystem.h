//#include <CoordinateSystem.h>
//
//class Particle {
//public:
//    Particle(float x, float y) : position(x, y), velocity(0.0f, -1.0f), lifespan(100), alpha(255) {}
//
//    void Update() {
//        position += velocity;
//        lifespan -= 1;
//        alpha = static_cast<Uint8>(lifespan * 2.55f); // Convert lifespan to alpha value (0-255)
//    }
//
//    bool IsDead() {
//        return lifespan <= 0;
//    }
//
//    void Render(SDL_Renderer* renderer) {
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
//        SDL_RenderDrawPoint(renderer, static_cast<int>(position.x), static_cast<int>(position.y));
//    }
//
//private:
//    Coordinates position;
//    Vector2D velocity;
//    int lifespan;
//    Uint8 alpha;
//};
//
//class ParticleSystem {
//public:
//    ParticleSystem(int numParticles, float x, float y) {
//        for (int i = 0; i < numParticles; ++i) {
//            particles.push_back(Particle(x, y));
//        }
//    }
//
//    void Update() {
//        for (auto& particle : particles) {
//            particle.Update();
//        }
//
//        particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) {
//            return p.IsDead();
//            }), particles.end());
//    }
//
//    void Render(SDL_Renderer* renderer) {
//        for (const auto& particle : particles) {
//            particle.Render(renderer);
//        }
//    }
//
//private:
//    std::vector<Particle> particles;
//};