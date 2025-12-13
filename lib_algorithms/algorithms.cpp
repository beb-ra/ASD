#include <cmath>
#include "algorithms.h"

#define EPSILON 0.00000001
#define PI 3.14

double my_sin(double x) {
    double rad = convert_to_radians(x);
    rad = fmod(rad, 2 * PI);
    if (rad > PI) rad -= 2 * PI;
    else if (rad < -PI) rad += 2 * PI;

    double res = rad;
    double term = rad;
    int n = 1;
    for (; abs(term) > EPSILON; n++) {
        term = -term * rad * rad / ((2 * n + 1) * (2 * n));
        res += term;
    }
    return res;
}

double my_cos(double x) {
    double rad = convert_to_radians(x);
    rad = fmod(rad, 2 * PI);
    if (rad > PI) rad -= 2 * PI;
    else if (rad < -PI) rad += 2 * PI;

    double res = 1.0;
    double term = 1.0;
    int n = 1;
    for (; abs(term) > EPSILON; n++) {
        term = -term * rad * rad / ((2 * n) * (2 * n - 1));
        res += term;
    }
    return res;
}

double my_tg(double x) {
    x = fmod(x, 360.0);
    if (x < 0) x += 360.0;
    if (my_abs(x - 90.0) < 1e-4 || my_abs(x - 270.0) < 1e-4)
        throw std::invalid_argument("Division by zero");
    return my_sin(x) / my_cos(x);
}

double my_abs(double x) {
	return x < 0 ? -x : x;
}

double convert_to_radians(double x) {
    return (x * PI) / 180;
}