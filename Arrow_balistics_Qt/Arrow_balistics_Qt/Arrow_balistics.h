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
    double toGrn(double Gm)
    {
        return Gm * 15.43;
    }
    double toGm (double Grn)
    {
        return Grn / 15.43;
    }
    double toFPS(double MS) 
    {
        return MS * 3.28;
    }
    double toMS(double FPS)
    {
        return FPS * 0.304;
    }
public:
    double get_arrow_d()
    {
        return d;
    }
    double get_arrow_weight()
    {
        return weight;
    }
    double get_arrow_speed()
    {
        return speed;
    }
    double get_arrow_K_feather()
    {
        return K_feather;
    }
    void info ()
    {
        cout << "Используютя стрелы:\n";
        cout << " - диаметр стрелы " << d << " мм\n";
        cout << " - вес стрелы " << weight << " г ( " << toGrn(weight) << " гн )\n";
        cout << " - начальная скорость стрелы " << speed << " м/с ( " << toFPS (speed) <<  " FPS )\n";
    }
    arrow() {;}
    ~arrow(){;}
};
class compound_bow
{
    double sight_base = 730;// расстояние от peepsight до скопа (мм)
    double bow_draw_weight = 60; // фунтаж лука
    double *sight;
    double *sight_scale; // шкала прицела. <0> прицел на 18 м
public:
    void set_18m_sight(double value)
    {
        sight [0] = value;
        sight_scale[0] = 0;
    }
    void set_sight (double value, int i)
    {
        sight[i] = value;
        sight_scale[i] = sight_base * std::tan(value - sight[0]);
    }
    double get_sight(int i)
    {
        double value = sight_scale[i];
        return value;
    }
    compound_bow ()
    {
        sight = new double[21];
        sight_scale = new double[21];
    }
    ~compound_bow()
    {
        delete [] sight;
        delete[] sight_scale;
    }
};
class target
{
    double Target_X;
    double Target_Y;
    double Target_D [6] = { 20, 80, 120, 160, 200, 240}; // размер зоны попадания
public:
    void info()
    {
        cout << "Используются мишени для стрельбы в помещении.\n";
    }
    target() { ; }
    ~target() { ; }
};
class ballistics
{
    arrow *arrow_;
    compound_bow *compound_bow_;
    target *target_;
    const double g = 9.8;
    const double pi = 3.14;
    const double Ro = 1.25; // плотность воздуха кг/м3
    const double Alfa = 0.25; // коэффициент лобового сопротивления
    double MAX_distanse;
    double toRadian (double Degrees)
    {
        return Degrees * pi / 180. ;
    }
    double toDegrees (double Radian)
    {
        return Radian * 180. / pi;
    }
    void dx_dy(double& dVx, double& dVy, double& Vx, double& Vy, const double& dt)
    {
        
        double S = pi * arrow_->get_arrow_d () * arrow_->get_arrow_d () / 4;
        double F_resist = arrow_->get_arrow_K_feather () * Alfa * S * Ro / 2;
        dVx = (-F_resist * Vx * std::sqrt(Vx * Vx + Vy * Vy)) * dt;
        dVy = (F_resist * Vy * std::sqrt(Vx * Vx + Vy * Vy) - g) * dt;
    }
    double get_normal_sight(double distance) // при ошибке возвращается -1
    {
        double sight = 0;
        const double dt = 0.001;
        const double accuracy = 10000;
        double* Vx = new double[accuracy];
        double* Vy = new double[accuracy];
        double dVx;
        double dVy;
        double* X = new double[accuracy];
        double* Y = new double[accuracy];
        double dX;
        double dY;
        double last_shot;
        double current_shot = 0;
        double V_x;
        double V_y;
        if (distance > MAX_distanse) return -1;
        do {
            last_shot = current_shot;
            Vx[0] = arrow_->get_arrow_speed() * std::cos(sight);
            Vy[0] = arrow_->get_arrow_speed() * std::sin(sight);
            X[0] = 0;
            Y[0] = 0;
            for (int i = 1; i < accuracy; i++)
            {
                V_x = Vx[i - 1];
                V_y = Vy[i - 1];
                dx_dy(dVx, dVy, V_x, V_y, dt);
                Vx[i] = Vx[i - 1] + dVx;
                Vy[i] = Vy[i - 1] + dVy;
                dX = (Vx[i] + Vx[i - 1]) / 2 * dt;
                dY = (Vy[i] + Vy[i - 1]) / 2 * dt;
                X[i] = X[i - 1] + dX;
                Y[i] = Y[i - 1] + dY;
                if (X[i] > distance)
                {
                    
                    current_shot = Y[i];
                    break;
                }
            }
            sight += 0.0001;
            if (sight > pi / 2) return -1;
        } while (current_shot * last_shot >= 0);
        delete[] Vx;
        delete[] Vy;
        delete[] X;
        delete[] Y;
        return sight;
    }
    double get_MAX_distanse ()
    {
        double distance = 0;
        double sight = 0;
        const double dt = 0.001;
        const double accuracy = 100000;
        double* Vx = new double[accuracy];
        double* Vy = new double[accuracy];
        double dVx;
        double dVy;
        double* X = new double[accuracy];
        double* Y = new double[accuracy];
        double dX;
        double dY;
        double V_x;
        double V_y;
        do {
            Vx[0] = arrow_->get_arrow_speed() * std::cos(sight);
            Vy[0] = arrow_->get_arrow_speed() * std::sin(sight);
            X[0] = 0;
            Y[0] = 0;
            for (int i = 1; i < accuracy; i++)
            {
                V_x = Vx[i - 1];
                V_y = Vy[i - 1];
                dx_dy(dVx, dVy, V_x, V_y, dt);
                Vx[i] = Vx[i - 1] + dVx;
                Vy[i] = Vy[i - 1] + dVy;
                dX = (Vx[i] + Vx[i - 1]) / 2 * dt;
                dY = (Vy[i] + Vy[i - 1]) / 2 * dt;
                X[i] = X[i - 1] + dX;
                Y[i] = Y[i - 1] + dY;
                if (Y[i] < 0)
                {
                    if (distance < X[i - 1])
                    {
                        distance = X[i-1];
                    }
                    break;
                }
            }
            sight += 0.001;
        } while (sight < pi/2);
        delete[] Vx;
        delete[] Vy;
        delete[] X;
        delete[] Y;
        return distance;
    }
    void set_normal_sights()
    {
        double value;
        for (int i = 1; i < 21; i++)
        {
            value = get_normal_sight(i * 5);
            compound_bow_->set_sight(value, i);
        }
    }
public:
    void show_MAX_distanse()
    {
        cout << "Максимальная дальность выстрела " << get_MAX_distanse() << " м.\n";
    }
    void show_normal_sights() 
    {
        cout << "\n";
        cout.width(25); cout << "<Дистанция>" ;
        cout.width(25); cout << "<Отступ на прицеле>\n";
        cout.width(20); cout << "(м)";
        cout.width(20); cout << "(мм)\n";
        cout.width(20); cout << 18;
        cout.width(20); cout << compound_bow_->get_sight(0) << endl;
        for (int i = 1; i < 21; i++)
        {
            cout.width(20); cout << i * 5;
            cout.width(20); cout << compound_bow_->get_sight(i) << endl;
        }
    }
    ballistics()
    {        
        arrow_ = new arrow;
        compound_bow_ = new compound_bow;
        target_ = new target;
        MAX_distanse = get_MAX_distanse();
        compound_bow_->set_18m_sight(get_normal_sight(18.));
        set_normal_sights();
    }
    ~ballistics()
    {
        delete arrow_;
        delete compound_bow_;
        delete target_;
    }
};
void set_rus_letters() //#include <windows.h>
{
    SetConsoleCP(1251); // включит "русский" язык
    SetConsoleOutputCP(1251); // включит "русский" язык
}
void Press_any_key_to_continue()

{
    cout << endl << "Press any key to continue ...";
    _getch();
}
