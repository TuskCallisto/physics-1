#include "raylib.h"
#include "raymath.h"
#include <vector>

struct PhysicsBody
{
    Vector2 position = Vector2Zeros;
    Vector2 velocity = Vector2Zeros;
    float drag = 1.0f;
    float invMass = 1.0f;
};

// Physics Simulation
struct PhysicsWorld
{
    Vector2 gravity = { 0.0f, 9.81f };
    std::vector<PhysicsBody> entities;
};

int main()
{
    InitWindow(800, 800, "Physics-1");
    SetTargetFPS(60);

    Rectangle platform;
    platform.x = 0.0f;
    platform.y = 600.0f;
    platform.width = 100.0f;
    platform.height = 20.0f;

    Rectangle ground;
    ground.x = 0.0f;
    ground.y = 780.0f;
    ground.width = 800.0f;
    ground.height = 20.0f;

    PhysicsWorld world;

    float birdRadius = 10.0f;
    float birdSpeed = 100.0f;
    float birdAngle = 0.0f;

    Vector2 launchVelocity = Vector2Zeros;
    Vector2 launchPosition = Vector2Zeros;
    launchPosition.x = platform.x + platform.width - birdRadius;
    launchPosition.y = platform.y - (platform.height - birdRadius);

    // All you have to do for lab exercise 2 is add the remaining if-statements to countrol launch angle and launch speed
    // Be sure to complete the re-launch logic when space is pressed too!
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // When space is pressed (lab 2 part 1):
        if (IsKeyPressed(KEY_SPACE))
        {
            PhysicsBody bird;
            // 1) TODO -- Set bird position to launch position
            // 2) TODO -- Set bird velocity to futureLaunchVelocity
            // 
            // 3) Add bird to physics world and watch it fly (done below)
            world.entities.push_back(bird);
        }

        if (IsKeyDown(KEY_D))
        {
            launchPosition.x += 100.0f * dt;
        }

        if (IsKeyDown(KEY_A))
        {
            launchPosition.x -= 100.0f * dt;
        }

        if (IsKeyDown(KEY_S))
        {
            launchPosition.y += 100.0f * dt;
        }

        if (IsKeyDown(KEY_W))
        {
            launchPosition.y -= 100.0f * dt;
        }

        if (IsKeyDown(KEY_Q))
        {
            // Rotate counter-clockwise at 90 degrees per second
            birdAngle -= 90.0f * DEG2RAD * dt;
        }

        if (IsKeyDown(KEY_E))
        {
            // Rotate counter-clockwise at 90 degrees per second
            birdAngle += 90.0f * DEG2RAD * dt;
        }

        if (IsKeyDown(KEY_ONE))
        {
            birdSpeed -= 50.0 * dt;
        }

        if (IsKeyDown(KEY_TWO))
        {
            birdSpeed += 50.0 * dt;
        }

        // Update all physics bodies
        for (size_t i = 0; i < world.entities.size(); i++)
        {
            PhysicsBody& e = world.entities[i];
            e.velocity += world.gravity * dt;   // v = a * t
            e.position += e.velocity * dt;      // p = v * t
        }

        // Update launch velocity every frame in case of speed or angle change
        launchVelocity = Vector2Rotate(Vector2UnitX, birdAngle) * birdSpeed;

        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangleRec(platform, DARKGRAY);
            DrawRectangleRec(ground, BEIGE);

            // Draw all physics bodies
            for (const PhysicsBody& e : world.entities)
            {
                DrawCircleV(e.position, birdRadius, RED);
            }

            // Where our bird should launch from when we press space
            DrawCircleV(launchPosition, birdRadius, ORANGE);

            // Show the result of user-defined launch-angle * launch-speed
            DrawLineEx(launchPosition, launchPosition + launchVelocity, 2.0f, GOLD);

            // Labels for user-defined launch values
            DrawText(TextFormat("Launch Position: %f %f", launchPosition.x, launchPosition.y), 10, 10, 20, RED);
            DrawText(TextFormat("Launch Angle: %f", birdAngle), 10, 40, 20, ORANGE);
            DrawText(TextFormat("Launch Speed: %f", birdSpeed), 10, 70, 20, GOLD);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
