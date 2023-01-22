//Zeph Van Iterson February-2020
//Nifty Mountains Asignment
//This program reads in a text file of integrers into a matrix, then it draws an elevation map using those numbers as elevations
//Fiinally, it draws paths for each possible starting position using a chosen pathing algorithm
//Greedy path always choposes the elevation closest to thye current elevartion
//Lowest path always chooses the lowest elevation

//Extensions:
    //Elevation map goes from red to blue instead of black to white
    //Users can choose they always go down pathing algorithm

#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<apmatrix.h>
#include <windows.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include<stdlib.h>
#include<math.h>

using namespace std;

const int height = 480;
const int width = 844;

void readFile(apmatrix<int> &matrix, ifstream &file);
int calcMin(const apmatrix<int> &matrix);
int calcMax(const apmatrix<int> &matrix);
int initializeAllegro();
int generateMap(int maximum, int minimum, const apmatrix<int> &matrix);
int checkAllegro(ALLEGRO_DISPLAY *display);
bool flipCoin();
int moveOnce(int &x, int &y, const apmatrix<int> &matrix );
int drawLowestElevPath(int &x, int &y, const apmatrix<int> &matrix);
int moveOnce2(int &x, int &y, const apmatrix<int> &matrix );
