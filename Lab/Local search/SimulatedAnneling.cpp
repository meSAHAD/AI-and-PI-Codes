#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_CITIES 4

// The graph from your image, represented as a distance matrix.
// Cities: 0=A, 1=B, 2=C, 3=D
int distances[NUM_CITIES][NUM_CITIES] = {
    {0, 4, 6, 3}, // Distances from A
    {4, 0, 8, 7}, // Distances from B
    {6, 8, 0, 5}, // Distances from C
    {3, 7, 5, 0}  // Distances from D
};

// This function calculates the total distance of a given tour.
int calculateTourCost(int tour[])
{
    int cost = 0;
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        cost += distances[tour[i]][tour[i + 1]];
    }
    // Add the cost of returning to the start city to complete the tour.
    cost += distances[tour[NUM_CITIES - 1]][tour[0]];
    return cost;
}

// Helper function to print a tour's path and cost.
void printTour(int tour[], char *title)
{
    printf("%s: ", title);
    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%c -> ", tour[i] + 'A'); // Convert city index (0,1,2,3) to letter (A,B,C,D)
    }
    printf("%c ", tour[0] + 'A');
    printf("(Cost: %d)\n", calculateTourCost(tour));
}

void simulatedAnnealingTSP()
{
    // --- INITIALIZATION ---
    int current_tour[NUM_CITIES] = {0, 1, 2, 3}; // Start with a simple tour A->B->C->D
    int best_tour[NUM_CITIES];

    // Copy the starting tour to the best_tour
    for (int i = 0; i < NUM_CITIES; i++)
        best_tour[i] = current_tour[i];

    int current_cost = calculateTourCost(current_tour);
    int best_cost = current_cost;

    printTour(current_tour, "Initial Tour");

    // Algorithm parameters
    double temperature = 10000.0;
    double cooling_rate = 0.999;

    // --- MAIN LOOP ---
    while (temperature > 1.0)
    {
        // 1. Create a new neighbor tour by swapping two cities.
        int new_tour[NUM_CITIES];
        for (int i = 0; i < NUM_CITIES; i++)
            new_tour[i] = current_tour[i];

        // Pick two random positions in the tour to swap.
        int pos1 = rand() % NUM_CITIES;
        int pos2 = rand() % NUM_CITIES;

        // Swap them
        int temp = new_tour[pos1];
        new_tour[pos1] = new_tour[pos2];
        new_tour[pos2] = temp;

        // 2. Calculate the costs.
        int new_cost = calculateTourCost(new_tour);

        // 3. Decide whether to move to the new tour.
        // We want to MINIMIZE cost, so a lower cost is better.
        int cost_delta = new_cost - current_cost;

        // If the new tour is better (shorter), always accept it.
        // Or, if it's worse, accept it with a certain probability.
        double probability = exp(-cost_delta / temperature);
        double random_chance = (double)rand() / RAND_MAX;

        if (cost_delta < 0 || random_chance < probability)
        {
            for (int i = 0; i < NUM_CITIES; i++)
                current_tour[i] = new_tour[i];
            current_cost = new_cost;
        }

        // 4. Keep track of the best solution found so far.
        if (current_cost < best_cost)
        {
            for (int i = 0; i < NUM_CITIES; i++)
                best_tour[i] = current_tour[i];
            best_cost = current_cost;
        }

        // 5. Cool the temperature.
        temperature *= cooling_rate;
    }

    printf("\nCooling complete.\n");
    printTour(best_tour, "Best tour found");
}

int main()
{
    // srand(time(NULL));
    simulatedAnnealingTSP();
    return 0;
}
