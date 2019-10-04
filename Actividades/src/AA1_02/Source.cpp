#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

#include "Types.h"

bool hover = false;

Vec2 mouse;
Vec2 mouse_click;



int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if(TTF_Init()==-1) throw "No es pot inicialitzar SDL_ttf";

	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 };
	if (!(Mix_Init(mixFlags)& mixFlags)) throw "Error amb SDL_Mixer init";

	// --- SPRITES ---


		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//Mouse
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "No s'ha pogut crear la textura";
	SDL_Rect playerRect{ 0, 0, 100, 70 };

	//-->Animated Sprite ---


	// --- TEXT ---
	//Cargar font
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";

	// Crear Surface
	SDL_Surface *tmpSurf {TTF_RenderText_Blended(font, "Play",SDL_Color{255,150,0,255})};
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";

	//Crear Text_1 Play
	SDL_Texture *textTexture1 { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Rect textRect1{ 350,100, tmpSurf->w, tmpSurf->h };

	//Crear TextHover Play
	tmpSurf = { TTF_RenderText_Blended(font, "Play",SDL_Color{0,100,255,255}) };
	SDL_Texture *textTexture2{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

	//Crear Text_2 Sound
	tmpSurf = { TTF_RenderText_Blended(font, "Sound Toggle",SDL_Color{255,150,0,255}) };
	SDL_Texture *textTexture3{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Rect textRect2{ 225,200, tmpSurf->w, tmpSurf->h };

	//Crear Text_3 Exit
	tmpSurf = { TTF_RenderText_Blended(font, "Quit",SDL_Color{255,150,0,255}) };
	SDL_Texture *textTexture4{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Rect textRect3{ 340,300, tmpSurf->w, tmpSurf->h };

	// Netejar
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);

	// --- AUDIO --- 

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable to initialize SDL Mixer audio system";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	// --- GAME LOOP ---

	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				mouse.x = event.motion.x;
				mouse.y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN: 
				mouse_click.x = event.motion.x;
				mouse_click.y = event.motion.y;
				break;
			default:;
			}
		}

		// UPDATE
		playerRect.x += (mouse.x - playerRect.x - playerRect.w/2) / 10;
		playerRect.y += (mouse.y - playerRect.y - playerRect.h/2) / 10;

		//sortir
		if (collision(mouse_click, textRect3)) {
			isRunning = false;
		}

		//play/pause
		if (collision(mouse_click, textRect2)) {
			if (Mix_PausedMusic() == 1 )
			{
				Mix_ResumeMusic();
			}
			else
			{
				Mix_PauseMusic();
			}
		}

		//Hover
		if (collision(mouse, textRect1)) {
			bool hover = true;
		}
		else {
			false;
		}

		// DRAW

		SDL_RenderClear(m_renderer);

		//Background

		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		//Fonts
		if (hover) {
			SDL_RenderCopy(m_renderer, textTexture2, nullptr, &textRect1);
		}
		else {
			SDL_RenderCopy(m_renderer, textTexture1, nullptr, &textRect1);
		};
		SDL_RenderCopy(m_renderer, textTexture3, nullptr, &textRect2);
		SDL_RenderCopy(m_renderer, textTexture4, nullptr, &textRect3);
		
		//Mouse
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);

		SDL_RenderPresent(m_renderer);
	}

	// --- DESTROY ---

	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(textTexture3);
	SDL_DestroyTexture(textTexture4);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}