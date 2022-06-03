#ifndef GNUP_H_INCLUDED
#define GNUP_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
#ifdef WIN32
//#define GNUPLOT_NAME "\"C:/Program Files/gnuplot/bin/gnuplot.exe\" -persist"
#define GNUPLOT_NAME "gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif

using namespace std;



extern "C" FILE *popen(const char *command, const char *mode);




class GnuP {

protected:

    /// Кол-во функций для построения
    int _k;

    /// Команды для Гнуплота
    string command;
    string command_set;

    /// Параметры по умолчанию
    int _line_; // ТИП ЛИНИИ: points / lines / linespoints
    int _lw_; // ТОЛЩИНА ЛИНИИ
    int _color_; // ЦВЕТ ЛИНИИ
    int _grid_; // СЕТКА
    int _shape_; // ОБУФТПЙФШ ЖПТНХ ПЛОБ
    int _loc_legend_1_; // РАСПОЛОЖЕНИЕ ЛЕГЕНДЫ
    int _loc_legend_2_; // РАСПОЛОЖЕНИЕ ЛЕГЕНДЫ
    string _legend_; // ПОДПИСЬ ФУНКЦИИ
    string _title_;  // ЗАГОЛОВОК

    /// Параметры пользователя
    int _line; // ТИП ЛИНИИ: points / lines / linespoints
    int _lw; // ТОЛЩИНА ЛИНИИ
    int _color; // ЦВЕТ ЛИНИИ
    int _grid; // СЕТКА
    int _shape; // ОБУФТПЙФШ ЖПТНХ ПЛОБ
    int _loc_legend_1; // РАСПОЛОЖЕНИЕ ЛЕГЕНДЫ (СЛЕВА/СПРАВА, СВЕРХУ/СНИЗУ)
    int _loc_legend_2; // РАСПОЛОЖЕНИЕ ЛЕГЕНДЫ (ВНУТРИ/СНАРУЖИ)
    string _legend; // ПОДПИСЬ ФУНКЦИИ
    string _title;  // ЗАГОЛОВОК

    /// Палитра цветов
    map <int,string> Colors;
    int col;


public:

    GnuP();
    ~GnuP();
    void Clear_Param();
    void setParam(int grid=0, int shape=0, int loc_legend_1=0, int loc_legend_2=0, string title="");
    void plot();

    template <typename X, typename Y>
    void Save_Data(int n, X *x, Y *y);



    template <typename X, typename Y>
    void plotArrayPar(int n, X *x, Y *y, int line=0, int lw=0, int color=0, string legend="");

    template <typename X, typename F>
    void plotFuncPar(int n, X *x, F (*f)(X), int line=0, int lw=0, int color=0, string legend="");

    template <typename X, typename F, typename A, typename B, typename C, typename D, typename E>
    void plotFuncArg5(int n, X *x, F (*f)(X,A,B,C,D,E), A a, B b, C c, D d, E e,
                      int line=0, int lw=0, int color=0, string legend="");

    template <typename X, typename F, typename A, typename B, typename C, typename D>
    void plotFuncArg4(int n, X *x, F (*f)(X,A,B,C,D), A a, B b, C c, D d,
                      int line=0, int lw=0, int color=0, string legend="");

    template <typename X, typename F, typename A, typename B, typename C>
    void plotFuncArg3(int n, X *x, F (*f)(X,A,B,C), A a, B b, C c,
                      int line=0, int lw=0, int color=0, string legend="");

    template <typename X, typename F, typename A, typename B>
    void plotFuncArg2(int n, X *x, F (*f)(X,A,B), A a, B b,
                      int line=0, int lw=0, int color=0, string legend="");

    template <typename X, typename F, typename A>
    void plotFuncArg1(int n, X *x, F (*f)(X,A), A a,
                      int line=0, int lw=0, int color=0, string legend="");


///____________________________________________plotArray__________________________________

    template <typename X, typename Y1>
    void plotArray(int n, X *x, Y1 *y1);

    template <typename X, typename Y1, typename Y2>
    void plotArray(int n, X *x, Y1 *y1, Y2 *y2);

    template <typename X, typename Y1, typename Y2, typename Y3>
    void plotArray(int n, X *x, Y1 *y1, Y2 *y2, Y3 *y3);

    template <typename X, typename Y1, typename Y2, typename Y3, typename Y4>
    void plotArray(int n, X *x, Y1 *y1, Y2 *y2, Y3 *y3, Y4 *y4);

