
/*
 * Student 1 :
 *    name : Yomna Maged ALi
 *    email : yomna1472004@gmail.com
 *    ID : 20221196
 *
 * Student 2 :
 *    name : Rawan Amr Nabil
 *    email : Rawanmontash453@gmail.com
 *    ID : 20221062
 *
 * Student 3 :
 *    name : Tasneem Mamdouh Mansy
 *    email : tasneem.mansy1@gmail.com
 *    ID : 20221041
 *
 * */
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void filters ();

void loadImage ();
void saveImage ();
void black_white ();
void invert_image ();
void merge_image ();
void flip_image ();
void darken_and_lighten ();
void rotate_image ();
void shrink_image ();
void blur_image ();
void option();
void enlarge();
void shuffle();

int main()
{
    loadImage();
    filters();
    option();
    //filters();
    //saveImage();
    return 0;
}
//_________________________________________
void option(){
    while (true) {
        char c_of_option;
        cout<< "if you need save image enter (S)ave , if you need stop edit enter (E)xit and if you need make more edit enter (M)ore :";
        cin >> c_of_option;
        if (c_of_option == 'S') {
            saveImage();
        }
        else if (c_of_option == 'M') {
            char y_or_n;
            cout << "enter (Y)es if you need to edit the same image and (N)o if you need another : ";
            cin >> y_or_n;
            if (y_or_n == 'Y') {
                filters();
            }
            else if(y_or_n=='N'){
                loadImage();
                filters();
            }
        }
        else if(c_of_option=='E'){
            break;
        }
    }
}
//_________________________________________
void loadImage () {
    char imageFileName[100];


    cout << "Enter the source image file name: ";
    cin >> imageFileName;


    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];


    cout << "Enter the target image file name: ";
    cin >> imageFileName;


    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________

void filters() {

    int n_of_filter;

    cout << "Enter number of filter you need :" << '\n'
         << "(1) Black & White Filter " << '\n'
         << "(2) Invert Filter" << '\n'
         << "(3) Merge Filter" << '\n'
         << "(4) Flip Image" << '\n'
         << "(5) Darken and Lighten Filter" << '\n'
         << "(6) rotate_image Filter" << '\n'
         << "(9) shrink_image Filter" << '\n'
         << "(10) shrink_image Filter" << '\n'
         << "(12) blur_image Filter" << '\n';

    cin >> n_of_filter;

    if (n_of_filter == 1)
    {
        black_white();
    }
    else if (n_of_filter == 2)
    {
        invert_image();
    }
    else if (n_of_filter == 3)
    {
        merge_image();
    }
    else if (n_of_filter == 4)
    {
        flip_image();
    }
    else if (n_of_filter == 5)
    {
        darken_and_lighten();
    }
    else if (n_of_filter == 6)
    {
        rotate_image();
    }
    else if (n_of_filter == 8)
    {
        enlarge();
    }
    else if (n_of_filter == 9)
    {
        shrink_image();
    }

    else if (n_of_filter == 10)
    {
        shuffle();
    }
    else if (n_of_filter == 12)
    {
        blur_image();
    }
}

//--------------------------------------------
//this process make the image black and white only
void black_white (){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            //we put the avarge to check if pixel more than 127 to convert to white
            if (image[i][j] > 127)
                image[i][j] = 255;

            //pixel turned to black if it less than 127
            else
                image[i][j] = 0;

        }
    }
}
//--------------------------------------------

void invert_image() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
//change pixel color to opposite degree to invert it
            image[i][j] = 255-image[i][j];
        }
    }
}

//--------------------------------------------

void merge_image() {

//    A variable to store the second image to be merged with the first image
    unsigned char marge_image[SIZE][SIZE];
    char Merged_image[100];

    cout << "Please enter the name of the image file to merge with: ";
    cin >> Merged_image;

//    Read the second image and store it in (marge_image)
    strcat(Merged_image, ".bmp");
    readGSBMP(Merged_image, marge_image);

//    Marge the two image in (image)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (marge_image[i][j] + image[i][j]) / 2;
        }
    }

}

//--------------------------------------------

// flip image (h)orizontly or (v)ertically(v)
void flip_image () {

    cout << "Flip (H)orizontally or (V)ertically ? ";

    char H_or_V; // User enter an charachter to choice the type (H or V)
    cin >> H_or_V;
    if (H_or_V == 'V') //if it vertical we make a loop in half of i and j as a matrix to swap
    {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {

                //we will swap column in the another direction so the same column of the pixel is changing and j still its number
                swap(image[i][j], image[256 - i][j]);

            }
        }
    }

    else if (H_or_V == 'H') //if it horizontal we make a loop in half of j and i as a matrix
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++)
            {

                //we will swap row in the another direction so the same row of the pixel is changing and i still its number
                swap (image[i][j] , image[i][256 - j]);
            }
        }
}

//--------------------------------------------

