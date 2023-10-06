// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char marge_image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void BW ();
//void  Invert_Image();
//void MergeImage ();
void Darken_and_Lighten_Image ();
void Blur ();

int main()
{
    loadImage();
//    BW();
//    Invert_Image();
//    MergeImage();
//    Darken_and_Lighten_Image();
    Blur ();
    saveImage();
    return 0;
}

//_________________________________________
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
//void  Invert_Image() {
//    for (int i = 0; i < SIZE; i++) {
//        for (int j = 0; j< SIZE; j++) {
//            if (image[i][j]==0){
//                image[i][j]=255;
//            }
//            else if (image[i][j]==255){
//                image[i][j]=0;
//            }
//            else{
//                image[i][j]=255-image[i][j];
//            }
//        }
//    }
//}

void BW () {

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {

            if(image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
void MergeImage() {
    char second_imageFileName[100];

    cout << "Please enter the name of the image file to merge with: ";
    cin >> second_imageFileName;

    strcat(second_imageFileName, ".bmp");
    readGSBMP(second_imageFileName, marge_image);

    // Attempt to load the second image
//    if (!readGSBMP(second_imageFileName, marge_image)) {
//        cout << "Error loading the second image." << endl;
//        return;
//    }

    // Check if the dimensions of the two images match
//    if (marge_image.size() != SIZE || marge_image[0].size() != SIZE) {
//        cout << "Image dimensions do not match. Cannot merge." << endl;
//        return;
//    }

    // Merge the images by calculating the average pixel value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (marge_image[i][j] + image[i][j]) / 2;
        }
    }

    // Optionally, you can save or display the merged image here.
}

void Darken_and_Lighten_Image () {

    char d_OR_l;

    cout << "Do you want to (d)arken or (l)ighten? ";
    cin >> d_OR_l;


    if(d_OR_l == 'd')
    {

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                image[i][j] = image[i][j] / 2;
//                image[i][j] -= image[i][j] / (10/7);
            }
        }
    }

    if(d_OR_l == 'l')
    {

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

//                image[i][j] -= 255;
                image[i][j] += (255 - image[i][j]) / 2;

            }
        }
    }

    else
    {
        cout << "Invalid char.";
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
                    int ni = i + x;
                    int nj = j + y;


                    if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE) {
                        sum_of_pixels += image[ni][nj];
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




//    unsigned char blur_image[SIZE][SIZE] = {'0'};
//
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//
//            if(i == 0 && j == 0)
//            {
//                unsigned char Xright_corner [] = { '0' ,'0' , '1' , '1' , '0' , '1' , '2' , '2' , '2' };
//                unsigned char Yright_corner [] = { '0' ,'1' , '1' , '0' , '2' , '2' , '2' , '1' , '0' };
//
//                for (int k = 0; k < 9; ++k)
//
//                    blur_image[i][j] += image[i + Xright_corner][j + Yright_corner];
//
//
//                blur_image[i][j] /= 9;
////                blur_image[i][j] = (image[i][j] + image[i][j+1] + image[i+1][j] + image[i+1][j+1]) / 4;
//            }
//            else if (i == 0 && j == 254)
//            {
//                int Xright_corner [] = { 0 ,0 , 1 , 1 , 0 , 1 , 2 , 2 , 2 };
//                int Yright_corner [] = { 0 ,-1 , -1 , 0 , -2 , -2 , -2 , -1 , 0 };
//
//
//                blur_image[i][j] = (image[i][j] + image[i][j-1] + image[i+1][j] + image[i+1][j-1]) / 4;
//            }
//            else if (i == 254 && j == 0)
//            {
//                blur_image[i][j] = (image[i][j] + image[i][j+1] + image[i-1][j] + image[i-1][j+1]) / 4;
//
//            }
//            else if (i == 254 && j == 254)
//            {
//                blur_image[i][j] = (image[i][j] + image[i][j-1] + image[i-1][j] + image[i-1][j-1]) / 4;
//
//            }
//
//            else if (i == 0 && j > 0 && j < 254)
//            {
//                blur_image[i][j] = (image[i][j] + image[i][j-1]  + image[i][j+1] + image[i+1][j-1] + image[i+1][j] + image[i+1][j+1]) / 6;
//
//            }
//            else if (i == 254 && j > 0 && j < 254)
//            {
//                blur_image[i][j] = (image[i][j] + image[i][j-1]  + image[i][j+1] + image[i-1][j-1] + image[i-1][j] + image[i-1][j+1]) / 6;
//
//            }
//            else if (j == 0 && i > 0 && i < 254)
//            {
//                blur_image[i][j] = (image[i][j] + image[i-1][j]  + image[i+1][j] + image[i-1][j+1] + image[i][j+1] + image[i+1][j+1]) / 6;
//
//            }
//            else if (j== 254 && i > 0 && i < 254)
//            {
//                blur_image[i][j] = (image[i][j] + image[i-1][j]  + image[i+1][j] + image[i-1][j-1] + image[i][j-1] + image[i+1][j-1]) / 6;
//
//            }
//            else
//            {
//                blur_image[i][j] = (image[i][j] + image[i-1][j-1] + image[i-1][j] + image[i-1][j+1] + image[i][j-1] + image[i][j+1] + image[i+1][j-1] + image[i+1][j] + image[i+1][j+1]) / 9;
//            }
//        }
//    }
//
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//
//            image[i][j] = blur_image[i][j];
//        }
//    }
}