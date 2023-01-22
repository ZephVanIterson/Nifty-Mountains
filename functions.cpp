//Zeph Van Iterson February-2020
//Nifty Mountains Asignment
//This program reads in a text file of integrers into a matrix, then it draws an elevation map using those numbers as elevations
//Fiinally, it draws paths for each possible starting position using a chosen pathing algorithm
//Greedy path always choposes the elevation closest to thye current elevartion
//Lowest path always chooses the lowest elevation

//Extensions:
    //Elevation map goes from red to blue instead of black to white
    //Users can choose they always go down pathing algorithm


#include "header.h"

//Reads in a file to a matrix
void readFile(apmatrix<int> &matrix, ifstream &file) {

    for(int i = 0; i<height; i++) {
        for(int k = 0; k<width; k++) {
            file>>matrix[i][k];
        }
    }
}

//Calculates the highest value conatined in a matrix
int calcMax(const apmatrix<int> &matrix) {
    int maximum = matrix[0][0];

    for(int i = 0; i<height; i++) {
        for(int k = 0; k<width; k++) {
            if(matrix[i][k]>maximum)
                maximum = matrix[i][k];
        }
    }

    return maximum;
}

//Calculates the lowest value conatined in a matrix
int calcMin(const apmatrix<int> &matrix) {
    int minimum = matrix[0][0];

    for(int i = 0; i<height; i++) {
        for(int k = 0; k<width; k++) {
            if(matrix[i][k]<minimum)
                minimum = matrix[i][k];
        }
    }

    return minimum;
}

//Initalizes Allegro and includes primitives
int initializeAllegro() {

    // Initialize Allegro
    al_init();
    al_init_primitives_addon();

    return 0;
}

