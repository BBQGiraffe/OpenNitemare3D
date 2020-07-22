#include <SDL.h>
#undef main
#include "engine/img/img.h"
#include <iostream>
#include "game/entities/player/Player.h"
#include <SDL_mixer.h>
#include <fstream>
IMG img;

SDL_Window* window = SDL_CreateWindow("Nitemare 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
bool open = true;

int ray_w = 320, ray_h = 200;



Uint32* pixels = new Uint32[ray_w * ray_h];

SDL_Texture* canvas = SDL_CreateTexture
(
	renderer,
	SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING,
	ray_w, ray_h
);

static Uint32 ColourToUint(Color c)
{
	return (Uint32)((c.r << 16) + (c.g << 8) + (c.b << 0));
}

void DrawPixel(int x, int y, Color color) {
	pixels[y * ray_w + x] = ColourToUint(color);
}

void ClearScreen() {
	for (int x = 0; x < ray_w; x++) {
		for (int y = 0; y < ray_h; y++) {
			DrawPixel(x, y, Color(0, 0, 0));
		}
	}
}

void Draw2DSprite(Sprite* sprite, int x, int y) {
    int i = 0;
    for (int tx = 0; tx < sprite->width; tx++) {
        for (int ty = 0; ty < sprite->height; ty++) {
            if (sprite->buffer[i] != Color(255, 255, 255)) {
                DrawPixel(tx + x, ty + y, sprite->buffer[i]);
            }
            
            i++;
        }
    }
}

struct wall {
    std::int8_t x, y;
    std::int8_t texture;
};

std::vector<wall> walls;


Color GetPixel(Sprite* sprite, int x, int y) {
	int i = x + y  * 64;
	return sprite->buffer[i];
}



std::vector<size_t> offsets;
char* mapbuff = new char[8192];
void LoadMap(int index) {
    std::ifstream is;

    is.open("MAP.1", std::ios::binary);


    is.seekg(514 + (8192*index));
    is.read(mapbuff, 8192);
}
#include <assert.h>


/*
for some reason Nitemare 3D has room types for floors and draws the walls based the room type


    floor layout in map file:
        #####
        #####
        &&&&&
    
    what's drawn:
         WWWW
        W####W
        W####W
        D&&&&D
         DDDD

    so now I have to write a bunch of sphagetti code to fix this
*/
void AddWalls(std::vector<int> map) {
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 64; y++) {
            int i = x + y*64;
            
            //if the nearby is empty, add wall
            if (map[i] != 1) {
                int X = x - 1;
                int I = X + y * 64;
                if (map[I] == 1) {
                    //std::cout << "Tile " << X << "," << y << " should be wall! \n";
                    map[I] == 420;
                }
            }
        }
    }
}
Uint32 time = 0; //time of current frame
Uint32 oldTime = 0; //time of previous frame
const int fps = 60;
const int fpsDelay = 1000 / fps;
Uint32 frameStart;
int frameTime;

int CalculateOffset(int index) {
    if (index > 14) {
        return index - 8;
    }

    return 0;
}


