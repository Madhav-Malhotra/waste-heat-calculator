// @file         - main.cpp
// @brief        - Getting input from users and returning output
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-10-11
// @version      - 0.2.0
// @since 0.1.0  - Tested all helper functions and included declarations
// @since 0.0.0  - Created file, created main, and imported libraries
// =======================================================================================

#include "constants.cpp"
#include "helper_functions.hpp"
#include <iostream>

int main();

// HELPER FUNCTION DECLARATIONS
double water_mass_weight(double weight_container,
                         double weight_water_container);
double water_mass_volume(double volume);
void add_to_array(double temp_datapoint, double *temp_array,
                  int temp_array_size, double *new_array);
double energy_transferred(double water_mass, double *temp_array,
                          int temp_array_size);
double power(double energy, double time);
double efficiency(double useful_power, double rated_power);
double annual_energy(double power, double daily_use, int yearly_use);
double waste_energy(double energy, double efficiency);
double energy_variable_cost(double energy, double unit_price);
double ROI(double initial_cost, double annual_savings);

int main() { 
  return 0; 
}