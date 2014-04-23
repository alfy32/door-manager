#ifndef ALFY_TABLE_H
#define ALFY_TABLE_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Table_Row.H>

#include "Alfy_Table_Row.h"
#include "Alfy_Strings.h"

class Alfy_Row
{
public:
    Alfy_Row* prev;
    Alfy_Row* next;
    Alfy_Table_Row row;

    Alfy_Row(Alfy_Row* p=0, Alfy_Row* n=0)
    :prev(p),next(n) {}
};

enum Alfy_Table_COL_TYPE {ALFY_TABLE_COL_STRING,ALFY_TABLE_COL_NUMBER};

class Alfy_Table : public Fl_Table_Row
{
    Alfy_Row* _head;
    Alfy_Row* _tail;
    Alfy_Row* _current_row;

    int _value;

    Alfy_Table_Row _headers;

    Fl_Boxtype  HEADER_BOX,
                CELL_BOX,
                TABLE_BOX;
    Fl_Color    HEADER_HOVER_COLOR,
                HEADER_TEXT_COLOR,
                CELL_COLOR,
                CELL_TEXT_COLOR,
                CELL_BORDER_COLOR,
                TABLE_COLOR,
                SELECTED_COLOR,
                SELECTED_TEXT_COLOR;
    Fl_Font     HEADER_FONT,
                CELL_FONT;
    Fl_Fontsize HEADER_FONT_SIZE,
                CELL_FONT_SIZE;
    int         LINE_THICKNESS;

    int prev_sort_col,
        prev_sort_acending;

    Alfy_Row* getRow(int row);

    int _col_align;
    int _col_header_hover;
    int _col_type;

    void draw_cell(TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0);
public:
    Alfy_Table(int X, int Y, int W, int H, const char* l=0);

    int handle(int event);

    void sort_ascending(int col);
    void sort_descending(int col);

    void add_row(const char text[]);
    void add_row(int col, std::string text[]);
    void add_row(Alfy_Table_Row new_row);
    void insert_row(int row, Alfy_Table_Row new_row);
    void remove_row(int row);
    void swap(int row_a, int row_b);
    void swap(Alfy_Row* row_a, Alfy_Row* row_b);
    void add_col(std::string header);
    void insert_col(int col, std::string header);
    std::string cell_text(int r,int c);
    void clear();
    void clear_rows();

    void auto_widths(int pad=20, int heads=0);

    void headers(Alfy_Table_Row header_row);

    void row(int row, Alfy_Table_Row new_row);
    Alfy_Table_Row row(int row);
    Alfy_Table_Row& operator [] (int row);

    void value(int row);
    int value();

    void col_align(int col, Fl_Align);
    Fl_Align col_align(int col);
    void col_type(int col, int type);
    int col_type(int col);

    void col_header_text_color(Fl_Color bcolor) { HEADER_TEXT_COLOR = bcolor;   }
    Fl_Color col_header_text_color()            { return HEADER_TEXT_COLOR;     }
    void col_header_font(Fl_Font font)          { HEADER_FONT = font;           }
    Fl_Font col_header_font()                   { return HEADER_FONT;           }
    void col_header_font_size(Fl_Fontsize fsize){ HEADER_FONT_SIZE = fsize;     }
    Fl_Fontsize col_header_font_size()          { return HEADER_FONT_SIZE;      }
    void col_header_box(Fl_Boxtype boxt)        { HEADER_BOX = boxt;            }
    Fl_Boxtype col_header_box()                 { return HEADER_BOX;            }

    void cell_border_color(Fl_Color bcolor)     { CELL_BORDER_COLOR = bcolor;   }
    Fl_Color cell_border_color()                { return CELL_BORDER_COLOR;     }
    void cell_text_color(Fl_Color tcolor)       { CELL_TEXT_COLOR = tcolor;     }
    Fl_Color cell_text_color()                  { return CELL_TEXT_COLOR;       }
    void cell_background_color(Fl_Color bcolor) { CELL_COLOR = bcolor;          }
    Fl_Color cell_background_color()            { return CELL_COLOR;            }
    void cell_font_size(Fl_Fontsize fsize)      { CELL_FONT_SIZE = fsize;       }
    Fl_Fontsize cell_font_size()                { return CELL_FONT_SIZE;        }
    void cell_font(Fl_Font font)                { CELL_FONT = font;             }
    Fl_Font cell_font()                         { return CELL_FONT;             }

    void line_thickness(int thick)              { LINE_THICKNESS = thick;       }
    int line_thickness()                        { return LINE_THICKNESS;        }

    void setData(int r, void* data_)            { if(getRow(r)) getRow(r)->row.setData(data_);                     }
    void* getData(int r)                        { if(getRow(r)) return getRow(r)->row.getData(); return (void*)-1; }
};

#endif
