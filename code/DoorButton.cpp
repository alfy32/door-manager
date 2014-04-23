#include "DoorButton.h"
#include "Alfy_SQL.h"

DoorButton::DoorButton(int X, int Y, int W, int H, const char *L)
:Fl_Button(X,Y,W,H,L)
{

}

//given a door object this function finds the picture and
// puts a label on the button
void DoorButton::add_door(Door door_)
{
    door = door_;
    Fl_JPEG_Image *img;     //the image of the door for each button

    //find the picture and load it
    string picture = "doors\\" + door.style() + ".jpg";
    fstream file(picture.c_str());
    if(file)    //if the picture exists
    {
        file.close();
        img = new Fl_JPEG_Image(picture.c_str());
        image(img->copy(72,160));
    }
 /*   else        //if it doesn't exist
    {
        img = new Fl_JPEG_Image("doors\\sample.jpg");
        image(img->copy(72,160));
    }
*/
/*
    Alfy_SQL db("data\\doors.db");
    db.open();
    if(db.getInt("SELECT count() FROM thumbs WHERE style='950HD'",0))
    {
        string pSQL = "SELECT pic FROM thumbs WHERE style='950HD'";
        int col = 0;

        ////cout << "got it";
        sqlite3_stmt *stmt;	// stores the results of the query

        // runs the statement and puts the results in stmt
        if( sqlite3_prepare_v2(db.getDatabase(), pSQL.c_str(), pSQL.length(), &stmt, NULL) )
        {
            // output error message
            //cout << "Prepare Error: " << sqlite3_errmsg(db.getDatabase()) << endl;

            //quit and return 0

        }

        // steps to the first row of values
        sqlite3_step(stmt);

        // gets a blob value from the given column
        const void *value = sqlite3_column_blob(stmt, col);




        Fl_JPEG_Image *img = new Fl_JPEG_Image(door.style().c_str(),(unsigned char*)value);
        image(img);

        // clears the stmt
        sqlite3_finalize(stmt);
    }
    db.close();

    */

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