void darken_and_lighten () {

// Variable to store what the user wants (lighten or darken)
    char d_OR_l;

    cout << "Do you want to (d)arken or (l)ighten? ";
    cin >> d_OR_l;

//    If user choose darken
    if(d_OR_l == 'd')
    {

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

//            Reduce the pixel brightness by half to get closer to zero (black)
                image[i][j] = image[i][j] / 2;
            }
        }
    }
//    If user choose lighten
    if(d_OR_l == 'l')
    {

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

//              Increase the pixel brightness by adding half the desired value to reach 255 (white)
//              to ensure that there will be no overflow after adding
                image[i][j] += (255 - image[i][j]) / 2;

            }
        }
    }

    else
    {
        cout << "Invalid char.";
    }
}

//--------------------------------------------

void rotate_image () {

    int copy [SIZE][SIZE],angle;

    //Make copy from the original image to use it in filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }

    //Take the angle that the user wants to rotate
    cout<<"Rotate (90),(180) or (270) : ";
    cin>>angle;

    if (angle==180){

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
            //Make each pixel in image with the pixel on other side in copy
                image[i][j]=copy[255-i][255-j];
            }
        }
    }

    else if (angle==90){
     // Make each column from left side in image equal each row from above in copy
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j]=copy[j][i];
            }
        }
    }

    else if (angle==270){
         // Make each column from the right side in image equal each row from above in copy
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j]=copy[255-j][255-i];
            }
        }
    }

}

//--------------------------------------------

void shrink_image() {

//  2D array to store the image inside it during shrinking
    unsigned char shrinked_image[SIZE][SIZE];

//  A variable to store inside the type of reduction that the user wants (half, quarter, third)
    int shrink_by;

    cout << "shrik by half (2) or by third (3) or by quarter (4) : ";
    cin >> shrink_by;

//  if the user choose half
    if (shrink_by == 2) {
        int row = 0; // the row we are in
        for (int i = 0; i < SIZE - 1; i += 2) {
            int column = 0; // the column we are in

            for (int j = 0; j < SIZE - 1; j += 2) {

                int sum = 0; //Here the values of the pixels that will be shrinked into one pixel are stored
                int counter = 0; //The number of pixels to be shrinked (and in this case will be 4)

                for (int k = i; k < i + 2; ++k) {
                    for (int l = j; l < j + 2; ++l) {

                        sum += image[k][l];
                        counter++;
                    }
                }

                shrinked_image[row][column] = sum / counter; // The sum of the pixel valuse is divided by their number to get the average
                column++; // Move to the next column
            }
            row++; // Move to the next row
        }

//      move the image in (shrinked_image) to (image) to be displayed
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

//              Because we are reducing by half, all pixels will be present from (0,0) until (127,127)
                if (i < 127 && j < 127) {
                    image[i][j] = shrinked_image[i][j];
                }

//              otherwise , white pixels will apper
                else {
                    image[i][j] = 255;
                }
            }
        }
    }

//  if the user choose third
    else if (shrink_by == 3) {

        int row = 0; // the row we are in
        for (int i = 0; i < SIZE - 2; i += 3) {
            int column = 0; // the column we are in

            for (int j = 0; j < SIZE - 2; j += 3) {

                int sum = 0; //Here the values of the pixels that will be shrinked into one pixel are stored
                int counter = 0; //The number of pixels to be shrinked (and in this case will be 9);

                for (int k = i; k < i + 3; ++k) {
                    for (int l = j; l < j + 3; ++l) {

                        sum += image[k][l];
                        counter++;
                    }
                }

                shrinked_image[row][column] = sum / counter; // The sum of the pixel valuse is divided by their number to get the average
                column++; // Move to the next column
            }
            row++; // Move to the next row
        }

//      move the image in (shrinked_image) to (image) to be displayed
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

//              Because we are reducing by half, all pixels will be present from (0,0) until (85,85)
                if (i < 85 && j < 85) {
                    image[i][j] = shrinked_image[i][j];
                }

//              otherwise , white pixels will apper
                else {
                    image[i][j] = 255;
                }
            }
        }
    }

//  if the user choose quarter
    else if (shrink_by == 4) {

        int row = 0; // the row we are in
        for (int i = 0; i < SIZE - 3; i += 4) {
            int column = 0; // the column we are in

            for (int j = 0; j < SIZE - 3; j += 4) {
                int sum = 0; //Here the sum of the values of the pixels that will be shrinked into one pixel are stored
                int counter = 0; //The number of pixels to be shrinked (and in this case will be 16);

                for (int k = i; k < i + 4; ++k) {
                    for (int l = j; l < j + 4; ++l) {
                        sum += image[k][l];
                        counter++;
                    }
                }

                shrinked_image[row][column] = sum / counter; // The sum of the pixel valuse is divided by their number to get the average
                column++; // Move to the next column
            }
            row++; // Move to the next row
        }

//      move the image in (shrinked_image) to (image) to be displayed
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

//              Because we are reducing by half, all pixels will be present from (0,0) until (64,64)
                if (i < 64 && j < 64) {
                    image[i][j] = shrinked_image[i][j];
                }

//              otherwise , white pixels will apper
                else {
                    image[i][j] = 255;
                }
            }
        }
    }
}