    template <typename X, typename Y1, typename Y2, typename Y3, typename Y4, typename Y5>
    void plotArray(int n, X *x, Y1 *y1, Y2 *y2, Y3 *y3, Y4 *y4, Y5 *y5);



    template <typename X1, typename Y1, typename X2, typename Y2>
    void plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2);

    template <typename X1, typename Y1, typename X2, typename Y2, typename X3, typename Y3>
    void plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2, int n3, X3 *x3, Y3 *y3);

    template <typename X1, typename Y1, typename X2, typename Y2, typename X3, typename Y3, typename X4,typename Y4>
    void plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2, int n3, X3 *x3, Y3 *y3, int n4, X4 *x4, Y4 *y4);

    template <typename X1, typename Y1, typename X2, typename Y2, typename X3, typename Y3, typename X4,typename Y4,
                typename X5,typename Y5>
    void plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2, int n3, X3 *x3, Y3 *y3, int n4, X4 *x4, Y4 *y4,
                   int n5, X5 *x5, Y5 *y5);



///____________________________________________plotFunc__________________________________

    template <typename X, typename F1>
    void plotFunc(int n, X *x, F1 (*f1)(X));

    template <typename X, typename F1, typename F2>
    void plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X));

    template <typename X, typename F1, typename F2, typename F3>
    void plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X), F3 (*f3)(X));

    template <typename X, typename F1, typename F2, typename F3, typename F4>
    void plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X), F3 (*f3)(X), F4 (*f4)(X));

    template <typename X, typename F1, typename F2, typename F3, typename F4, typename F5>
    void plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X), F3 (*f3)(X), F4 (*f4)(X), F5 (*f5)(X));



    template <typename X1, typename F1, typename X2, typename F2>
    void plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2));

    template <typename X1, typename F1, typename X2, typename F2, typename X3, typename F3>
    void plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2), int n3, X3 *x3, F3 (*f3)(X3));

    template <typename X1, typename F1, typename X2, typename F2, typename X3, typename F3, typename X4,typename F4>
    void plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2), int n3, X3 *x3, F3 (*f3)(X3),
                  int n4, X4 *x4, F4 (*f4)(X4));

    template <typename X1, typename F1, typename X2, typename F2, typename X3, typename F3, typename X4,typename F4,
                typename X5, typename F5>
    void plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2), int n3, X3 *x3, F3 (*f3)(X3),
                  int n4, X4 *x4, F4 (*f4)(X4), int n5, X5 *x5, F5 (*f5)(X5));



};

///===================================================================================================
///===================================================================================================
///===================================================================================================



GnuP::GnuP()
{
    /// Кол-во функций для построения
    _k = -1;

    /// Команды для Гнуплота
    command = "";
    command_set = "set grid\n";

    /// Параметры по умолчанию
    _line_ = 2; // ТИП ЛИНИИ: points / lines / linespoints - ЛИНИЯ
    _lw_ = 2; // ТОЛЩИНА ЛИНИИ
    _color_ = 1; // ЦВЕТ ЛИНИИ
    _legend_ = ""; // ПОДПИСЬ ФУНКЦИИ
    _grid_ = 1; // СЕТКА - ВКЛ.
    _shape_ = 2; // ОБУФТПЙФШ ЖПТНХ ПЛОБ
    _loc_legend_1 = 2; // РАСПОЛОЖЕНИЕ ЛЕГЕНДЫ (СЛЕВА/СПРАВА, СВЕРХУ/СНИЗУ) - СПРАВА СВЕРХУ
    _loc_legend_2 = 1; // РАСПОЛОЖЕНИЕ ЛЕГЕНДЫ (ВНУТРИ/СНАРУЖИ) - ВНУТРИ
    _title_ = "";  // ЗАГОЛОВОК
    Clear_Param();
    Colors = {{0,"#0000DD"},{1,"#00CCEE"},{2,"#99FF99"},{3,"#99CC00"},{4,"#CCFF33"},
                        {5,"#9900FF"},{6,"#DD88FF"},{7,"#FFAAFF"},{8,"#CC0099"},{9,"#990000"},{10,"#FF0000"},
                        {11,"#FFAA00"},{12,"#FFFF88"},{13,"#00AA99"},{14,"#000000"}};
    col = 15; // КОЛ-ВО ЦВЕТОВ
}


