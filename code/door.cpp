#include "door.h"

Door Door::readDoor(ifstream &in)
{
	Door door;
	char text[80];

	in.getline(text,80,',');
	door.style(text);

	in.getline(text,80,',');
	door.material(text);

	in.getline(text,80,',');
	door.design(text);

	in.getline(text,80,'\n');
	door.glass_style(text);

	return door;
}

string Door::doorToSQL(Door door)
{
    string statement = "INSERT INTO doors (door_style, material, design, glass_style) ";
    statement +=		  "VALUES ('" + door.style() + "','" + door.material() + "','" + door.design() + "','" + door.glass_style() + "');";

    return statement;
}
