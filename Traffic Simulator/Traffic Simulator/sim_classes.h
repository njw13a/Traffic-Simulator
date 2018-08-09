
#include <iostream>
#include <vector>
using namespace std;


class simulation
{
private:
    long time = 0;
    int car_chance;
    static double total_cars;
    static double waiting_cars;
    static int longest_line;
    static long total_wait;
public:
    simulation (long a, int b) {time = a; car_chance = b;}
    static void increment_cars() {total_cars++;}
    static void add_waiting(int car_count) {waiting_cars += car_count;}
    static void change_line(int car_count) {if(car_count > longest_line) longest_line = car_count;}
    double get_chance () {return car_chance;}
    static void add_wait_time( long wait_time ) {total_wait += wait_time;}
    void renderStats() {cout << "Total number cars created: " << total_cars << "\nAverage number of cars in simulator per time step: " << total_cars / time << "\nLongest line at a red light: " << longest_line << "\nAverage number of cars at a red light per time step: " << waiting_cars / time << "\nAverage time waited at red light: " << total_wait / time << endl;}
};
double simulation::total_cars = 0;
double simulation::waiting_cars = 0;
int simulation::longest_line = 0;
long simulation::total_wait = 0;

class car
{
private:
	double time_active = 0;
    int location = 0;
    int direction;
public:
    car (int c) {direction = c;}
	~car ();
    void increment_time() {time_active++;}
	double get_time () {return time_active;}
    int get_location () {return location;}
    void drive()
    {
        location++;
    }
};

class street
{
private:
    vector <car*> carVector;
	string name;
	
	int car_count = 0;
    int active_light;
    double green_length;
    double red_length;
    double timer;
public:
    street (string a, int b, double c, double d, int e) {name = a; direction = b; car_count = 0; green_length = c; red_length = c + 6; timer = d; active_light = e;}
	~street ();
	string get_name () {return name;}
    int direction;
	int get_cars (){return car_count;}
    void add_car(car* automobile) {carVector.push_back(automobile); car_count++; simulation::increment_cars();}
    void remove_car() {simulation::add_wait_time((*carVector.begin()) -> get_time() - 44); carVector.erase(carVector.begin());}
    bool canSpawn() {if(carVector.empty() || carVector.back() -> get_location() > 3) return true; return false;}
    void change ()
    {
        if (active_light == 0)
        {
            active_light = 1;
            timer = 6;
        }
        else if(active_light == 1)
        {
            active_light = 2;
            timer = red_length;
        }
        else
        {
            active_light = 0;
            timer = green_length;
            simulation::add_waiting(car_count);
            simulation::change_line(car_count);
        }
    }

    void decrement_timer() {if(timer == 0) change(); else timer--;}
    double get_time () {return timer;}
    
    void move_cars()
    {
        for(vector<car*>::reverse_iterator it = carVector.rbegin(); it != carVector.rend(); ++it)
        {
            (*it) -> increment_time();
            if((*it) -> get_location() > 20 || active_light == 0)
            {
                (*it) -> drive();
                if((*it) -> get_location() == 21)
                    car_count--;
                if((*it) -> get_location() == 45)
                    remove_car();
            }
            else if(active_light != 2 && (*it) -> get_location() < 20 && (*it) -> get_location() < car_count * 2)
            {
                (*it) -> drive();
            }
        }
    }
//    void move_cars()
//    {
//        for(vector<car*>::iterator it = carVector.end(); it != carVector.begin(); it--)
//        {
//            (*it) -> increment_time();
//            if((*it) -> get_location() > 20 || active_light == 0)
//            {
//                (*it) -> drive();
//                if((*it) -> get_location() == 21)
//                    car_count--;
//                if((*it) -> get_location() == 45)
//                    remove_car();
//            }
//            else if(active_light != 0 && (*it) -> get_location() < 20 && (*it) -> get_location() < car_count * 2)
//            {
//                (*it) -> drive();
//            }
//        }
//    }
};


