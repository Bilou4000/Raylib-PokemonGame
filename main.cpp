#include <iostream>
#include <string>

#include "raylib.h"
#include "Battle.h"
#include "StartGame.h"
#include "allTrainers.h"

using namespace std;

typedef enum GameScreen { MENU, START, STROLL, ATTACKPOKEMON, ATTACKTRAINER, ENDING } GameScreen;
GameScreen currentScreen;

//Screen
int screenWidth = 1600; //1600
int screenHeight = 1200; //1200

int boxInput = NULL;
int answerPath = NULL;

//text Box
Rectangle TextBox { screenWidth - 1550, screenHeight - 425 - 20, 1500, 400 };
Rectangle pathAnswerBox{ 780, 850, 80, 70 };

//player and opponent
vector<Pokemon> firstTeam;
vector<Pokemon> secondTeam;

Trainer firstTrainer;
Trainer secondTrainer;

StartGame startGame;

Battle theBattle; 
Pokemon opponentPokemon = Pokemon();
bool isInCombat = false;

//Function
void Load();
void Update();
void Draw();
void Unload();

void StrollingAround();

int main()
{
    Load();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    Unload();
    return 0;
}


void Load() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "RAYLIB PROJECT");
    currentScreen = MENU;
    SetTargetFPS(60);

    AllPokemons::Load();
    allTrainer::Init();
    startGame.Init();


    //--------------------------------------TO CHANGE -------------------------------------------------------------------
    //secondTeam = { AllPokemons::Copperajah, AllPokemons::Snorlax, AllPokemons::Magikarp };
    //secondTrainer = Trainer("MECHANT", "GRONUL", "OHOHOHOHOHOH !!!", secondTeam); 

    //--------------------------------------TO CHANGE -------------------------------------------------------------------
    theBattle = Battle(firstTrainer, secondTrainer);

}

void Update() 
{
    switch (currentScreen)
    {
        case MENU:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = START;
            }
        }
        break;
        case START:
        {
            startGame.Update();
            if (startGame.Update())
            {
                string firstName = startGame.mFirstName;
                string lastName = startGame.mLastName;

                firstTeam.push_back(startGame.mPlayerPokemon);

                firstTrainer = Trainer(firstName, lastName, "As the wind continues to blow, so too shall I continue to fight !", firstTeam);
                currentScreen = STROLL;
            }
        }
        case STROLL:
        {
            isInCombat = false;
            StrollingAround();

            srand(time(NULL));
            int randomTrainer = rand() % allTrainer::mAllTrainers.size();
            secondTrainer = allTrainer::mAllTrainers[randomTrainer];
        }
        break;
        case ATTACKPOKEMON:
        {
            if (!isInCombat)
            {
                opponentPokemon = theBattle.ChoosePokemonToCapture();
                isInCombat = true;
            }

            theBattle.BattleAgainstPokemon(opponentPokemon);
            theBattle.BattleCaptureUpdate();

            if (theBattle.EndOfBattle())
            {
                currentScreen = STROLL;
            }
        }
        break;
        case ATTACKTRAINER:
        {
            if (!isInCombat)
            {
                opponentPokemon = theBattle.ChooseOpponentPokemon();
                isInCombat = true;
            }

            theBattle.BattleAgainstTrainer(opponentPokemon);
            theBattle.BattleTrainerUpdate();

            if (theBattle.EndOfBattle())
            {
                currentScreen = STROLL;
            }
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_R))
            {
                // restart
                currentScreen = START;
            }

            if (IsKeyPressed(KEY_SEMICOLON))
            {
                // go to menu
                currentScreen = MENU;
            }
        }
        break;
        default: break;
    }
}

void StrollingAround()
{
    if (GetKeyPressed())
    {
        boxInput = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER) && answerPath > 0 && answerPath <= 2)
    {
        if (answerPath == 1) 
        {
            currentScreen = ATTACKTRAINER;
        }
        else if (answerPath == 2) 
        {
            currentScreen = ATTACKPOKEMON;
        }
    }
}


void Draw() 
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    switch (currentScreen)
    {
        case MENU:
        {
            DrawText("POKEMON", 450, 150, 150, RED);
            DrawText("Press ENTER to PLAY", 350, 400, 80, BLACK);
        }
        break;
        case START:
        {
            DrawRectangleRec(TextBox, WHITE);

            startGame.Draw();
           
        }
        break;
        case STROLL:
        {
            DrawRectangleRec(TextBox, WHITE);

            DrawText("YOU HAVE 2 PATH IN FRONT OF YOU : ", 70, 125, 70, RED);
            DrawText("1. Challenge an other trainer ", 70, 300, 70, BLACK);
            DrawText("2. Try to battle and capture a Pokemon : ", 70, 400, 70, BLACK);

            DrawText("Choose a path : ", 70, 775, 70, BLACK);
            DrawText("Write the corresponding number :", 70, 870, 40, RED);

            DrawRectangleRec(pathAnswerBox, LIGHTGRAY);

            if (isdigit(boxInput))
            {
                string printAnswer { (char) boxInput };
                DrawText(TextFormat("%s", printAnswer.c_str()), 800, 855, 70, BLACK);

                answerPath = stoi(printAnswer);
            }
            else
            {
                DrawText("_", 800, 855, 70, BLACK);
            }
        }
        break;
        case ATTACKPOKEMON:
        {
            DrawRectangleRec(TextBox, WHITE);
            theBattle.BattleCaptureDraw();
        }
        break;
        case ATTACKTRAINER:
        {
            DrawRectangleRec(TextBox, WHITE);
            theBattle.BattleTrainerDraw();
        }
        break;
        case ENDING:
        {
            DrawText("Press R to PLAY AGAIN", 350, 400, 80, BLACK);
            DrawText("Or Press M to go back to MENU", 150, 500, 80, BLACK);
        }
        break;
        default: break;
    }

    EndDrawing();
}

void Unload() 
{
    CloseWindow();
}


