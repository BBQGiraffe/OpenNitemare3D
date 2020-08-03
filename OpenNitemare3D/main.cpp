#include <SDL.h>
#undef main
#include "engine/img/img.h"
#include <iostream>
#include "game/entities/player/Player.h"
#include <SDL_mixer.h>
#include <fstream>
#include <SDL_image.h>
#include "engine/dr_pcx.h"
#include "engine/tiles/Tiles.h"
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



char* mapbuff = new char[8192];
char* maptiles = new char[4096];
char* entities = new char[4096];

void LoadMap(int index) {
    std::ifstream is;

    is.open("MAP.1", std::ios::binary);


    is.seekg(514 + (8192*index));
    is.read(mapbuff, 8192);
}
#include <assert.h>

Uint32 time = 0; //time of current frame
Uint32 oldTime = 0; //time of previous frame
const int fps = 60;
const int fpsDelay = 1000 / fps;
Uint32 frameStart;
int frameTime;

Uint8* audioBuff = nullptr;
Uint8* audioBuffEnd = nullptr;


char pitch = 1;

void audioCallback(void* userdata, Uint8* stream, int len)
{
    Uint32 length = (Uint32)len;
    for (Uint32 i = 0; i < length; i++)
    {
        if (audioBuff > audioBuffEnd)
        {
            return;
        }

        stream[i] = audioBuff[0];
        stream[++i] = audioBuff[1];
        audioBuff += 2 * pitch;
    }
}

