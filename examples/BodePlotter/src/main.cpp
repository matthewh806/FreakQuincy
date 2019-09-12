#include <vector>
#include <math.h>

#include "gnuplot-iostream.h"
#include "engine/filters/SecondOrderButterworthLowPassFilter.hpp"

/*
    This commented out main fn is just for an example of how gnuplot-iostream works.

    int main(int argc, char* argv[]) {
        std::unique_ptr<engine::filters::SecondOrderButterworthLowPassFilter> filter = 
                std::unique_ptr<engine::filters::SecondOrderButterworthLowPassFilter>(
                    new engine::filters::SecondOrderButterworthLowPassFilter(220, 0.1)
        );

        std::vector<std::pair<double, double>> xy_values;
        Gnuplot gp;
        
        int points = 10000;
        double inc = 2*M_PI / (double)points;

        for(int i = 0; i < points; i++) {
            double theta = i*inc;
            xy_values.push_back(std::make_pair(theta, sin(theta)));
        }

        gp << "set xrange [0:6.283]\nset yrange [-1:1]\n";
        gp << "plot '-' with lines\n";
        gp.send1d(xy_values);

        return 0;
    }
*/

int main(int argc, char* argv[]) {
    std::unique_ptr<engine::filters::SecondOrderButterworthLowPassFilter> filter = 
            std::unique_ptr<engine::filters::SecondOrderButterworthLowPassFilter>(
                new engine::filters::SecondOrderButterworthLowPassFilter(220, 0.1)
    );

    Gnuplot gp;
    std::vector<std::pair<double, double>> xy_values;
    
    int points = 1000;
    double inc = 20000 / (double)points;

    for(int i = 0; i < points; i++) {
        double w = 2 * M_PI * (i * inc);
        xy_values.push_back(std::make_pair(log10(w), 20 * log10(filter->calculateTransferFunction(w))));
    }

    gp << "set xrange [2:6]\nset yrange[-30:0]\n";
    gp << "plot '-' with lines\n";
    gp.send1d(xy_values);

    return 0;
}