GnuP::~GnuP()
{
    command.clear();
    command_set.clear();
    string name;
    //for (int i=0;i<=_k;i++){ // Удаляем созданные текстовые файлы
    //    name = "Graph_" + to_string(i) + ".txt";
    //    remove(name.c_str());
    //}
    _k = -1;
}

void GnuP::Clear_Param()
{
    _line = _line_;
    _lw = _lw_;
    _color = _color_;
    _legend = _legend_;
    _title = _title_;
}


template <typename X, typename Y>
void GnuP::Save_Data(int n, X *x, Y *y)
{
    _k++; // СЧЁТЧИК ФУНКЦИЙ (на 1 меньше, чем функций)
    string name = "Graph_" + to_string(_k) + ".txt";
    ofstream file;
    file.open(name);
    for (int i=0;i<n;i++) {
        if (i<n-1)
            file<<x[i]<<" "<<y[i]<<"\n";
        else file<<x[i]<<" "<<y[i];
        //cout<<"x="<<x[k][i]<<"   f(x)="<<y[k][i]<<endl;
    }
    string line_or_point;
    if (_line == 1)
        line_or_point = "points pt " + to_string((_k%10)+6) + " ";
    else if (_line == 3)
        line_or_point = "linespoints pt " + to_string((_k%10)+6) + " ";
    else                     //if (_line == 2)
        line_or_point = "lines ";
    if (_k==0) command = "plot ";
    else command += ", ";
    command += "\"" + name + "\" u 1:2 w " + line_or_point;
    command += "lw " + to_string(_lw) + " lt rgb '" + Colors[(_color-1)%col] + "'";
    command += "title \"" + _legend + "\"";
}


void GnuP::setParam(int grid, int shape, int loc_legend_1, int loc_legend_2, string title)
{
    if (grid!=0) _grid = grid;
        else _grid = _grid_;
    if (shape!=0) _shape = shape;
        else _shape = _shape_;
    if (loc_legend_1!=0) _loc_legend_1 = loc_legend_1;
        else _loc_legend_1 = _loc_legend_1_;
    if (loc_legend_2!=0) _loc_legend_2 = loc_legend_2;
        else _loc_legend_2 = _loc_legend_2_;
    if (title.size()) _title = title;
        else _title = _title_;
    if (_grid==2) command_set = "";
    if (_shape==1) command_set += "set size square\n";

    if (_loc_legend_2==1) { // ВНУТРИ ОКОШКА
        if (_loc_legend_1==1) command_set += "set key left top \n"; // ЛЕВО ВЕРХ
        else if (_loc_legend_1==2) command_set += "set key right top \n"; // ПРАВО ВЕРХ
        else if (_loc_legend_1==3) command_set += "set key left bottom \n"; // ЛЕВО НИЗ
        else if (_loc_legend_1==4) command_set += "set key right bottom \n"; // ПРАВО НИЗ
        else if (_loc_legend_1==5) command_set = "unset key\n";
    }
    else if (_loc_legend_2==2) { // СНАРУЖИ ОКОШКА
        if (_loc_legend_1==1) command_set += "set key left outside \n"; // ЛЕВО ВЕРХ
        else if (_loc_legend_1==2) command_set += "set key right outside \n"; // ПРАВО ВЕРХ
        else if (_loc_legend_1==3) command_set += "set key left below \n"; // ЛЕВО НИЗ
        else if (_loc_legend_1==4) command_set += "set key right below \n"; // ПРАВО НИЗ
        else if (_loc_legend_1==5) command_set = "unset key\n";
    }
    if (_title.size()) command_set += "set title \"" + _title + "\"\n";
}


void GnuP::plot()
{
    if (_k!=-1) {
        FILE *gnu = popen(GNUPLOT_NAME, "w");
        command_set += command + "\n";
        fprintf(gnu, "%s", command_set.c_str());
    }
    else
        cout<<" Unable to plot: no data"<<endl;
}




template <typename X, typename Y>
void GnuP::plotArrayPar(int n, X *x, Y *y, int line, int lw, int color, string legend)
{
    Clear_Param();
    if (line) _line = line;
    if (lw) _lw = lw;
    if (color) _color = color;
        else _color = _k+2;
    if (legend.size()) _legend = legend;
        else _legend = "f" + to_string(_k+2);
    Save_Data(n,x,y);
}