Tiles tiles;
void RegisterTiles() {
    
    tiles.RegisterTile(0, 229);
    tiles.RegisterTile(1, 0); //Dining Room - Plain
    tiles.RegisterTile(2, 1); //Dining Room - Small Picture
    tiles.RegisterTile(3, 2); //Dining Room - Sconces
    tiles.RegisterTile(4, 4); //Dining Room - Hutch
    tiles.RegisterTile(5, 6); //Dining Room - Large Picture


    tiles.RegisterTile(6, 8); //Dining Room - Window
    tiles.RegisterTile(7, 8); //Dining Room - Curtains


    tiles.RegisterTile(8, 10); //Dining Room - Panel R
    tiles.RegisterTile(9, 11); //Dining Room - Panel L
    tiles.RegisterTile(10, 12); //Living Room - Plain
    tiles.RegisterTile(11, 13); //Living Room - Curtains
    tiles.RegisterTile(12, 14); //Living Room - Window
    tiles.RegisterTile(13, 15); //Living Room - Bookcase
    tiles.RegisterTile(14, 16); //Living Room - Fireplace
    tiles.RegisterTile(15, 24); //Living Room - Panel Right
    tiles.RegisterTile(16, 25); //Living Room - Panel Left
    tiles.RegisterTile(17, 26); //Kitchen - Sink Area
    tiles.RegisterTile(18, 27); //Kitchen - Fuse box
    tiles.RegisterTile(19, 28); //Kitchen - Stove Area
    tiles.RegisterTile(20, 29); //Kitchen - Plain
    tiles.RegisterTile(21, 30); //Kitchen - Door(red key)
    tiles.RegisterTile(22, 31); //*Kitchen - Door (stairs up)
    tiles.RegisterTile(23, 32); //*Kitchen - Door (stairs down)
    tiles.RegisterTile(24, 33); //Kitchen - Panel Right
    tiles.RegisterTile(25, 34); //Kitchen - Panel Left
    tiles.RegisterTile(26, 35); //Beige Hallway - Plain
    tiles.RegisterTile(27, 36); //Beige Hallway - Panel Right
    tiles.RegisterTile(28, 37); //Beige Hallway - Panel Left
    tiles.RegisterTile(29, 38); //Grey Hallway - Plain
    tiles.RegisterTile(30, 39); //Grey Hallway - Panel Right
    tiles.RegisterTile(31, 40); //Grey Hallway - Panel Left
    tiles.RegisterTile(32, 41); //Garden - Plain
    tiles.RegisterTile(33, 42); //Garden - Eyes Right
    tiles.RegisterTile(34, 43); //Garden - Eyes Left
    tiles.RegisterTile(35, 44); //Garden - Gargoyle
    tiles.RegisterTile(36, 45); //Office - Plain
    tiles.RegisterTile(37, 46); //Office - Desk
    tiles.RegisterTile(38, 48); //Office - Cabinets
    tiles.RegisterTile(39, 49); //Office - Chalkboard
    tiles.RegisterTile(40, 50); //Office - Sconces
    tiles.RegisterTile(41, 52); //Bedroom 1 - Plain
    tiles.RegisterTile(42, 53); //Bedroom 1 - Window
    tiles.RegisterTile(43, 54); //Bedroom 1 - Dresser
    tiles.RegisterTile(44, 55); //Bedroom 1 - Mirror
    tiles.RegisterTile(45, 56); //Bedroom 3/1 Door (Green key)
    tiles.RegisterTile(46, 57); //Bedroom 1/3 Door (Green key)
    tiles.RegisterTile(47, 58); //Closet - Full
    tiles.RegisterTile(48, 59); //Closet - Panel Right
    tiles.RegisterTile(49, 60); //Closet - Panel Left
    tiles.RegisterTile(50, 61); //Bedroom 2 - Window
    tiles.RegisterTile(51, 62); //Bedroom 2/1 Door (Blue key)
    tiles.RegisterTile(52, 63); //Bedroom 1/2 Door (Blue key)
    tiles.RegisterTile(53, 64); //Bedroom 2 - Plain
    tiles.RegisterTile(54, 65); //Bedroom 2 - Picture
    tiles.RegisterTile(55, 66); //Kitchen - inside & out
    tiles.RegisterTile(56, 67); //Bedroom 3 - Panel Right
    tiles.RegisterTile(57, 68); //Bedroom 3 - Panel Left
    tiles.RegisterTile(58, 69); //Kitchen - patio door
    tiles.RegisterTile(59, 70); //Bedroom 3 - Plain
    tiles.RegisterTile(60, 71); //Bedroom 3 - Window
    tiles.RegisterTile(61, 72); //Bedroom 3/3 Door (green key)
    tiles.RegisterTile(62, 73); //Kitchen Refridgerator (half tile)
    tiles.RegisterTile(63, 74); //*Bedroom 3 - Door (stairs down)
    tiles.RegisterTile(64, 75); //*Beige Hall - Stairs up (half tile)
    tiles.RegisterTile(65, 76); //*Beige Hall - Stairs down (half tile)
    tiles.RegisterTile(66, 77); //*Beige Hall - Stairs up and down
    tiles.RegisterTile(67, 78); //*Beige Hall - Stairs down and up
    tiles.RegisterTile(68, 79); //Bedroom 4 - Curtain
    tiles.RegisterTile(69, 80); //Bedroom 4 - Plain
    tiles.RegisterTile(70, 81); //Bedroom 4 - Window
    tiles.RegisterTile(71, 82); //Attic - Plain
    tiles.RegisterTile(72, 83); //Attic - Target
    tiles.RegisterTile(73, 84); //Attic - Mice,Spider
    tiles.RegisterTile(74, 85); //Attic - Boxes, Mouse
    tiles.RegisterTile(75, 86); //Attic - Window
    tiles.RegisterTile(76, 87); //Attic - Clothing
    tiles.RegisterTile(77, 88); //Attic - Trunk
    tiles.RegisterTile(78, 89); //Living Room - Large Picture
    tiles.RegisterTile(79, 90); //Dining Room - Small Bookcase
    tiles.RegisterTile(80, 91); //Cemetery - Plain
    tiles.RegisterTile(81, 92); //Cemetery - Gargoyle

    

    //Dining Room curtains
    tiles.RegisterTile(11, 9);
    tiles.RegisterTile(112, 9);
    tiles.RegisterTile(113, 9);

    

    tiles.RegisterTile(114, 13);

   
}
Player* player;

