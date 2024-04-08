#include <iostream>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <Arrow_ballistics.h>
using namespace std;
    double arrow::toGrn (double Gm)
    {
        return Gm * 15.43;
    }
    double arrow::toGm (double Grn)
    {
        return Grn / 15.43;
    }
    double arrow::toFPS(double MS)
    {
        return MS * 3.28;
    }
    double arrow::toMS(double FPS)
    {
        return FPS * 0.304;
    }
    double arrow::get_arrow_d()
    {
        return d;
    }
    double arrow::get_arrow_weight()
    {
        return weight;
    }
    double arrow::get_arrow_weight_gn()
    {
        return toGrn(weight);
    }
    double arrow::get_arrow_speed()
    {
        return speed;
    }
    double arrow::get_arrow_speed_fps()
    {
        return toFPS (speed);
    }
    double arrow::get_arrow_K_feather()
    {
        return K_feather;
    }
    void arrow::info ()
    {
        cout << "Используютя стрелы:\n";
        cout << " - диаметр стрелы " << d << " мм\n";
        cout << " - вес стрелы " << weight << " г ( " << toGrn(weight) << " гн )\n";
        cout << " - начальная скорость стрелы " << speed << " м/с ( " << toFPS (speed) <<  " FPS )\n";
    }
    arrow::arrow() {;}
    arrow::~arrow(){;}
    void compound_bow::set_18m_sight(double value)
    {
        sight [0] = value;
        sight_scale[0] = 0;
    }
    void compound_bow::set_sight (double value, int i)
    {
        sight[i] = value;
        sight_scale[i] = sight_base * std::tan(value - sight[0]);
    }
    double compound_bow::get_sight(int i)
    {
        double value = sight_scale[i];
        return value;
    }
    compound_bow::compound_bow ()
    {
        sight = new double[101];
        sight_scale = new double[101];
    }
    compound_bow::~compound_bow()
    {
        delete [] sight;
        delete[] sight_scale;
    }
    double Target_X;
    double Target_Y;
    double Target_D [6] = { 20, 80, 120, 160, 200, 240}; // размер зоны попадания
    void target::info()
    {
        cout << "Используются мишени для стрельбы в помещении.\n";
    }
    target::target() { ; }
    target::~target() { ; }
    double ballistics::toRadian(double Degrees)
    {
        return Degrees * pi / 180.;
    }
    double ballistics::toDegrees(double Radian)
    {
        return Radian * 180. / pi;
    }
    void ballistics::dx_dy(double& dVx, double& dVy, double& Vx, double& Vy, const double& dt)
    {

        double S = pi * arrow_->get_arrow_d() * arrow_->get_arrow_d() / 4;
        double F_resist = arrow_->get_arrow_K_feather() * Alfa * S * Ro / 2;
        dVx = (-F_resist * Vx * std::sqrt(Vx * Vx + Vy * Vy)) * dt;
        dVy = (F_resist * Vy * std::sqrt(Vx * Vx + Vy * Vy) - g) * dt;
    }
    double ballistics::get_normal_sight(double distance) // при ошибке возвращается -1
    {
        double sight = 0;
        const double dt = 0.001;
        const double accuracy = 10000;
        double Vx;
        double Vy;
        double dVx;
        double dVy;
        double X;
        double Y;
        double dX;
        double dY;
        double last_shot;
        double current_shot = 0;
        double V_x;
        double V_y;
        if (distance > MAX_distanse) return -1;
        do {
            last_shot = current_shot;
            Vx = arrow_->get_arrow_speed() * std::cos(sight);
            Vy = arrow_->get_arrow_speed() * std::sin(sight);
            X = 0;
            Y = 0;
            for (int i = 1; i < accuracy; i++)
            {
                V_x = Vx;
                V_y = Vy;
                dx_dy(dVx, dVy, Vx, Vy, dt);
                Vx = Vx + dVx;
                Vy = Vy + dVy;
                dX = (Vx + V_x) / 2 * dt;
                dY = (Vy + V_y) / 2 * dt;
                X = X + dX;
                Y = Y + dY;
                if (X > distance)
                {

                    current_shot = Y;
                    break;
                }
            }
            sight += 0.0001;
            if (sight > pi / 2) return -1;
        } while (current_shot * last_shot >= 0);
        return sight;
    }
    double ballistics::get_MAX_distanse()
    {
        double distance = 0;
        double sight = 0;
        const double dt = 0.001;
        const double accuracy = 100000;
        double Vx;
        double Vy;
        double dVx;
        double dVy;
        double X;
        double Y;
        double dX;
        double dY;
        double V_x;
        double V_y;
        do {
            Vx = arrow_->get_arrow_speed() * std::cos(sight);
            Vy = arrow_->get_arrow_speed() * std::sin(sight);
            X = 0;
            Y = 0;
            for (int i = 1; i < accuracy; i++)
            {
                V_x = Vx;
                V_y = Vy;
                dx_dy(dVx, dVy, Vx, Vy, dt);
                Vx = Vx + dVx;
                Vy = Vy + dVy;
                dX = (Vx + V_x) / 2 * dt;
                dY = (Vy + V_y) / 2 * dt;
                X = X + dX;
                Y = Y + dY;
                if (Y < 0)
                {
                    if (distance < (X - dX))
                    {
                        distance = (X - dX);
                    }
                    break;
                }
            }
            sight += 0.001;
        } while (sight < pi / 2);
        return distance;
    }
    void ballistics::set_normal_sights()
    {
        double value;
        for (int i = 1; i < 101; i++)
        {
            value = get_normal_sight(i);
            compound_bow_->set_sight(value, i);
        }
    }
    void ballistics::show_MAX_distanse()
    {
        cout << "Максимальная дальность выстрела " << get_MAX_distanse() << " м.\n";
    }
    void ballistics::show_normal_sights()
    {
        cout << "\n";
        cout.width(25); cout << "<Дистанция>";
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
    ballistics::ballistics()
    {
        arrow_ = new arrow;
        compound_bow_ = new compound_bow;
        target_ = new target;
        MAX_distanse = get_MAX_distanse();
        compound_bow_->set_18m_sight(get_normal_sight(18.));
        set_normal_sights();
    }
    ballistics::~ballistics()
    {
        delete arrow_;
        delete compound_bow_;
        delete target_;
    }
