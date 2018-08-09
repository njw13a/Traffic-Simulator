#include "sim_classes.h"
#include <stdlib.h>

int main()
{
    int spawnChance, greenLength;
    long runTime;
	cout << "Input percent chance for car to spawn when possible (integer 1-100).\n";
	cin >> spawnChance;
    spawnChance = 100 - spawnChance;
	//function for car spawn chance will use if (math.rand(spawnChance) == 0) to determine whether or not the car will spawn
    cout << "Input length of green light as an integer.\n";
    cin >> greenLength;
    cout << "Input time to run.\n";
    cin >> runTime;
    
    simulation Simulator = simulation(runTime, spawnChance);
    
    street* streetArray[4];
    streetArray[0] = new street("North", 3, greenLength, greenLength, 0);
    streetArray[1] = new street("South", 1, greenLength, greenLength, 0);
    streetArray[2] = new street("East", 0, greenLength, greenLength + 4, 2);
    streetArray[3] = new street("West", 2, greenLength, greenLength + 4, 2);
    
    for(int i = 0; i < 4; i++)
    {
        car* newCar = new car(streetArray[i] -> direction);
        streetArray[i] -> add_car(newCar);
    }


    for( int i = 0; i < runTime; i++)
    {
        for(int a = 0; a < 4; a++)
        {
            if(streetArray[a] -> canSpawn())
            {
                
                if(rand() % (spawnChance + 1) == 0)
                {
                    car* newCar = new car(streetArray[a] -> direction);
                    streetArray[a] -> add_car(newCar);
                }
            }
            streetArray[a] -> decrement_timer();
            streetArray[a] -> move_cars();
        }
    }
    
    Simulator.renderStats();
}