template <typename X, typename Y>
void GnuP::plotFuncPar(int n, X *x, Y (*f)(X), int line, int lw, int color, string legend)
{
    Y y[n];
    for (int i=0;i<n;i++){
        y[i] = f(x[i]);
    }
    plotArrayPar(n,x,y,line,lw,color,legend);
}




template <typename X, typename Y, typename A, typename B, typename C, typename D, typename E>
void GnuP::plotFuncArg5(int n, X *x, Y (*f)(X,A,B,C,D,E), A a, B b, C c, D d, E e,
                        int line, int lw, int color, string legend){
    Y y[n];
    for (int i=0;i<n;i++){
        y[i] = f(x[i],a,b,c,d,e);
    }
    plotArrayPar(n,x,y,line,lw,color,legend);
}


template <typename X, typename Y, typename A, typename B, typename C, typename D>
void GnuP::plotFuncArg4(int n, X *x, Y (*f)(X,A,B,C,D), A a, B b, C c, D d,
                        int line, int lw, int color, string legend){
    Y y[n];
    for (int i=0;i<n;i++){
        y[i] = f(x[i],a,b,c,d);
    }
    plotArrayPar(n,x,y,line,lw,color,legend);
}



template <typename X, typename Y, typename A, typename B, typename C>
void GnuP::plotFuncArg3(int n, X *x, Y (*f)(X,A,B,C), A a, B b, C c,
                        int line, int lw, int color, string legend){
    Y y[n];
    for (int i=0;i<n;i++){
        y[i] = f(x[i],a,b,c);
    }
    plotArrayPar(n,x,y,line,lw,color,legend);
}


template <typename X, typename Y, typename A, typename B>
void GnuP::plotFuncArg2(int n, X *x, Y (*f)(X,A,B), A a, B b,
                        int line, int lw, int color, string legend){
    Y y[n];
    for (int i=0;i<n;i++){
        y[i] = f(x[i],a,b);
    }
    plotArrayPar(n,x,y,line,lw,color,legend);
}



template <typename X, typename Y, typename A>
void GnuP::plotFuncArg1(int n, X *x, Y (*f)(X,A), A a,
                        int line, int lw, int color, string legend){
    Y y[n];
    for (int i=0;i<n;i++){
        y[i] = f(x[i],a);
    }
    plotArrayPar(n,x,y,line,lw,color,legend);
}




///_____________________________________________________plotArray___________________________________________

template <typename X, typename Y1>
void GnuP::plotArray(int n, X *x, Y1 *y1)
{
    plotArrayPar(n,x,y1);
}


template <typename X, typename Y1, typename Y2>
void GnuP::plotArray(int n, X *x, Y1 *y1, Y2 *y2)
{
    plotArrayPar(n,x,y1);
    plotArrayPar(n,x,y2);
}


template <typename X, typename Y1, typename Y2, typename Y3>
void GnuP::plotArray(int n, X *x, Y1 *y1, Y2 *y2, Y3 *y3)
{
    plotArrayPar(n,x,y1);
    plotArrayPar(n,x,y2);
    plotArrayPar(n,x,y3);
}


template <typename X, typename Y1, typename Y2, typename Y3, typename Y4>
void GnuP::plotArray(int n, X *x, Y1 *y1, Y2 *y2, Y3 *y3, Y4 *y4)
{
    plotArrayPar(n,x,y1);
    plotArrayPar(n,x,y2);
    plotArrayPar(n,x,y3);
    plotArrayPar(n,x,y4);
}


template <typename X, typename Y1, typename Y2, typename Y3, typename Y4, typename Y5>
void GnuP::plotArray(int n, X *x, Y1 *y1, Y2 *y2, Y3 *y3, Y4 *y4, Y5 *y5)
{
    plotArrayPar(n,x,y1);
    plotArrayPar(n,x,y2);
    plotArrayPar(n,x,y3);
    plotArrayPar(n,x,y4);
    plotArrayPar(n,x,y5);
}






template <typename X1, typename Y1, typename X2, typename Y2>
void GnuP::plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2)
{
    plotArrayPar(n1,x1,y1);
    plotArrayPar(n2,x2,y2);
}

template <typename X1, typename Y1, typename X2, typename Y2, typename X3, typename Y3>
void GnuP::plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2, int n3, X3 *x3, Y3 *y3)
{
    plotArrayPar(n1,x1,y1);
    plotArrayPar(n2,x2,y2);
    plotArrayPar(n3,x3,y3);
}

