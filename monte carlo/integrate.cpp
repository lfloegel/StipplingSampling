#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <array>
#include <iterator>

//uniform pdf: 
//return (b - a) / (double)n * sum 
//f(x_i) 
//inversion method: 
//p(x) = c * f(x) = c * sin(x) 
//integrate 0 to pi/2 (p(x)) = 1 integrate 0 to pi/2 (c * sin(x)) = 1
//p(x) = c * integrate 0 to pi/2 (sin(x)) = 1
//P(x) = integrate 0 to x (p(x)) 
//E = P(x) 
//x = P^-1(E)
//pass in sample to function
//draw sample Xi from pdf:
//compute cdf: P(x) = integrate 0 to x (p(x)dx)
//compute inverse: P^-1(x)
//  solve for u in P(x) = u 
//obtain uniformly distributed random number: E ~ U(0, 1]
//compute Xi: Xi = P^-1(E)

//f(x_i): 
//sin(x_i)

//make a pdf method for each pdf using inversion method
//calculate x_i from that pdf

//store integration into array<>

//pdf proportional to y
//use functiomn of y in inversion method
//plus in value into f(x_i)
//uniform pdf okay as not using pdf explicitly in equation

//uniform pdf:
//x_i = math.random() * (b-a) + a
//sum += f(x_i)

//cx = 8 / pi^2
//p(x) = 8x / pi^2
//P(x) = 4x^2 / pi^2
//E = 4x^2 / pi^2 
//pi^2(E)= 4x^2
//pi^2(E) / 4 = x^2
//x = sqrt(pi^2(E) / 4)
//E = pseudo_random_generator

//csin(x) = 1
//p(x) = sin(x)
//P(x) = 1 - cos(x)
//E = 1 - cos(x)
//E - 1 = cos(x)
//x = cos^-1(E - 1)
//E = pseudo_random_generator

//p(x) = 1 / (b - a)
//P(X) = x - a / b - a
//E = x - a / b - a
//E(b - a) = x - a
//x = E(b - a) + a

//use it to calculate random vairable
//plug in random variable into pdf

//E
double pseudo_random_generator() 
{
    srand(static_cast<unsigned int>(clock()));
    return ((double)rand()) / ((double)RAND_MAX + 1.0);
} 

//f(x) = sin(x)
double f(double random_variable)
{
    return sin(random_variable);
}

//uniform_pdf
double uniform_random_variable(double a, double b) 
{
    return pseudo_random_generator() * (double)(b - a) + (double)a;
}

double pdf(double a, double b) 
{
    return 1 / (b - a);
}

//x_pdf
double x_random_variable(double a, double b)
{
    return sqrt((pow(M_PI, 2) * pseudo_random_generator()) / 4);
}

double x_pdf(double x_i) 
{
    return (8 * x_i) / pow(M_PI, 2);
}

//sinx_pdf
double sinx_random_variable(double a, double b)
{
    return acos(pseudo_random_generator() - 1);
}

double sinx_pdf(double x_i) 
{
    return sin(x_i);
}

/*double integrate_monte_carlo(double a, double b, double n)
{
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        double x_i = uniform_pdf(a, b);
        sum += f(x_i);
    }

    return (double)(b - a) / (double)n * sum;
}*/

double integrate_monte_carlo(double a, double b, double n, char c) 
{
    double sum = 0; 

    switch(c)
    {
        case '1':
            for(int i = 0; i < n; i++) 
            {
                double x_i = uniform_random_variable(a, b); 
                sum += f(x_i) / pdf(a, b); 
            }
        break;
        case '2':
            for(int i = 0; i < n; i++) 
            {
                double x_i = x_random_variable(a, b); 
                sum += f(x_i) / x_pdf(x_i); 
            }
        break;
        case '3':
            std::cout << "entered" << '\n';
            for(int i = 0; i < n; i++) 
            {
                double x_i = sinx_random_variable(a, b); 
                sum += f(x_i) / sinx_pdf(x_i); 
            }
        break;
        default:
            std::cout << "No valid pdf given" << '\n';
            break;
    }
    return 1 / (double)n * sum; 
}

int main () 
{
    double a = 0, b = M_PI/2, n = 1;
    std::array<double, 31> uniform_integral;
    std::array<double, 31> x_integral;
    std::array<double, 31> sinx_integral;

    for(int i = 0; i <= 30; i++)
    {
        std::cout << '\n' << "entered" << i << std::endl;
        uniform_integral[i] = integrate_monte_carlo(a, b, n, '1'); 
        x_integral[i] = integrate_monte_carlo(a, b, n, '2');
        sinx_integral[i] = integrate_monte_carlo(a, b, n, '3');
        std::cout << x_integral[i] << std::endl;
        n *= 2;
    } 

    std::ofstream dataFile1("uniform_integral.dat");
    std::copy(uniform_integral.begin(), uniform_integral.end(), std::ostream_iterator<double>(dataFile1, " "));
    dataFile1.close();
    std::ofstream dataFile2("x_integral.dat");
    std::copy(x_integral.begin(), x_integral.end(), std::ostream_iterator<double>(dataFile2, " "));
    dataFile2.close();
    std::ofstream dataFile3("sinx_integral.dat");
    std::copy(sinx_integral.begin(), sinx_integral.end(), std::ostream_iterator<double>(dataFile3, " "));
    dataFile3.close();
    return 0;

}