//Checks that allegro and display are working
int checkAllegro(ALLEGRO_DISPLAY *display) {

    // Initialize Allegro

    //check integrity
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primitive add on
    //check integrity
    if (!al_init_primitives_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_set_window_title(display, "Nifty Mountains");

    return 0;
}

//Generates a coloured elevation map using a matrix of elevations
int generateMap(int maximum, int minimum, const apmatrix<int> &matrix) {
    int range = maximum - minimum;
    ALLEGRO_COLOR shade;
    float scaleShade = 0;

    for(int i = 0; i<height; i++) {
        for(int k = 0; k<width; k++) {

            scaleShade = matrix[i][k];
            scaleShade -= minimum;
            scaleShade /= range;
            scaleShade *= 255;

            shade = al_map_rgb(scaleShade, 0, 255-scaleShade);

            al_draw_pixel(k, i, shade);
        }
    }

    return 0;
}

//Finds the position directly ahead with the closest elevation to the current elevation and draws a black pixel there(moves hiker to that position)
int moveOnce(int &x, int &y, const apmatrix<int> &matrix ) {

    int upperPath = 0;
    int middlePath = 0;
    int lowerPath = 0;

    middlePath = abs(matrix[y][x] - matrix[y][x+1]);

    if(y<=0) {
        lowerPath = abs(matrix[y][x] - matrix[y+1][x+1]);
        upperPath = lowerPath + middlePath;
    } else if(y>=479) {
        upperPath = abs(matrix[y][x] - matrix[y-1][x+1]);
        lowerPath = middlePath + upperPath;
    } else {
        upperPath = abs(matrix[y][x] - matrix[y-1][x+1]);
        lowerPath = abs(matrix[y][x] - matrix[y+1][x+1]);
    }

    x++;

    if(upperPath < middlePath && upperPath < lowerPath) {
        y--;
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return upperPath;
    } else if(middlePath < upperPath && middlePath < lowerPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return middlePath;
    } else if(lowerPath < upperPath && lowerPath < middlePath) {
        y++;
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return lowerPath;
    } else if(upperPath == middlePath && upperPath < lowerPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return middlePath;
    } else if(upperPath == lowerPath && upperPath < middlePath) {
        if(flipCoin() == true) {
            y--;
            al_draw_pixel(x, y, al_map_rgb(0,0,0));
            return upperPath;
        } else {
            y++;
            al_draw_pixel(x, y, al_map_rgb(0,0,0));
            return lowerPath;
        }

    } else if(lowerPath == middlePath && lowerPath < upperPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return middlePath;
    } else if(lowerPath == middlePath && lowerPath == upperPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return middlePath;
    }

    return 0;
}

//Has a 50% chance of returning true and a 50% chance of returning false
bool flipCoin() {

    int result = rand() % 2;

    switch(result) {
    case 0:
        return true;
        break;
    case 1:
        return false;
        break;
    default:
        cout<<"Coin Error!"<<endl;
        return false;
        break;
    }
}

////Finds the position directly ahead with the closest elevation to the current elevation and draws a green ixel there(same as moveOnce but using a diffeent colour)
int drawLowestElevPath(int &x, int &y, const apmatrix<int> &matrix ) {

    int upperPath = 0;
    int middlePath = 0;
    int lowerPath = 0;

    middlePath = abs(matrix[y][x] - matrix[y][x+1]);

    if(y<=0) {
        lowerPath = abs(matrix[y][x] - matrix[y+1][x+1]);
        upperPath = lowerPath + middlePath;
    } else if(y>=479) {
        upperPath = abs(matrix[y][x] - matrix[y-1][x+1]);
        lowerPath = middlePath + upperPath;
    } else {
        upperPath = abs(matrix[y][x] - matrix[y-1][x+1]);
        lowerPath = abs(matrix[y][x] - matrix[y+1][x+1]);
    }

    x++;

    if(upperPath < middlePath && upperPath < lowerPath) {
        y--;

    } else if(middlePath < upperPath && middlePath < lowerPath) {

    } else if(lowerPath < upperPath && lowerPath < middlePath) {
        y++;

    } else if(upperPath == middlePath && upperPath < lowerPath) {

    } else if(upperPath == lowerPath && upperPath < middlePath) {

        if(flipCoin() == true) {
            y--;
        } else {
            y++;
        }

    } else if(lowerPath == middlePath && lowerPath < upperPath) {

    } else if(lowerPath == middlePath && lowerPath == upperPath) {

    }

    al_draw_pixel(x, y, al_map_rgb(0,255,0));
    return 0;
}

//Finds the position directly ahead with the lowest elevation and draws a black pixel there(moves hiker to that position)
int moveOnce2(int &x, int &y, const apmatrix<int> &matrix ) {

    int upperPath = 0;
    int middlePath = 0;
    int lowerPath = 0;

    middlePath = matrix[y][x] - matrix[y][x+1];

    if(y<=0) {
        lowerPath = matrix[y][x] - matrix[y+1][x+1];
        upperPath = abs(lowerPath) + abs(middlePath);
    } else if(y>=479) {
        upperPath = matrix[y][x] - matrix[y-1][x+1];
        lowerPath = abs(middlePath) + abs(upperPath);
    } else {
        upperPath = matrix[y][x] - matrix[y-1][x+1];
        lowerPath = matrix[y][x] - matrix[y+1][x+1];
    }

    x++;

    if(upperPath < middlePath && upperPath < lowerPath) {
        y--;
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return abs(upperPath);
    } else if(middlePath < upperPath && middlePath < lowerPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return abs(middlePath);
    } else if(lowerPath < upperPath && lowerPath < middlePath) {
        y++;
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return abs(lowerPath);
    } else if(upperPath == middlePath && upperPath < lowerPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return abs(middlePath);
    } else if(upperPath == lowerPath && upperPath < middlePath) {

        if(flipCoin() == true) {
            y--;
            al_draw_pixel(x, y, al_map_rgb(0,0,0));
            return abs(upperPath);
        } else {
            y++;
            al_draw_pixel(x, y, al_map_rgb(0,0,0));
            return abs(lowerPath);
        }

    } else if(lowerPath == middlePath && lowerPath < upperPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return abs(middlePath);
    } else if(lowerPath == middlePath && lowerPath == upperPath) {
        al_draw_pixel(x, y, al_map_rgb(0,0,0));
        return abs(middlePath);
    }

    return 0;
}


