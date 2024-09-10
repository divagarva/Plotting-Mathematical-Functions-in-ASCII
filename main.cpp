#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional> // Include this to use std::function

const int WIDTH = 80;  // Width of the graph
const int HEIGHT = 20; // Height of the graph

// Function to plot a point on the console
void plotPoint(int x, int y, char graph[HEIGHT][WIDTH]) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        graph[HEIGHT - y - 1][x] = '*';
    }
}

// Function to plot the axes
void plotAxes(char graph[HEIGHT][WIDTH]) {
    // Plot X-axis
    for (int x = 0; x < WIDTH; ++x) {
        graph[HEIGHT / 2][x] = '-';
    }
    // Plot Y-axis
    for (int y = 0; y < HEIGHT; ++y) {
        graph[y][WIDTH / 2] = '|';
    }
    // Plot the origin
    graph[HEIGHT / 2][WIDTH / 2] = '+';
}

// Function to plot a mathematical function
void plotFunction(std::function<double(double)> func, double scaleX, double scaleY, char graph[HEIGHT][WIDTH]) {
    for (int x = 0; x < WIDTH; ++x) {
        double realX = (x - WIDTH / 2) / scaleX;
        double realY = func(realX);
        int y = static_cast<int>(realY * scaleY + HEIGHT / 2);
        plotPoint(x, y, graph);
    }
}

// Function to display the graph
void displayGraph(char graph[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            std::cout << graph[y][x];
        }
        std::cout << std::endl;
    }
}

int main() {
    char graph[HEIGHT][WIDTH];

    // Initialize graph with blank spaces
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            graph[y][x] = ' ';
        }
    }

    // Plot the axes
    plotAxes(graph);

    // Select the function to plot
    int choice;
    std::cout << "Select a function to plot:\n";
    std::cout << "1. Sine\n2. Cosine\n3. Quadratic (y = ax^2 + bx + c)\n";
    std::cin >> choice;

    if (choice == 1) {
        plotFunction(static_cast<double(*)(double)>(sin), 10.0, 5.0, graph); // Sine function with scaling
    } else if (choice == 2) {
        plotFunction(static_cast<double(*)(double)>(cos), 10.0, 5.0, graph); // Cosine function with scaling
    } else if (choice == 3) {
        // Quadratic function: ax^2 + bx + c
        double a, b, c;
        std::cout << "Enter coefficients a, b, c for y = ax^2 + bx + c: ";
        std::cin >> a >> b >> c;
        auto quadratic = [a, b, c](double x) {
            return a * x * x + b * x + c;
        };
        plotFunction(quadratic, 10.0, 0.1, graph); // Quadratic function with scaling
    } else {
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }

    // Display the graph
    displayGraph(graph);

    return 0;
}
