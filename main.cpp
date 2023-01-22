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

int main() {

    //Seed random time
    srand(time(0));

    //Declare and initialize variables
    string path;
    int totalElevChange = 0;
    int lowestElevChange = 100000000;
    int bestStart = 0;
    int x = 0;
    int y = 0;
    int minimum = 0;
    int maximum = 0;
    apmatrix<int> elevationMap(height, width);

    //Open file
    ifstream inputFile("Colorado.dat");

    //Call function to read file into a matrix
    readFile(elevationMap, inputFile);

    //close file
    inputFile.close();

    //Call functions to calculate the maximum and minimum values
    minimum = calcMin(elevationMap); //1010
    maximum = calcMax(elevationMap); //4334

    //Print out the maximum and minimum values
    cout<<"Minimum is "<<minimum<<endl;
    cout<<"Maximum is "<<maximum<<endl;

    //Ask the user which path algorithm to use
    cout<<"Would you like to see greedy paths or lowest paths? "<<endl;
    cout<<"Enter the word 'greedy' or the word 'lowest'"<<endl;
    cin>>path;

    //Print out legend
    cout<<endl<<"LEGEND"<<endl;
    cout<<"------"<<endl;
    cout<<"Black lines are paths"<<endl;
    cout<<"Green line is the path with the least total change in elevation"<<endl<<endl;

    //Initialize allegro and create display
    initializeAllegro();
    ALLEGRO_DISPLAY *display = al_create_display(width, height);
    checkAllegro(display);

    //Generate the map from the matrix
    generateMap(maximum, minimum, elevationMap);
    al_flip_display();

    //Call functions to draw the path chosen by the user
    if(path == "greedy") {
        //greedy path
        for(int i=0; i<height-1; i++) {
            x=0;
            y=i;
            totalElevChange = 0;
            while(x<=width-2) {
                totalElevChange += moveOnce(x, y, elevationMap);
            }
            al_flip_display();
            if(lowestElevChange > totalElevChange) {
                lowestElevChange = totalElevChange;
                bestStart = y;
            }
        }
    } else if(path == "lowest") {
        //lowest path
        for(int i=0; i<height-1; i++) {
            x=0;
            y=i;
            totalElevChange = 0;
            while(x<=width-2) {
                totalElevChange += moveOnce2(x, y, elevationMap);
            }
            al_flip_display();
            if(lowestElevChange > totalElevChange) {
                lowestElevChange = totalElevChange;
                bestStart = y;
            }
        }
    }


    x=0;
    y=bestStart;

    //Draw the path with the least change in elevation in a different colour
    for(int k = 0; k<width-1; k++) {
        drawLowestElevPath(x, y, elevationMap);
    }
    al_flip_display();

    //tells the user the best path
    cout<<"The path that has the least total change in elevation starts at "<<bestStart;
    cout<<" and has a total change in elevation of "<<lowestElevChange<<endl;

    al_rest(20);

    al_destroy_display(display);

    return 0;

}


