#include "raylib.h"

int main(void){
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(0); // uncapped fps
	
	Rectangle leftPaddle = {30, 175, 15, 100};
	Rectangle rightPaddle = {755, 175, 15, 100};

	Rectangle ball = {392, 217, 16, 16};

	float ballSpeedX = 400.0f;
	float ballSpeedY = 250.0f;

	float paddleSpeed = 500.0f;

	while (!WindowShouldClose()){
		float dt = GetFrameTime();

		if (IsKeyDown(KEY_W))
			leftPaddle.y -= paddleSpeed * dt;

		if (IsKeyDown(KEY_S))
			leftPaddle.y += paddleSpeed * dt;

		if (IsKeyDown(KEY_O))
			rightPaddle.y -= paddleSpeed * dt;

		if (IsKeyDown(KEY_L))
			rightPaddle.y += paddleSpeed * dt;

		if (leftPaddle.y < 0)
			leftPaddle.y = 0;

		if (leftPaddle.y + leftPaddle.height > screenHeight)
			leftPaddle.y = screenHeight - leftPaddle.height;

		if (rightPaddle.y < 0)
			rightPaddle.y = 0;

		if (rightPaddle.y + rightPaddle.height > screenHeight)
			rightPaddle.y = screenHeight - rightPaddle.height;

		ball.x += ballSpeedX * dt;
		ball.y += ballSpeedY * dt;

		if (ball.y <= 0){
			ball.y = 0;
			ballSpeedY *= -1;
		}

		if (ball.y + ball.height >= screenHeight){
			ball.y = screenHeight - ball.height;
			ballSpeedY *= -1;
		}

		if (CheckCollisionRecs(ball, leftPaddle) && ballSpeedX < 0){
			ball.x = leftPaddle.x + leftPaddle.width;
			ballSpeedX *= -1;
		}

		if (CheckCollisionRecs(ball, rightPaddle) && ballSpeedX > 0){
			ball.x = rightPaddle.x - ball.width;
			ballSpeedX *= -1;
		}

		if (ball.x < -ball.width || ball.x > screenWidth){
			ball.x = screenWidth / 2 - ball.width / 2;
			ball.y = screenHeight / 2 - ball.height / 2;

			ballSpeedX *= -1;
		}

		BeginDrawing();

		ClearBackground(BLACK);

		for (int y = 0; y < screenHeight; y += 20){
			DrawRectangle(screenWidth / 2 - 2, y, 4, 10, DARKGRAY);
		}

		DrawRectangleRec(leftPaddle, GREEN);
		DrawRectangleRec(rightPaddle, GREEN);

		DrawRectangleRec(ball, WHITE);

		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, GREEN);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