//thankfully the map viewer comes with readable text files that have entity names and id's
void SpawnEntity(char id, int x, int y) {
    if (id > 0 && id <= 4) {
        player->SetPosition(x, y);
        return;
    }
    
    
}




int main() {
    RegisterTiles();

    LoadMap(0);
    
    SDL_Init(SDL_INIT_AUDIO);


    SDL_AudioSpec wavSpec;
    SDL_memset(&wavSpec, 0, sizeof(wavSpec)); /* or SDL_zero(want) */

    wavSpec.callback = audioCallback;
    wavSpec.userdata = nullptr;
    wavSpec.format = AUDIO_S16;
    wavSpec.channels = 2;
    wavSpec.samples = 2048;

    if (SDL_OpenAudio(&wavSpec, NULL) < 0)
    {
        fprintf(stderr, "Could not open audio: %s\n", SDL_GetError());
    }

    

    Mix_OpenAudioDevice(10989, AUDIO_U8, 1, 2048, SDL_GetAudioDeviceName(0, 0), 1);
   
    Datreader snd("SND.DAT");
    Datreader uif("UIF.DAT");

        
    Music::PlaySong(7, snd, -1);
    
    
    
 
    
    Map map("MAP.1");
    
    

   
    


    


	Camera* c = new Camera();
	
	
    img.Init("GAME.PAL", "IMG.1");
	
	memset(pixels, 255, ray_w * ray_h * sizeof(Uint32));

	SDL_Event event;
	SDL_RenderSetLogicalSize(renderer, 320, 240);
    
	player = new Player(0, 0, c, map, &snd);
    
    int j = 0;
    int x = 0, y = 0;
    for (int i = 0; i < 64 * 64 * 2; i++) {

        if (i % 2 == 0) {
            maptiles[j] = mapbuff[i];
            j++;


        }
        else {
            SpawnEntity(mapbuff[i], x, y);
            x++;
            if (x == 64) {
                x = 0;
                y++;
            }
        }



    }
	while (open) {
        Uint64 start = SDL_GetPerformanceCounter();
        frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
            
		}
		SDL_RenderClear(renderer);
		
		ClearScreen();
		

        for (int x = 0; x < ray_w; x++)
        {
            //calculate ray position and direction
            float cameraX = 2 * x / float(ray_w) - 1; //x-coordinate in camera space
            float rayDirX = player->dirX + c->planeX * cameraX;
            float rayDirY = player->dirY + c->planeY * cameraX;
            //which box of the map we're in

            int mapX = player->GetTilePosition().x;//int(posX);
            int mapY = player->GetTilePosition().y;//int(posY);

            //length of ray from current position to next x or y-side
            float sideDistX;
            float sideDistY;

            //length of ray from one x or y-side to next x or y-side
            float deltaDistX = std::abs(1 / rayDirX);
            float deltaDistY = std::abs(1 / rayDirY);
            float perpWallDist;

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
                int wall = maptiles[mapX + mapY * 64];
                texture = wall;
              
                
                
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
                DrawPixel(x, y, GetPixel(img[tiles.GetTile(texture).texture], texY, texX));
            }

            
            
           


        }





        //deltaTime stuff
        oldTime = time;
        time = SDL_GetTicks();
        
        float frameTime = (time - oldTime) / 1000.0; 

        if (fpsDelay > frameTime) {
            SDL_Delay(fpsDelay - frameTime);
        }

        Uint64 end = SDL_GetPerformanceCounter();

        const Uint8* state = SDL_GetKeyboardState(NULL);
 

        player->Update(frameTime);

       
        


        

        

        
        Draw2DSprite(img[700], 160, 100);
        

     

		SDL_UpdateTexture(canvas, NULL, pixels, ray_w * sizeof(Uint32));
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderCopy(renderer, canvas, NULL, NULL);
        SDL_RenderPresent(renderer);
        


      
        
		

	}

    return 0;
}