void main() {

    
    LoadMap(0);
    Map map;
   

    std::ofstream myfile("map1.txt", std::ios::binary);
    for (int i = 0; i < 64 * 64; i++) {
        map.maptiles.push_back(0);
    }
    if (myfile.is_open())
    {
        int j = 0;
        int k = 64 * 64;
        for (int i = 0; i < 64 * 64*2; i++) {

            if (i % 2 == 0) {
                
                //maptiles.push_back(mapbuff[i]);
                map.maptiles[j] = mapbuff[i];
                k--;
                j++;
                myfile << mapbuff[i];

            }
            
            
        }
        
        myfile.close();
    }


    AddWalls(map.maptiles);
  /*
    int j = 0;
    for (int i = 0; i < 64 * 64 * 2; i++) {
        if (j % 2 == 0) {
            maptiles[i] = mapbuff[i];
        }
    }
    */

	Camera* c = new Camera();
	
	
    img.Init("GAME.PAL", "IMG.1");
	
	memset(pixels, 255, ray_w * ray_h * sizeof(Uint32));

	SDL_Event event;
	SDL_RenderSetLogicalSize(renderer, 320, 240);
    
	Player* player = new Player(22, 56, c, map);
    std::cout << "cock\n";
    
    

	while (open) {
        //std::cout << player->GetTilePosition().x << "," << player->GetTilePosition().y << std::endl;
        Uint64 start = SDL_GetPerformanceCounter();
        frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {

		}
		SDL_RenderClear(renderer);
		
		ClearScreen();
		

        for (int x = 0; x < ray_w; x++)
        {
            //calculate ray position and direction
            double cameraX = 2 * x / double(ray_w) - 1; //x-coordinate in camera space
            double rayDirX = player->dirX + c->planeX * cameraX;
            double rayDirY = player->dirY + c->planeY * cameraX;
            //which box of the map we're in

            int mapX = player->GetTilePosition().x;//int(posX);
            int mapY = player->GetTilePosition().y;//int(posY);

            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            //length of ray from one x or y-side to next x or y-side
            double deltaDistX = std::abs(1 / rayDirX);
            double deltaDistY = std::abs(1 / rayDirY);
            double perpWallDist;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

            // Alternative code for deltaDist in case division through zero is not supported
            deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
            deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));
            

            //calculate step and initial sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (player->GetPosition().x - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - player->GetPosition().x) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (player->GetPosition().y - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - player->GetPosition().y) * deltaDistY;
            }
           
            int texture = 1;
            //perform DDA
            while (hit == 0)
            {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                //Check if ray has hit a wall
                //if (map.worldMap[mapX][mapY] > 0) hit9 = 1;


                //what?
                //int wall = map.maptiles[-(mapX - mapY * 64)];
                int wall = map.maptiles[mapX + mapY * 64];
                texture = wall;
              
                if (texture >= 3) {
                    texture++;
                }
                if (texture >= 4) {
                    texture++;
                }

                if (wall <= 181 && wall > 0) hit = 1;
                
                
                
            }

            

            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (side == 0) perpWallDist = (mapX - player->GetPosition().x + (1 - stepX) / 2) / rayDirX;
            else           perpWallDist = (mapY - player->GetPosition().y + (1 - stepY) / 2) / rayDirY;


            //Calculate height of line to draw on screen
            int lineHeight = (int)(ray_h / perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + ray_h / 2;
            if (drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + ray_h / 2;
            if (drawEnd >= ray_h)drawEnd = ray_h - 1;

            //texturing calculations
            int texNum = 1;//map.worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

            //calculate value of wallX
            float wallX; //where exactly the wall was hit
            if (side == 0) wallX = player->GetPosition().y + perpWallDist * rayDirY;
            else           wallX = player->GetPosition().x + perpWallDist * rayDirX;
            wallX -= floor((wallX));

            //x coordinate on the texture
            int texX = int(wallX * float(64));
            if (side == 0 && rayDirX > 0) texX = 64 - texX - 1;
            if (side == 1 && rayDirY < 0) texX = 64 - texX - 1;

            float step = 1.0 * 64 / lineHeight;
            // Starting texture coordinate
            float texPos = (drawStart - ray_h / 2 + lineHeight / 2) * step;
            for (int y = drawStart; y < drawEnd; y++)
            {
                // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
                int texY = (int)texPos & (64 - 1);
                texPos += step;
                
                DrawPixel(x, y, GetPixel(img[texture], texY, texX));
            }

            
            
           


        }

        oldTime = time;
        time = SDL_GetTicks();
        
        float frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds

        if (fpsDelay > frameTime) {
            SDL_Delay(fpsDelay - frameTime);
        }

        Uint64 end = SDL_GetPerformanceCounter();

        const Uint8* state = SDL_GetKeyboardState(NULL);
 

        player->Update(frameTime);

       
        


        

        

        
        //player->SetPosition(posX, posY);
        Draw2DSprite(img[700], 160, 100);
        

        
        for (int x = 0; x < 64; x++) {
            for (int y = 0; y < 64; y++) {
                int ti = -(x - y * 64);

                if (map.maptiles[ti] != 1) {
                    //Draw2DSprite(img[1], x * 64, y * 64);
                    DrawPixel(x, y, Color(255, 255, 255));
                }
                else {
                    DrawPixel(x, y, Color(0, 0, 0));
                }
            }
        }
        
		
        DrawPixel(player->GetTilePosition().x, player->GetTilePosition().x, Color(0, 0, 0));


		SDL_UpdateTexture(canvas, NULL, pixels, ray_w * sizeof(Uint32));
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderCopy(renderer, canvas, NULL, NULL);
		SDL_RenderPresent(renderer);



      
        
		

	}
}