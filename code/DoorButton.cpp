#include "DoorButton.h"
#include <iostream>

DoorButton::DoorButton(int X, int Y, int W, int H, const char *L)
:Fl_Button(X,Y,W,H,L)
{

}

//given a door object this function finds the picture and
// puts a label on the button
void DoorButton::add_door(Door door_)
{
    int SIZE = 2000000;
    string name = "CCV932.jpg";

    door = door_;

    string d;
    char ch;
    char *stuff; // = new char[SIZE];

    string filename = "doors\\" + name;
    fstream file(filename.c_str(), ios::in | ios::binary);
    file.seekg(0L, ios::end);
    //cout << "filesize: " << file.tellg() << endl;
    SIZE = file.tellg();
    int i = 0;

    stuff = new char[SIZE];

    file.clear();
    file.seekg(0L, ios::beg);
    file.read(reinterpret_cast<char*>(stuff), SIZE);

/*
    while(!file.eof())
    {
        stuff[i++] = file.get();
    }
    d = stuff;
    cout << d.size() << endl;
    cout << d << endl;
*/
    Fl_JPEG_Image *img;



    img = new Fl_JPEG_Image("pic", (unsigned char*)stuff);
   /* Fl_JPEG_Image *img;     //the image of the door for each button

    //find the picture and load it
    string picture = "doors\\" + door.style() + ".jpg";
    fstream file(picture.c_str());
    if(file)    //if the picture exists
    {
        file.close();
        img = new Fl_JPEG_Image(picture.c_str());
        image(img->copy(72,160));
    }
    else        //if it doesn't exist
    {
        img = new Fl_JPEG_Image("doors\\sample.jpg");
        image(img->copy(72,160));
    }
*/
    image(img->copy(72,160));

    //make the label for the door
    string label = "Style:" + door.style() +
                " \nMaterial: " + door.material() +
                " \nDesign: " + door.design() +
                " \nGlass: " + door.glass_style();
    copy_label(label.c_str());
}

Door DoorButton::get_door()
{
    return door;
}
