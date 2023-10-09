
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

void Filters ();

void loadImage ();
void saveImage ();
void Black_White ();
void Invert_Image ();
void MergeImage ();
void FlipImage ();
void Darken_and_Lighten ();
void Rotate ();
void Shrink ();
void Blur ();
int main()
{
    loadImage();
    Filters();
    saveImage();
    return 0;
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

void Filters() {

    int n_of_filter;

    cout << "Enter number of filter you need :" << '\n'
         << "(1) Black & White Filter " << '\n'
         << "(2) Invert Filter" << '\n'
         << "(3) Merge Filter" << '\n'
         << "(4) Flip Image" << '\n'
         << "(5) Darken and Lighten Filter" << '\n'
         << "(6) Rotate Filter" << '\n'
         << "(9) Shrink Filter" << '\n'
         << "(12) Blur Filter" << '\n';

    cin >> n_of_filter;

    if (n_of_filter == 1)
    {
        Black_White ();
    }
    else if (n_of_filter == 2)
    {
        Invert_Image();
    }
    else if (n_of_filter == 3)
    {
        MergeImage();
    }
    else if (n_of_filter == 4)
    {
        FlipImage();
    }
    else if (n_of_filter == 5)
    {
        Darken_and_Lighten ();
    }
    else if (n_of_filter == 6)
    {
        Rotate ();
    }
    else if (n_of_filter == 9)
    {
        Shrink ();
    }
    else if (n_of_filter == 12)
    {
        Blur ();
    }

}

//--------------------------------------------
//this process make the image black and white only
void Black_White (){
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

void Invert_Image() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            image[i][j] = 255-image[i][j];
        }
    }
}

//--------------------------------------------

void MergeImage() {

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
void FlipImage () {

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

void Darken_and_Lighten () {

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

void Rotate () {

    int copy [SIZE][SIZE],angle;
    cout<<"enter the angle you want to Rotate to eg. (90,180,270) : ";
    cin>>angle;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }

    if (angle==180){

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j]=copy[255-i][255-j];
            }
        }
    }
    else if (angle==270){

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j]=copy[255-j][255-i];
            }
        }
    }
    else if (angle==90){

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j]=copy[j][i];
            }
        }
    }

}

//--------------------------------------------

void Shrink() {

    unsigned char shrinked_image[SIZE][SIZE];
    int shrink_by;

    cout << "shrik by haif (2) or by third (3) or by quarter (4) : ";
    cin >> shrink_by;

    if (shrink_by == 2) {
        int row = 0;
        for (int i = 0; i < SIZE - 1; i += 2) {
            int column = 0;

            for (int j = 0; j < SIZE - 1; j += 2) {

                int sum = 0;
                int counter = 0;

                for (int k = i; k < i + 2; ++k) {
                    for (int l = j; l < j + 2; ++l) {

                        sum += image[k][l];
                        counter++;
                    }
                }

                shrinked_image[row][column] = sum / counter;
                column++;
            }
            row++;
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (i < 127 && j < 127) {
                    image[i][j] = shrinked_image[i][j];
                }

                else {
                    image[i][j] = 255;
                }
            }
        }
    }

    else if (shrink_by == 3) {

        int row = 0;
        for (int i = 0; i < SIZE - 2; i += 3) {
            int column = 0;

            for (int j = 0; j < SIZE - 2; j += 3) {
                int sum = 0;
                int counter = 0;

                for (int k = i; k < i + 3; ++k) {
                    for (int l = j; l < j + 3; ++l) {

                        sum += image[k][l];
                        counter++;
                    }
                }

                shrinked_image[row][column] = sum / counter;
                column++;
            }
            row++;
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (i < 85 && j < 85) {
                    image[i][j] = shrinked_image[i][j];
                } else {
                    image[i][j] = 255;
                }
            }
        }
    }

    else if (shrink_by == 4) {

        int row = 0;
        for (int i = 0; i < SIZE - 3; i += 4) {
            int column = 0;

            for (int j = 0; j < SIZE - 3; j += 4) {
                int sum = 0;
                int counter = 0;

                for (int k = i; k < i + 4; ++k) {
                    for (int l = j; l < j + 4; ++l) {
                        sum += image[k][l];
                        counter++;
                    }
                }

                shrinked_image[row][column] = sum / counter;
                column++;
            }
            row++;
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (i < 64 && j < 64) {
                    image[i][j] = shrinked_image[i][j];
                } else {
                    image[i][j] = 255;
                }
            }
        }
    }
}

void Blur () {

    unsigned char blur_image[SIZE][SIZE];

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum_of_pixels = 0;
            int n_pixels = 0;

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


            blur_image[i][j] = sum_of_pixels / n_pixels;
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = blur_image[i][j];
        }
    }
}

