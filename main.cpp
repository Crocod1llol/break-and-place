#include <string>
#include <iostream>
#include <vector>

extern "C" {
	#include "raylib.h"
}

//define constants
const int Width = 1002;
const int Height = 801;

//defying classes for different blocks
class dirt {
    public:
	//coordonates
	float x;
	float y;

	//textures
	Texture2D texture = LoadTexture("./resources/dirt.png");

	Rectangle hitbox = {x, y, 50, 50};
};

class stone {
    public:
	//coordonates
	float x;
	float y;

	//textures
	Texture2D texture = LoadTexture("resources/stone.png");

	Rectangle hitbox = {x, y, 50, 50};
};

class grass {
    public:
	//coordonates
	float x;
	float y;

	//textures
	Texture2D texture = LoadTexture("resources/grass.png");

	Rectangle hitbox = {x, y, 50, 50};
};

class wood {
    public:
	//coordonates
	float x;
	float y;

	//textures
	Texture2D texture = LoadTexture("resources/wood.png");

	Rectangle hitbox = {x, y, 50, 50};
};

//variable to keep count of the picked block
// 1 - stone; 2 - dirt; 3 - grass; 4 - wood
int blockPick = 4;

//variables to keep count of the amount of blocks available
int maxBlocksOption = 4;
int minBlocksOption = 1;

int main() {
	
	InitWindow(Width, Height, "block game (alpha 1.0)");
	InitAudioDevice();

	SetExitKey(KEY_APOSTROPHE);

	SetTargetFPS(60);

	//generating structures to create the map :0
	//using a vector to keep track of the spawned blocks
	std::vector<stone> wstone;
	std::vector<dirt> wdirt;
	std::vector<grass> wgrass;
	std::vector<wood> wwood;
	
	//creating a loop to make the default world have all the blocks
	
	//SPAWNING GRASS 
	//loop for the horinzontal axis
	for (float i = 0; i < 951; i = i + 50) {
		//creating a loop to have a row of blocks
		grass gworld = {i, 450};

		//then add to vector
		wgrass.push_back(gworld);
	}

	//SPAWNING DIRT 
	//loop for the vertical axis
	for (float y = 500; y <= 550; y = y + 50) {
		//loop for the horinzontal axis
		for (float i = 0; i < 951; i = i + 50) {
			//creating a loop to have a row of blocks
			dirt dworld = {i, y};

			//then add to vector
			wdirt.push_back(dworld);
		}
	}

	//SPAWNING STONE  @
	//loop for the vertical axis
	for (float y = 600; y <= 750; y = y + 50) {
		//loop for the horinzontal axis
		for (float i = 0; i < 951; i = i + 50) {
			//creating a loop to have a row of blocks
			stone sworld = {i, y};
			
			//then add to vector
			wstone.push_back(sworld);
		}
	}

	//main loop
	while (!WindowShouldClose()) {
		
		//DEFY mouseHitbox
		float mosX = GetMouseX();
		float mosY = GetMouseY();
		//mouse hitbox as rectangle for rectangle collision
		Rectangle mouseHitbox = {mosX, mosY, 2, 2};

		//setup canvas (DO NOT DRAW ANYTHING BEFORE THIS)
		BeginDrawing();
		ClearBackground(SKYBLUE);

		DrawText(TextFormat("Selected Block: %d", blockPick), 0, 0, 20, BLACK);

		//setting up world spawn blocks
		//stone:
		for (long unsigned int a = 0; a < wstone.size(); a++) {
			//get the value from the pos of the vector (a)
			auto i = wstone.at(a);

			DrawTexture(i.texture, i.x, i.y, WHITE); 

			//check if mouse hitbox collides with block hitbox and if the LMB is pressed
			//also remove from vector to prevent them from loading in
			if (CheckCollisionRecs(i.hitbox, mouseHitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

				wstone.erase(wstone.begin() + a);
			}
		}

		//dirt:
		for (long unsigned int a = 0; a < wdirt.size(); a++) {

			//get the value from the pos of the vector (a)
			auto i = wdirt.at(a);

			DrawTexture(i.texture, i.x, i.y, WHITE); 

			//check if mouse hitbox collides with block hitbox and if the LMB is pressed
			//also remove from vector to prevent them from loading in
			if (CheckCollisionRecs(i.hitbox, mouseHitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

				wdirt.erase(wdirt.begin() + a);
			}
		}

		//grass:
		for (long unsigned int a = 0; a < wgrass.size(); a++) {
			//get the value from the pos of the vector (a)
			auto i = wgrass.at(a);

			DrawTexture(i.texture, i.x, i.y, WHITE); 

			//check if mouse hitbox collides with block hitbox and if the LMB is pressed
			//also remove from vector to prevent them from loading in
			if (CheckCollisionRecs(i.hitbox, mouseHitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

				wgrass.erase(wgrass.begin() + a);
			}
		}

		//wood:
		for (long unsigned int a = 0; a < wwood.size(); a++) {
			//get the value from the pos of the vector (a)
			auto i = wwood.at(a);

			DrawTexture(i.texture, i.x, i.y, WHITE); 

			//check if mouse hitbox collides with block hitbox and if the LMB is pressed
			//also remove from vector to prevent them from loading in
			if (CheckCollisionRecs(i.hitbox, mouseHitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

				wwood.erase(wwood.begin() + a);
			}
		}

		//the section responsible for placing blocks:
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			
			//the future variables
			int future_x;
			int future_y;

			//also convert the mosX and mosY to int
			int int_mosX = (int)mosX;
			int int_mosY = (int)mosY;

			//check if the mouse pos align with the X grid
			//and if its NOT, then subtract the amount of offset it has
			if (int_mosX % 50 != 0) {
				future_x = int_mosX - (int_mosX % 50);

			} else {
				future_x = int_mosX;
			}

			//check if the mouse pos align with the X grid
			//and if its NOT, then subtract the amount of offset it has
			if (int_mosY % 50 != 0) {
				future_y = int_mosY - (int_mosY % 50);

			} else {
				future_y = int_mosY;
			}

			//and also check what block is picked before
			//object and inserting into vector

			if (blockPick == 1) {
				stone fstone = {future_x, future_y};
			
				wstone.push_back(fstone);
			}
			if (blockPick == 2) {
				dirt fdirt = {future_x, future_y};

				wdirt.push_back(fdirt);
			}
			if (blockPick == 3) {
				grass fgrass = {future_x, future_y};

				wgrass.push_back(fgrass);
			}
			if (blockPick == 4) {
				wood fwood = {future_x, future_y};
				
				wwood.push_back(fwood);
			}
			
		}


		//DrawRectangleRec(mouseHitbox, GRAY);
		DrawText(TextFormat("Selected Block: %d", blockPick), 0, 0, 20, BLACK);

		//the section for picking blocks (keyboard):
		if (IsKeyPressed(KEY_ONE)) {
			blockPick = 1;
		}
		if (IsKeyPressed(KEY_TWO)) {
			blockPick = 2;
		}
		if (IsKeyPressed(KEY_THREE)) {
			blockPick = 3;
		}
		if (IsKeyPressed(KEY_FOUR)) {
			blockPick = 4;
		}
		
		//the section for picking blocks (MOUSE WHEEL):

		blockPick = blockPick + GetMouseWheelMove();

		//borders
		if (blockPick > maxBlocksOption) {
			blockPick = maxBlocksOption;
		}
		if (blockPick < minBlocksOption) {
			blockPick = minBlocksOption;
		}

		EndDrawing();
	}

	CloseWindow();
	CloseAudioDevice();

	return 0;
}
