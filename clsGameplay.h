#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include <cmath>
#include "Globa.h"
const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 20;
int TotalTimerSecond = 0;

class clsGameplay {
private:
    static void DrawMap(short playerX, short playerY, short botplayerX, short botplayerY, short ballX, short ballY) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPosition;

        // Move cursor to the top left
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(hConsole, cursorPosition);

        for (short y = 0; y < MAP_HEIGHT; y++) {
            for (short x = 0; x < MAP_WIDTH; x++) {
                // Top and bottom borders with central goals
                if ((y == 0 || y == MAP_HEIGHT - 1) && !(x > MAP_WIDTH / 2 - 3 && x < MAP_WIDTH / 2 + 3)) {
                    std::cout << "_"; // Solid border excluding the goal area
                }
                else if (y == 0 || y == MAP_HEIGHT - 1) {
                    std::cout << " "; // Open goal area
                }
                // Left and right borders
                else if (x == 0 || x == MAP_WIDTH - 1) {
                    std::cout << "|";
                }
                // Centerline
                else if (y == MAP_HEIGHT / 2 && x % 2 == 0) {
                    std::cout << "-";
                }
                // Player paddle
                else if (x >= playerX && x < playerX + 3 && (y == playerY || y == playerY + 1)) {
                    std::cout << "_";
                }
                // Bot paddle
                else if (x >= botplayerX && x < botplayerX + 3 && (y == botplayerY || y == botplayerY + 1)) {
                    std::cout << "_";
                }
                // Ball
                else if (x == ballX && y == ballY) {
                    std::cout << "*";
                }
                // Empty space
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    static void WaitForContinue() {
        std::cout << "\n\n\n\nYou scored a goal! Press 'T' to continue...";
        while (true) {
            if (GetAsyncKeyState('T') & 0x8000) {
                break; // Continue when 'T' is pressed
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy-waiting
        }
    }

    static void WaitForContinue2() {
        std::cout << "\n\n\n\nThe bot scored a goal! Press 'T' to continue...";
        while (true) {
            if (GetAsyncKeyState('T') & 0x8000) {
                break; // Continue when 'T' is pressed
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy-waiting
        }
    }

    static void TimerGame() {
        TotalTimerSecond++;
        Timer = TotalTimerSecond / 60; // Update the global Timer variable
    }

public:
    static short levelGameplay(short levelGame) {
        switch (levelGame) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        }
    }

    static void PlayGame(char inputLeft, char inputRight, char inputUp, char inputDown) {
        const short MAP_HALF_WIDTH = MAP_WIDTH / 2;
        const short MAP_HALF_HEIGHT = MAP_HEIGHT / 2;
        const short PLAYER_START_X = MAP_HALF_WIDTH - 1;
        const short PLAYER_START_Y = MAP_HEIGHT - 3;

        short playerX = PLAYER_START_X;  // Player paddle position
        short playerY = PLAYER_START_Y;
        short botplayerX = PLAYER_START_X;
        short botplayerY = 1;  // Bot's starting position
        short ballX = MAP_HALF_WIDTH;
        short ballY = MAP_HALF_HEIGHT;
        short ballVelocityX = 1;
        short ballVelocityY = -1;
        ballVelocityX = 1;  // or -1
        ballVelocityY = -1;  // or 1
        int player2Score = 0;
        ScorePlay1 = 0;
        const short MAX_VELOCITY = 3;
        auto startTime = std::chrono::steady_clock::now();
        static int reactionCounter = 0; // Keeps track of reaction timing
        static int bounceCounter = 0;
        DrawMap(playerX, playerY, botplayerX, botplayerY, ballX, ballY);
        bool Gameruuing = true;
        std::cout << "\nPress 'E' to exit the game.";

        while (Gameruuing) {
            // Check for exit
            if (GetAsyncKeyState('E') & 0x8000) {
                break;
            }

            // Paddle controls
            if ((GetAsyncKeyState(inputLeft) & 0x8000) && playerX > 1) {
                playerX--;
            }
            if ((GetAsyncKeyState(inputRight) & 0x8000) && playerX < MAP_WIDTH - 4) {
                playerX++;
            }
            if ((GetAsyncKeyState(inputUp) & 0x8000) && playerY > MAP_HALF_HEIGHT) {
                playerY--;
            }
            if ((GetAsyncKeyState(inputDown) & 0x8000) && playerY < MAP_HEIGHT - 2) {
                playerY++;
            }

            // Bot movement
            if (levelGameplay(levelgame) == 1) {
                if (ballX > botplayerX + 1 && botplayerX < MAP_WIDTH - 4) botplayerX++;
                else if (ballX < botplayerX && botplayerX > 1) botplayerX--;
                if (ballY > botplayerY + 1 && botplayerY < MAP_HALF_HEIGHT - 1) botplayerY++;
                else if (ballY < botplayerY && botplayerY > 1) botplayerY--;
            }
            else if (levelGameplay(levelgame) == 2) {
                // Moderate speed with random adjustment
                int randomAdjustment = rand() % 2;
                if (ballX > botplayerX + 1 && botplayerX < MAP_WIDTH - 4) botplayerX += 2 + randomAdjustment;
                else if (ballX < botplayerX && botplayerX > 1) botplayerX -= 2 + randomAdjustment;
                if (ballY > botplayerY + 1 && botplayerY < MAP_HALF_HEIGHT - 1) botplayerY += 2 + randomAdjustment;
                else if (ballY < botplayerY && botplayerY > 1) botplayerY -= 2 + randomAdjustment;
            }
            else if (levelGameplay(levelgame) == 3) {
                // High speed with trajectory prediction
                int predictedBallX = ballX + ballVelocityX * 3;
                if (predictedBallX > botplayerX + 1 && botplayerX < MAP_WIDTH - 4) botplayerX += 3;
                else if (predictedBallX < botplayerX && botplayerX > 1) botplayerX -= 3;
                if (ballY > botplayerY + 1 && botplayerY < MAP_HALF_HEIGHT - 1) botplayerY += 3;
                else if (ballY < botplayerY && botplayerY > 1) botplayerY -= 3;
            }


            // Ball movement and collisions
            ballX += ballVelocityX;
            ballY += ballVelocityY;
            if (levelGameplay(levelgame) == 1) {
                if (ballX <= 1 || ballX >= MAP_WIDTH - 2) 
                    ballVelocityX = -ballVelocityX;
                
                if (ballY == 0 && !(ballX > MAP_HALF_WIDTH - 3 && ballX < MAP_HALF_WIDTH + 3)) 
                    ballVelocityY = -ballVelocityY;
         
                if (ballY == MAP_HEIGHT - 1 && !(ballX > MAP_HALF_WIDTH - 3 && ballX < MAP_HALF_WIDTH + 3)) 
                    ballVelocityY = -ballVelocityY;
                    
                if (ballY == playerY - 1 && ballX >= playerX && ballX < playerX + 3) 
                    ballVelocityY = -ballVelocityY;
                   
                
                if ((ballX == playerX - 1 || ballX == playerX + 3) && ballY == playerY) 
                    ballVelocityX = -ballVelocityX;
                 
                if (ballY == botplayerY + 1 && ballX >= botplayerX && ballX < botplayerX + 3) {
                    ballVelocityY = -ballVelocityY;
                    ballVelocityX = (ballX == botplayerX) ? -1 : (ballX == botplayerX + 2) ? 1 : ballVelocityX;
                }
                

            }
            else if (levelGameplay(levelgame) == 2) {
                // Ball collision with horizontal walls
                if (ballX <= 1 || ballX >= MAP_WIDTH - 2) {
                    ballVelocityX = -ballVelocityX;
                    bounceCounter++;
                }

                // Ball collision with vertical walls (ensure proper bounds checking)
                if (ballY <= 0) {  // Top boundary
                    ballY = 0;  // Reset position to valid bound
                    ballVelocityY = -ballVelocityY;
                    bounceCounter++;
                }
                if (ballY >= MAP_HEIGHT - 1) {  // Bottom boundary
                    ballY = MAP_HEIGHT - 1;  // Reset position to valid bound
                    ballVelocityY = -ballVelocityY;
                    bounceCounter++;
                }

                // Ball collision with player paddle
                if (ballY == playerY - 1 && ballX >= playerX && ballX < playerX + 3) {
                    ballVelocityY = -ballVelocityY;
                    bounceCounter++;
                }
                if ((ballX == playerX - 1 || ballX == playerX + 3) && ballY == playerY) {
                    ballVelocityX = -ballVelocityX;
                    bounceCounter++;
                }

                // Ball collision with bot paddle
                if (ballY == botplayerY + 1 && ballX >= botplayerX && ballX < botplayerX + 3) {
                    ballVelocityY = -ballVelocityY;
                    bounceCounter++;
                }

                // Increment velocity every 5 bounces
                if (bounceCounter > 0 && bounceCounter % 5 == 0) {
                    ballVelocityX += (ballVelocityX > 0) ? 1 : -1;
                    ballVelocityY += (ballVelocityY > 0) ? 1 : -1;
                }

                // Ensure velocities do not exceed MAX_VELOCITY
                if (std::abs(ballVelocityX) > MAX_VELOCITY) {
                    ballVelocityX = (ballVelocityX > 0) ? MAX_VELOCITY : -MAX_VELOCITY;
                }
                if (std::abs(ballVelocityY) > MAX_VELOCITY) {
                    ballVelocityY = (ballVelocityY > 0) ? MAX_VELOCITY : -MAX_VELOCITY;
                }
            }

            // Level 3 gameplay logic
            else if (levelGameplay(levelgame) == 3) {
                // Move the ball
                ballX += ballVelocityX;
                ballY += ballVelocityY;

                // Ball collision with left and right walls
                if (ballX <= 0) {
                    ballX = 0; // Prevent ball from going out of bounds
                    ballVelocityX = -ballVelocityX;
                    bounceCounter += 2;
                }
                if (ballX >= MAP_WIDTH - 1) {
                    ballX = MAP_WIDTH - 1; // Prevent ball from going out of bounds
                    ballVelocityX = -ballVelocityX;
                    bounceCounter += 2;
                }

                // Ball collision with top wall (except safe zone)
                if (ballY == 0 && !(ballX > MAP_HALF_WIDTH - 3 && ballX < MAP_HALF_WIDTH + 3)) {
                    ballY = 0; // Prevent ball from going out of bounds
                    ballVelocityY = -ballVelocityY;
                    bounceCounter += 2;
                }

                // Ball collision with bottom wall (except safe zone)
                if (ballY == MAP_HEIGHT - 1 && !(ballX > MAP_HALF_WIDTH - 3 && ballX < MAP_HALF_WIDTH + 3)) {
                    ballY = MAP_HEIGHT - 1; // Prevent ball from going out of bounds
                    ballVelocityY = -ballVelocityY;
                    bounceCounter += 2;
                }

                // Ball collision with player paddle
                if (ballY == playerY - 1 && ballX >= playerX && ballX < playerX + 3) {
                    ballY = playerY - 1; // Prevent ball from going out of bounds
                    ballVelocityY = -ballVelocityY;

                    // Slightly adjust X velocity for more challenging gameplay
                    ballVelocityX += (rand() % 3 - 1); // Random -1, 0, or 1
                    bounceCounter += 2;
                }

                // Ball collision with bot paddle
                if (ballY == botplayerY + 1 && ballX >= botplayerX && ballX < botplayerX + 3) {
                    ballY = botplayerY + 1; // Prevent ball from going out of bounds
                    ballVelocityY = -ballVelocityY;

                    // Adjust X velocity based on hit position
                    ballVelocityX = (ballX == botplayerX) ? -2 : (ballX == botplayerX + 2) ? 2 : ballVelocityX;
                    bounceCounter += 2;
                }

                // Ball speed adjustment every 5 bounces
                if (bounceCounter > 0 && bounceCounter % 5 == 0) {
                    ballVelocityX += (ballVelocityX > 0) ? 1 : -1;
                    ballVelocityY += (ballVelocityY > 0) ? 1 : -1;
                }

                // Cap the ball speed to MAX_VELOCITY
                if (std::abs(ballVelocityX) > MAX_VELOCITY) {
                    ballVelocityX = (ballVelocityX > 0) ? MAX_VELOCITY : -MAX_VELOCITY;
                }
                if (std::abs(ballVelocityY) > MAX_VELOCITY) {
                    ballVelocityY = (ballVelocityY > 0) ? MAX_VELOCITY : -MAX_VELOCITY;
                }

                // Ensure ball stays within map boundaries
                if (ballX < 0) ballX = 0;
                if (ballX >= MAP_WIDTH) ballX = MAP_WIDTH - 1;
                if (ballY < 0) ballY = 0;
                if (ballY >= MAP_HEIGHT) ballY = MAP_HEIGHT - 1;
            }


            // Scoring and reset logic
            if (ballY == 0 && (ballX > MAP_HALF_WIDTH - 3 && ballX < MAP_HALF_WIDTH + 3)) {
                ScorePlay1++;
                WaitForContinue2();
                ballX = MAP_HALF_WIDTH;
                ballY = MAP_HALF_HEIGHT;
                ballVelocityX = 1;
                ballVelocityY = -1;
                switch (levelGameplay(levelgame)) {
                case 1:
                    if (ScorePlay1 == 3){
                        std::cout << "your win :-)\n";
                        Gameruuing = false;
                        static bool _Wingame = true;
                        CounterWinGame++;
                    }
                    break;
                case 2:
                    if (ScorePlay1 == 5) {
                        std::cout << "you win :-)\n";
                        Gameruuing = false;
                        static bool _Wingame = true; 
                        CounterWinGame++;
                    }
                    break;
                case 3:
                    if (ScorePlay1 == 7) {
                        std::cout << "you win :-)\n";
                        Gameruuing = false;
                        static bool _Wingame = true;
                        CounterWinGame++;
                    }
                    break;
                }
            }
            if (ballY == MAP_HEIGHT - 1 && (ballX > MAP_HALF_WIDTH - 3 && ballX < MAP_HALF_WIDTH + 3)) {
                player2Score++;
                WaitForContinue();
                ballX = MAP_HALF_WIDTH;
                ballY = MAP_HALF_HEIGHT;
                ballVelocityX = -1;
                ballVelocityY = 1;
                if (player2Score == 3) {
                    std::cout << "you lost :-(\n";
                    static bool _Wingame = false;
                    break;
                }
            }

            // Update timer
            TimerGame();

            // Redraw the map and display stats
            DrawMap(playerX, playerY, botplayerX, botplayerY, ballX, ballY);
            std::cout << "Player Score: " << ScorePlay1 << " | Bot Score: " << player2Score << "\n";

            // Short delay for visibility
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

          //  std::cout << "\n\n\n\n\n\n\n\nBall Position: (" << ballX << ", " << ballY << "), Velocity: (" << ballVelocityX << ", " << ballVelocityY << ")\n";

        }
        std::cout << "Time Played: " << Timer << " minutes\n";
        std::cout << "think you for player :-)" << std::endl;
        Sleep(1500);
    }
 };
