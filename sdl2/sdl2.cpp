#include <iostream>
#include <SDL.h>
#include <fstream>
#include <string>
#include "drawingOOP.h"
using namespace std;

SDL_Renderer* renderer;
void Circle::Draw()
{
    cout << "Drawing " << m_name << endl;
	const int32_t diameter = (m_radius * 2);

	int32_t x = (m_radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, m_x + x, m_y - y);
		SDL_RenderDrawPoint(renderer, m_x + x, m_y + y);
		SDL_RenderDrawPoint(renderer, m_x - x, m_y - y);
		SDL_RenderDrawPoint(renderer, m_x - x, m_y + y);
		SDL_RenderDrawPoint(renderer, m_x + y, m_y - x);
		SDL_RenderDrawPoint(renderer, m_x + y, m_y + x);
		SDL_RenderDrawPoint(renderer, m_x - y, m_y - x);
		SDL_RenderDrawPoint(renderer, m_x - y, m_y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void Rectangle::Draw()
{
    cout << "Drawing " << m_name << endl;
    SDL_Rect r;
    r.x = m_x;
    r.y = m_y;
    r.w = m_width;
    r.h = m_height;
    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
    SDL_RenderFillRect(renderer, &r);

}

void Triangle::Draw() {
    cout << "Drawing" << m_name << endl;
    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
		SDL_RenderDrawLine(renderer, m_x, m_y, m_x1, m_x);
		SDL_RenderDrawLine(renderer, m_x2, m_y, m_x1, m_x);
		SDL_RenderDrawLine(renderer, m_x, m_y, m_x2, m_y);
 
}

int main(int argc, char** argv)
{
    bool leftMouseButtonDown = false;
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    Uint32* pixels = new Uint32[800 * 600];
    memset(pixels, 0xff000000, 800 * 600 * sizeof(Uint32));
    
    
    
    
    
    while (!quit)
    {
        
        SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = true;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                //pixels[mouseY * 640 + mouseX] = 0;
            }
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear winow
        SDL_RenderClear(renderer);
        Color color = Color{ 1,2,3,4 };
        vector<Shape*> items;
        Rectangle* rect1 = new Rectangle("First Rectangle", 500, 100, 100, 100, Color{123,123,123,255});
		Triangle* triangle1 = new Triangle("First triangle",0,  200, 100, 200, Color{ 123,123,123,255 });
		Circle* circle = new Circle("first circle", 200, 200, 100, Color{ 123, 123, 123, 255 });
        
        items.push_back(rect1);
		items.push_back(triangle1);
		items.push_back(circle);

        for (Shape* it : items)
        {
            it->Draw();
            delete it;
        }

        items.clear();
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}