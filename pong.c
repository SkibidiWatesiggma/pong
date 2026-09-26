#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(0);

    Rectangle leftPaddle = {
        30,
        screenHeight / 2 - 50,
        15,
        100
    };

    Rectangle rightPaddle = {
        screenWidth - 45,
        screenHeight / 2 - 50,
        15,
        100
    };

    float paddleSpeed = 550.0f;

    Rectangle ball = {
        screenWidth / 2 - 8,
        screenHeight / 2 - 8,
        16,
        16
    };

    float ballSpeedX = 500.0f;
    float ballSpeedY = 300.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_W))
        {
            leftPaddle.y -= paddleSpeed * dt;
        }

        if (IsKeyDown(KEY_S))
        {
            leftPaddle.y += paddleSpeed * dt;
        }

        if (IsKeyDown(KEY_O))
        {
            rightPaddle.y -= paddleSpeed * dt;
        }

        if (IsKeyDown(KEY_L))
        {
            rightPaddle.y += paddleSpeed * dt;
        }

        if (leftPaddle.y < 0)
        {
            leftPaddle.y = 0;
        }

        if (leftPaddle.y + leftPaddle.height > screenHeight)
        {
            leftPaddle.y = screenHeight - leftPaddle.height;
        }

        if (rightPaddle.y < 0)
        {
            rightPaddle.y = 0;
        }

        if (rightPaddle.y + rightPaddle.height > screenHeight)
        {
            rightPaddle.y = screenHeight - rightPaddle.height;
        }

        ball.x += ballSpeedX * dt;
        ball.y += ballSpeedY * dt;

        if (ball.y <= 0)
        {
            ball.y = 0;
            ballSpeedY *= -1;
        }

        if (ball.y + ball.height >= screenHeight)
        {
            ball.y = screenHeight - ball.height;
            ballSpeedY *= -1;
        }

        if (CheckCollisionRecs(ball, leftPaddle) && ballSpeedX < 0)
        {
            ball.x = leftPaddle.x + leftPaddle.width;

            float paddleCenter = leftPaddle.y + leftPaddle.height / 2;
            float ballCenter = ball.y + ball.height / 2;
            float hitPosition =
                (ballCenter - paddleCenter) / (leftPaddle.height / 2);

            ballSpeedX = 500.0f;
            ballSpeedY = hitPosition * 400.0f;
        }

        if (CheckCollisionRecs(ball, rightPaddle) && ballSpeedX > 0)
        {
            ball.x = rightPaddle.x - ball.width;

            float paddleCenter = rightPaddle.y + rightPaddle.height / 2;
            float ballCenter = ball.y + ball.height / 2;
            float hitPosition =
                (ballCenter - paddleCenter) / (rightPaddle.height / 2);

            ballSpeedX = -500.0f;
            ballSpeedY = hitPosition * 400.0f;
        }

        if (ball.x < -ball.width || ball.x > screenWidth)
        {
            bool wasMovingLeft = ballSpeedX < 0;

            ball.x = screenWidth / 2 - ball.width / 2;
            ball.y = screenHeight / 2 - ball.height / 2;

            ballSpeedX = wasMovingLeft ? 500.0f : -500.0f;
            ballSpeedY = 300.0f;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        for (int y = 0; y < screenHeight; y += 20)
        {
            DrawRectangle(
                screenWidth / 2 - 2,
                y,
                4,
                10,
                DARKGRAY
            );
        }

        DrawRectangleRec(leftPaddle, GREEN);
        DrawRectangleRec(rightPaddle, GREEN);
        DrawRectangleRec(ball, WHITE);

        DrawText(
            TextFormat("FPS: %d", GetFPS()),
            10,
            10,
            20,
            GREEN
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}