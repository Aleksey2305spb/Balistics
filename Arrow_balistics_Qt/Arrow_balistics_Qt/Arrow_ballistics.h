#include <iostream>
#include <cmath>
#include <conio.h>
#include <windows.h>
using namespace std;
class arrow
{
    double d = 9.3 / 1000; // диаметр стрелы м (Стрелы Easton 23/14)
    double weight = 30; // вес стрелы в граммах
    double speed = 75; // начальная скорость стрелы м/с
    double K_feather = 1.2; // коэфициент сопротивления перьев 
    double toGrn(double Gm);
    double toGm (double Grn);
    double toFPS(double MS);
    double toMS(double FPS);
public:
    double get_arrow_d();
    double get_arrow_weight();
    double get_arrow_weight_gn();
    double get_arrow_speed();
    double get_arrow_speed_fps();
    double get_arrow_K_feather();
    void info ();
    arrow();
    ~arrow();
};
class compound_bow
{
    double sight_base = 730;// расстояние от peepsight до скопа (мм)
    double bow_draw_weight = 60; // фунтаж лука
    double *sight;
    double *sight_scale; // шкала прицела. <0> прицел на 18 м
public:
    void set_18m_sight(double value);
    void set_sight (double value, int i);
    double get_sight(int i);
    compound_bow ();
    ~compound_bow();
};
class target
{
    double Target_X;
    double Target_Y;
    double Target_D [6] = { 20, 80, 120, 160, 200, 240}; // размер зоны попадания
public:
    void info();
    target();
    ~target();
};
class ballistics
{
    const double g = 9.8;
    const double pi = 3.14;
    const double Ro = 1.25; // плотность воздуха кг/м3
    const double Alfa = 0.25; // коэффициент лобового сопротивления
    double MAX_distanse;
    double toRadian(double Degrees);
    double toDegrees(double Radian);
    void dx_dy(double& dVx, double& dVy, double& Vx, double& Vy, const double& dt);
    double get_normal_sight(double distance); // при ошибке возвращается -1
    double get_MAX_distanse();
    void set_normal_sights();
public:
    void show_MAX_distanse();
    void show_normal_sights();
    ballistics();
    ~ballistics();
    arrow* arrow_;
    compound_bow* compound_bow_;
    target* target_;
};
