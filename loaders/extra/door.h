#ifndef DOOR_H
#define DOOR_H

#include<fstream>
#include<string>
using namespace std;

#define FIBERGLASS	1
#define STEEL		2

class Door
{
private:
	string style_;
	string material_;
	string design_;
	string glass_style_;
public:
	Door() {}
	Door(string _style, string _material, string _design, string _glass_style)
	:style_(_style),material_(_material),design_(_design),glass_style_(_glass_style)
	{}

	void style(string _style)		{ style_ = _style;			}
	void material(string _material)	{ material_ = _material;	}
	void design(string _design)		{ design_ = _design;		}
	void glass_style(string _style)	{ glass_style_ = _style;	}

	string style()					{ return style_;			}
	string material()				{ return material_;			}
	string design()					{ return design_;			}
	string glass_style()			{ return glass_style_;		}

	static Door readDoor(ifstream &in);
	static string doorToSQL(Door door);
};

#endif // DOOR_H_INCLUDED