void blur_image () {

//  2D array to store the image inside it during process of blurring
    unsigned char blur_image[SIZE][SIZE];

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum_of_pixels = 0; //Here the sum of the values of the pixels that around the pixel needed to blur are stored
            int n_pixels = 0; //The number of pixels around the desired pixel

//          We pass through a certain number of rows and columns around the pixels that we want to blur to get their values
//          This number can be change depending on the desired degree of blurring (reduce it to reduce blur and vice versa)
            for (int x = -3; x <= 3; ++x) {
                for (int y = -3; y <= 3; ++y) {
                    int row_of_pixel = i + x;
                    int column_of_pixel = j + y;


                    if (row_of_pixel >= 0 && row_of_pixel < SIZE && column_of_pixel >= 0 && column_of_pixel < SIZE) {
                        sum_of_pixels += image[row_of_pixel][column_of_pixel];
                        n_pixels++;
                    }
                }
            }


            blur_image[i][j] = sum_of_pixels / n_pixels; // The sum of the pixel valuse is divided by their number to get the average
        }
    }

//  move the image in (blur_image) to (image) to be displayed
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = blur_image[i][j];
        }
    }
}
//--------------------------------------------
void shuffle_Filter(){

    int copy [SIZE][SIZE],operation;

    //Make copy from the original image to use it in filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }
    cout <<"New order of quarters : ";
    for (int k=1;k<=4;k++) {
        int row ,column;
        cin >> operation;
        if (k==1){
            column=0;
            row=0;
        }
        else if (k==2){
            column=127;
            row=0;
        }
        else if (k==3){
            column=0;
            row=127;
        }
        else if (k==4){
            column= 127;
            row=127;
        }
        int copy_x=column;
        if (operation == 1) {
            for (int i = 0; i < 127; i++) {
                column=copy_x;
                for (int j = 0; j < 127; j++) {
                    image[row][column] = copy[i][j];
                    column++;

                }
                row++;

            }

        } else if (operation == 2) {

            for (int i = 0; i < 127; i++) {
                column=copy_x;
                for (int j = 127; j < SIZE; j++) {
                    image[row][column] = copy[i][j];
                    column++;
                }
                row++;
            }
        } else if (operation == 3) {
            for (int i = 127; i < SIZE; i++) {
                column=copy_x;
                for (int j = 0; j < 127; j++) {

                    image[row][column] = copy[i][j];
                    column++;
                }
                row++;
            }
        } else if (operation == 4) {
            for (int i = 127; i < SIZE; i++) {
                column=copy_x;
                for (int j = 127; j < SIZE; j++) {

                    image[row][column] = copy[i][j];

                    column++;
                }
                row++;
            }
        }
    }

}
//--------------------------------------------
void enlarge(){

    int copy [SIZE][SIZE],operation;

    //Make copy from the original image to use it in filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }
    cout<<"Which quarter to enlarge 1 ,2,3 or 4 ? "<<'\n';
    cin >> operation;
    int row=0;
    if(operation == 1){
        for (int i = 0; i < 128; i++) {
            int column=0;
            for (int j = 0; j < 128; j++) {

                image[1 + row][column]= copy[i][j] ;
                image[row][1 + column]= copy[i][j] ;
                image[row][column]= copy[i][j] ;
                image[1 + row][1 + column]= copy[i][j] ;
                column++;column++;
            }
            row++;row++;
        }

    }
    else if (operation == 2){
        for (int i = 0; i < 128; i++) {
            int x=0;
            for (int j = 128; j < SIZE; j++) {

                image[1 + row][x]= copy[i][j] ;
                image[row][1 + x]= copy[i][j] ;
                image[row][x]= copy[i][j] ;
                image[1 + row][1 + x]= copy[i][j] ;
                x++;x++;
            }
            row++;row++;
        }
    }
    else if(operation == 3){
        for (int i = 128; i < SIZE; i++) {
            int x=0;
            for (int j = 0; j < 128; j++) {

                image[1 + row][x]= copy[i][j] ;
                image[row][1 + x]= copy[i][j] ;
                image[row][x]= copy[i][j] ;
                image[1 + row][1 + x]= copy[i][j] ;
                x++;x++;
            }
            row++;row++;
        }
    }
    else if(operation == 4){
        for (int i = 128; i < SIZE; i++) {
            int x=0;
            for (int j = 128; j < SIZE; j++) {

                image[1 + row][x]= copy[i][j] ;
                image[row][1 + x]= copy[i][j] ;
                image[row][x]= copy[i][j] ;
                image[1 + row][1 + x]= copy[i][j] ;
                x++;x++;
            }
            row++;row++;
        }
    }

}
//--------------------------------------------