template <typename X1, typename Y1, typename X2, typename Y2, typename X3, typename Y3, typename X4,typename Y4>
void GnuP::plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2, int n3, X3 *x3, Y3 *y3, int n4, X4 *x4, Y4 *y4)
{
    plotArrayPar(n1,x1,y1);
    plotArrayPar(n2,x2,y2);
    plotArrayPar(n3,x3,y3);
    plotArrayPar(n4,x4,y4);
}

template <typename X1, typename Y1, typename X2, typename Y2, typename X3, typename Y3, typename X4,typename Y4,
            typename X5,typename Y5>
void GnuP::plotArray(int n1, X1 *x1, Y1 *y1, int n2, X2 *x2, Y2 *y2, int n3, X3 *x3, Y3 *y3, int n4, X4 *x4, Y4 *y4,
               int n5, X5 *x5, Y5 *y5)
{
    plotArrayPar(n1,x1,y1);
    plotArrayPar(n2,x2,y2);
    plotArrayPar(n3,x3,y3);
    plotArrayPar(n4,x4,y4);
    plotArrayPar(n5,x5,y5);
}




///_____________________________________________________plotFunc___________________________________________

template <typename X, typename F1>
void GnuP::plotFunc(int n, X *x, F1 (*f1)(X))
{
    plotFuncPar(n,x,f1);
}


template <typename X, typename F1, typename F2>
void GnuP::plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X))
{
    plotFuncPar(n,x,f1);
    plotFuncPar(n,x,f2);
}

template <typename X, typename F1, typename F2, typename F3>
void GnuP::plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X), F3 (*f3)(X))
{
    plotFuncPar(n,x,f1);
    plotFuncPar(n,x,f2);
    plotFuncPar(n,x,f3);
}

template <typename X, typename F1, typename F2, typename F3, typename F4>
void GnuP::plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X), F3 (*f3)(X), F4 (*f4)(X))
{
    plotFuncPar(n,x,f1);
    plotFuncPar(n,x,f2);
    plotFuncPar(n,x,f3);
    plotFuncPar(n,x,f4);
}

template <typename X, typename F1, typename F2, typename F3, typename F4, typename F5>
void GnuP::plotFunc(int n, X *x, F1 (*f1)(X), F2 (*f2)(X), F3 (*f3)(X), F4 (*f4)(X), F5 (*f5)(X))
{
    plotFuncPar(n,x,f1);
    plotFuncPar(n,x,f2);
    plotFuncPar(n,x,f3);
    plotFuncPar(n,x,f4);
    plotFuncPar(n,x,f5);
}




template <typename X1, typename F1, typename X2, typename F2>
void GnuP::plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2))
{
    plotFuncPar(n1,x1,f1);
    plotFuncPar(n2,x2,f2);
}

template <typename X1, typename F1, typename X2, typename F2, typename X3, typename F3>
void GnuP::plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2), int n3, X3 *x3, F3 (*f3)(X3))
{
    plotFuncPar(n1,x1,f1);
    plotFuncPar(n2,x2,f2);
    plotFuncPar(n3,x3,f3);
}

template <typename X1, typename F1, typename X2, typename F2, typename X3, typename F3, typename X4,typename F4>
void GnuP::plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2), int n3, X3 *x3, F3 (*f3)(X3),
              int n4, X4 *x4, F4 (*f4)(X4))
{
    plotFuncPar(n1,x1,f1);
    plotFuncPar(n2,x2,f2);
    plotFuncPar(n3,x3,f3);
    plotFuncPar(n4,x4,f4);
}

template <typename X1, typename F1, typename X2, typename F2, typename X3, typename F3, typename X4,typename F4,
            typename X5, typename F5>
void GnuP::plotFunc(int n1, X1 *x1, F1 (*f1)(X1), int n2, X2 *x2, F2 (*f2)(X2), int n3, X3 *x3, F3 (*f3)(X3),
              int n4, X4 *x4, F4 (*f4)(X4), int n5, X5 *x5, F5 (*f5)(X5))
{
    plotFuncPar(n1,x1,f1);
    plotFuncPar(n2,x2,f2);
    plotFuncPar(n3,x3,f3);
    plotFuncPar(n4,x4,f4);
    plotFuncPar(n5,x5,f5);
}

#endif // GNUP_H_INCLUDED