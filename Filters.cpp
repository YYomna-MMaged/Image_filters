

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
unsigned char cropimage[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
void menu ();

void loadImage ();
void saveImage ();
void option ();
void black_white ();
void invert ();
void merge ();
void flip ();
void darken_and_lighten ();
void rotate ();
void detect();
void shrink ();
void mirror();
void blur ();
void enlarge();
void shuffle();
void crop();
void skew_right();
void skew_up ();

int main()
{
    loadImage();
    menu();
    return 0;
}
//_______________

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

void menu() {

    char n_of_filter;
    while (n_of_filter != '0') {
        cout << "Enter number of filter you need :" << '\n'
             << "(1) Black & White image Filter " << '\n'
             << "(2) Invert image Filter" << '\n'
             << "(3) Merge image Filter" << '\n'
             << "(4) Flip image Filter" << '\n'
             << "(5) Darken and Lighten image Filter" << '\n'
             << "(6) Rotate image Filter" << '\n'
             << "(7) Detect image Filter" << '\n'
             << "(8) enlarge image Filter" << '\n'
             << "(9) Shrink image Filter" << '\n'
             << "(a) Mirror 1/2 image Filter" << '\n'
             << "(b) Shuffle image Filter" << '\n'
             << "(c) Blur image Filter" << '\n'
             << "(d) Crop image Filter" << '\n'
             << "(e) Skew horizontal image Filter" << '\n'
             << "(f) Skew vertical image Filter" << '\n'
             << "(s) Save the image to a file" << '\n'
             << "(0) Exit" << '\n';

        cin >> n_of_filter;

        if (n_of_filter == '1') {
            black_white();
        } else if (n_of_filter == '2') {
            invert();
        } else if (n_of_filter == '3') {
            merge();
        } else if (n_of_filter == '4') {
            flip();
        } else if (n_of_filter == '5') {
            darken_and_lighten();
        } else if (n_of_filter == '6') {
            rotate();
        } else if (n_of_filter == '7') {
            detect();
        } else if (n_of_filter == '8') {
            enlarge();
        } else if (n_of_filter == '9') {
            shrink();
        } else if (n_of_filter == 'a') {
            mirror();
        } else if (n_of_filter == 'b') {
            shuffle();
        } else if (n_of_filter == 'c') {
            blur();
        } else if (n_of_filter == 'd') {
            crop();
        } else if (n_of_filter == 'e') {
            skew_right();
        } else if (n_of_filter == 'f') {
            skew_up();
        } else if (n_of_filter == 's') {
            saveImage();
        } else if (n_of_filter == '0') {
            break;
        }
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

void invert() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
//change pixel color to opposite degree to invert it
            image[i][j] = 255-image[i][j];
        }
    }
}

//--------------------------------------------

void merge() {

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
void flip () {

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

void rotate () {

    int copy [SIZE][SIZE],angle;

    //Make copy from the original image to use it in filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }

    //Take the angle that the user wants to rotate
    cout<<"enter the angle you want to rotate to eg. (90,180,270) : ";
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
    void detect() {
        black_white(); //we call a function we do to turn to black and white to make it easy to compare pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //we compare the pixel with the pixels around it to check if it same to turn to white or black if it differ
                if (image[i][j] != image[i][j - 1] ||  image[i][j] != image[i][j+1] || image[i][j] != image[i +1][j] || image[i][j] != image[i -1][j] || image[i][j] != image[i -1][j-1] || image[i][j] != image[i+1][j+1])
                    image2[i][j]=0;

                else
                    image2[i][j] = 255; // if it doesnt same pixel turned to white
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i][j]; //we transfer the image to the new
            }
        }
    }

//--------------------------------------------
void shrink() {

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
//------------------------------------------------
    void mirror(){
        cout<<"enter the type of mirror do you want left(1) right(2) upper(3) lower(4):  ";
        int type;//we enter an int to choice the type we want to mirror
        cin>>type;
        if (type==1) // we make aloop in i and half of j to copy the left of image
            for (int i =0 ; i <SIZE ; i++) {
                for (int j =SIZE-1 / 2; j >0  ; j--) { // we start with j =SIZE-1/2 to copy the left of image
                    image[i][j] = image[ i][256-j];
                }
            }
        if (type==2)//we make aloop in i and half of j to copy the right of image
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    image[i][j] = image[ i][256-j];
                }
            }
        if (type==3)//if the user choice 3 we make amirror to the upper side
            for (int i =SIZE-1/2 ; i >0; i--) {// we start from the SIZE-1/2 to copy the upper side opsite of lower side
                for (int j = 0; j < SIZE ; j++) {
                    image[i][j] = image[256 - i][j];
                }
            }
        if (type==4)//if the user choice 4 we make amirror to the lower side
            for (int i = 0; i < SIZE/2; i++) {
                for (int j = 0; j < SIZE ; j++) {
                    image[i][j] = image[256 - i][j];
                }
            }
    }

//-------------------------------------------------
void blur () {

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

//  move the image in (blur) to (image) to be displayed
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = blur_image[i][j];
        }
    }
}


