/*
 * Weltraum.cpp
 *
 *  Created on: 16.06.2017
 *      Author: sahel03_bk7
 */
#include <SDL.h>
#include <SDL_image.h>

class Sterne {
  public:
	// Eigenschaften (Variablen)
	SDL_Surface *bild;
	int position;

    // Methoden (Funktionen)
	void bewegen() {
		if (position > -800){
			position = position-1;
		}
		else{
			position = position + 800 - 1;
		}
	}
	void zeichnen(SDL_Surface *hg, SDL_Surface *surf) {

	 SDL_Rect source;
	 SDL_Rect dest;
	 source = {x: 0, y: 0, w:800, h:600};
	 dest = {x: position, y: 0, w:800, h:600};
	 SDL_BlitSurface(hg, NULL, surf, NULL);
	 SDL_BlitSurface(bild, &source, surf, &dest);
	 dest = {x: position+800, y: 0, w:800, h:600};
	 SDL_BlitSurface(bild, &source, surf, &dest);
	}

};

class Raumschiff {
public:
	// Attribute
	SDL_Surface *bild;
	int grenzen [2];
	int xpos;
	int ypos;
	int tempo;

	// Methoden
	void zeichnen(SDL_Surface *src, SDL_Surface *surf){

		 SDL_Rect source;
		 SDL_Rect dest;
		 source = {x: 0, y: 0, w:33, h:28};
		 dest = {x: xpos, y: ypos, w:33, h:28};
		 //SDL_BlitSurface(src, NULL, surf, NULL);
		 SDL_BlitSurface(bild, &source, surf, &dest);
		 //dest = {x: x1-33, y: y1-28, w:33, h:28};
		 //SDL_BlitSurface(bild, &source, surf, &dest);

	};

	void bewegen(int richtung){
		switch (richtung){
		case 1:
			if (ypos > 0){
				ypos -= tempo;
			}
			break;
		case 2:
			if (xpos + 33 < grenzen[0]){
				xpos += tempo;
			}
			break;
		case 3:
			if (ypos + 28< grenzen[1]){
				ypos += tempo;
			}
			break;
		case 4:
			if (xpos > 0){
				xpos -= tempo;
			}
			break;
		}
	}

};

class Meteorit : public Sterne{
public:
	void zeichnenm(SDL_Surface *hg, SDL_Surface *surf) {

	 SDL_Rect source;
	 SDL_Rect dest;
	 source = {x: 0, y: 0, w:800, h:600};
	 dest = {x: position, y: 0, w:800, h:600};
	 SDL_BlitSurface(hg, NULL, surf, NULL);
	 SDL_BlitSurface(bild, &source, surf, &dest);
	 //dest = {x: position+800, y: 0, w:800, h:600};
	 //SDL_BlitSurface(bild, &source, surf, &dest);
	}


};



int main(int a, char* b[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("Raumschiffrennen", 400, 200, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Surface *surf = SDL_GetWindowSurface(win);

    SDL_Init(IMG_INIT_PNG);

    SDL_Surface *hg = IMG_Load("background.png");
    SDL_Surface *sterne1 = IMG_Load("stars2.png");
    SDL_Surface *raumschiff = IMG_Load("raumschiffVorne.png");
    SDL_Surface *gMeteor = IMG_Load("grauerMeteorit.png");

    SDL_Event e;


	// Aufrufen der Objekte

    Sterne s1;
    s1.bild = sterne1;
    s1.position = 0;

    Raumschiff r1;
    r1.bild = raumschiff;
    r1.grenzen[0] = 800;
    r1.grenzen[1] = 600;
    r1.xpos = 50;
    r1.ypos = r1.grenzen[1]/2;
    r1.tempo = 10;

    Meteorit mgrau;
    mgrau.bild = gMeteor;
    mgrau.position = 800;




    s1.zeichnen(sterne1, surf);
    r1.zeichnen(raumschiff, surf);

    for (int x=0; x<30000; x++) {
    	s1.bewegen();
    	s1.zeichnen(hg, surf);
    	//r1.bewegen();
    	mgrau.bewegen();
    	mgrau.zeichnenm(gMeteor,surf);

        if ( SDL_PollEvent( &e ) != 0 ) {
        	switch (e.key.keysym.sym) {
        	            		case SDLK_UP:
        	            			r1.bewegen(1);
        	            			break;
        	            		case SDLK_DOWN:
        	            			r1.bewegen(3);
        	            			break;
        	            		case SDLK_LEFT:
        	            			r1.bewegen(4);
        	            			break;
        	            		case SDLK_RIGHT:
        	            			r1.bewegen(2);
        	            			break;
        	            	}
        }
    	r1.zeichnen(raumschiff, surf);

        SDL_UpdateWindowSurface(win);
        SDL_Delay(2);
    }

    return 0;
}