//--------------------------------------------
void shuffle (){

    int copy [SIZE][SIZE],operation;

    //Make copy from the original image to use it in filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }
    // made loop to get  four squares
    cout <<"New order of quarters : ";
    for (int k=1;k<=4;k++) {
        int row ,column;
        cin >> operation;
        //make four if condition to determine the border of the square we will copy in
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
        // make another four if to determine witch square user need to copy
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

    int copy [SIZE][SIZE],option;

    //Make copy from the original image to use it in filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            copy[i][j] = image[i][j];
        }
    }
    //take the number of square that user need
    cout<<"Which quarter to enlarge 1 ,2,3 or 4 ? "<<'\n';
    cin >> option;
    int row=0;
    //make four if to each square and make each pixel in the selected square in copy = four pixels in image
    if(option == 1){
        for (int i = 0; i < 128; i++) {
            int column=0;
            for (int j = 0; j < 128; j++) {

                image[1 + row][column]= copy[i][j] ;
                image[row][1 + column]= copy[i][j] ;
                image[row][column]= copy[i][j] ;
                image[1 + row][1 + column]= copy[i][j] ;
                column+=2;
            }
            row+=2;
        }

    }
    else if (option == 2){
        for (int i = 0; i < 128; i++) {
            int column=0;
            for (int j = 128; j < SIZE; j++) {

                image[1 + row][column]= copy[i][j] ;
                image[row][1 + column]= copy[i][j] ;
                image[row][column]= copy[i][j] ;
                image[1 + row][1 + column]= copy[i][j] ;
                column+=2;
            }
            row+=2;
        }
    }
    else if(option == 3){
        for (int i = 128; i < SIZE; i++) {
            int column=0;
            for (int j = 0; j < 128; j++) {

                image[1 + row][column]= copy[i][j] ;
                image[row][1 + column]= copy[i][j] ;
                image[row][column]= copy[i][j] ;
                image[1 + row][1 + column]= copy[i][j] ;
                column+=2;
            }
            row+=2;
        }
    }
    else if(option == 4){
        for (int i = 128; i < SIZE; i++) {
            int column=0;
            for (int j = 128; j < SIZE; j++) {

                image[1 + row][column]= copy[i][j] ;
                image[row][1 + column]= copy[i][j] ;
                image[row][column]= copy[i][j] ;
                image[1 + row][1 + column]= copy[i][j] ;
                column+=2;
            }
            row+=2;
        }
    }

}
//--------------------------------------------
void crop() {
    int x, y, l, w;//

    cout << "please enter the x,y position to cut the image :\n ";
    cin >> x >> y;//we enter an x , y to identify the position to cut an specific part from  the image
    cout << "please enter the length(l)and width(w) :\n ";
    cin >> l >> w;//we enter an l , w  to cut a square of length(l)and width(w) from  the image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
           cropimage[i][j] = 255;// we make a new white image to put in it
        }
    }

    for (int i = x; i < x + l; i++) {//we put the first point = x (distance is l) so the next point is x+l
        for (int j = y; j < x + w; j++) {// we put the opposite point = y (distance is w) so the next point is x+w
            cropimage[i][j] = image[i][j];//we store in the new one
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = cropimage[i][j];//copy the new image
        }
    }
}
//-----------------------------------------------
void skew_up() {

//    Take value of degree required for the work of the skew from user
    double degree;
    cin >> degree;

//    Convert the for radians to circles
    degree = (degree * (22/7)) / 180.0;

    double extra = tan(degree) * 256.0; //This process gives us the number of rows to be added to create the degree deviation entered by the user
    double step = extra / SIZE; //The number of steps to be decreased per column after each turn
    double x = extra;

//    An expanded 2D array to place images in after skewing and before shrinking
    unsigned char skewed_image[SIZE + (int)extra][SIZE];

//     Make all pixels white
    for (int i = 0; i < SIZE + (int)extra; i++) {
        for (int j = 0; j < SIZE; j++) {
            skewed_image[i][j] = 255;
        }
    }

//    Move the images and make them skewed while reducing the required displacement in each column
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            skewed_image[j + (int)x][i] = image[j][i];
        }
        x -= step;
    }

//    The percentage required to clear the image based on the increase in the number of rows
    double shrink_rate = (SIZE + (int)extra) / 256.0;

//    Transfer of image from "skew_image" to "image" after being shrunk
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            //the row that must be developed a certain number of each column (= shrink_rate) in each pixel to reduce the image
            //the "beg_row" changes after each complete entire role on "j"
            int beg_row = i * shrink_rate;
            int sum = 0;

//          We add the pixel values and put them in "sum"
            for (int y = beg_row; y < beg_row + ceil(shrink_rate); y++) {
                sum += skewed_image[y][j];
            }

//          and then divide the sum of the pixels by their number (= shrink_rate)
//          and put it in the pixel opposite in the "image"
            image[i][j] = sum / ceil(shrink_rate);
        }
    }


}
//-----------------------------------------

void skew_right() {
    double angle;
    cout << "Please enter degree to skew right : ";
    cin >> angle;
    //calculate the offset of image and the rate of change
    double offset = 256 * (tan((angle * 22) / (7 * 180)));
    double rate_of_change = offset / 256, x = offset;
    // make array with new size to make the skew
    int new_image[SIZE][SIZE + (int) offset];
    //make all pixel in new array white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE + (int) offset; j++) {

            new_image[i][j] = 255;

        }
    }
    //copy the image in new image with skew starting from the offset
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            new_image[i][j + (int) x] = image[i][j];

        }
        //decrease the amount of offset
        x = x - rate_of_change;
    }

    // calculate how many pixel will take to make shrink
    double number_of_pixel = (256 + (int) offset) / 256.0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            //to determine the place of start index to make shrink to image
            int start_of_shrink = j * number_of_pixel;
            for (int t = start_of_shrink; t < (int) number_of_pixel + start_of_shrink; t++) {
                // take summation of pixels
                sum = sum + new_image[i][t];
            }
            //take the average of summation
            image[i][j] = sum / (int) number_of_pixel;

        }

    }
}