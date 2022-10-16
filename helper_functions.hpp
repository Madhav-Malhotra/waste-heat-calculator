// @file         - helper_functions.hpp
// @brief        - Physics and math functions for calculating the efficiency of a stove
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-09-21
// @version      - 1.0.3
// @since 0.7.3  - Removed add_to_array() function. Only tracking initial and final temperature.
// @since 0.7.0  - Tested functions. Fixed syntax errors and precision errors.
// @since 0.6.0  - Added parameter assertions and minor bug fixes
// @since 0.5.0  - Split into header files.
// @since 0.4.0  - Defined functions involving arrays and data storage
// @since 0.3.0  - Defined physics functions in file
// @since 0.2.0  - Defined physical constants
// @since 0.1.0  - Created file and outlined functions to include
// =======================================================================================



#include <cassert> 



// FUNCTION DEFINITIONS


// @brief                         - Get the mass of the water with weight measurements
// @param weight_container        - Weight of the container without water [g]
// @param weight_water_container  - Weight of the container with water [g]
// @return                        - Mass of the water [kg]
double water_mass_weight(double weight_container, double weight_water_container) {
  // Check inputs
  assert( weight_container > 0 
    && "The weight of the container should be over 0 grams.");
  assert( weight_water_container > 0 
    && "The weight of the container and water should be over 0 grams.");

  double weight_water = (weight_water_container - weight_container) / 1000;
  return weight_water;
}


// @brief                         - Get the mass of the water with volume measurements
// @param volume                  - Volume of water used [mL]
// @return                        - Mass of the water [kg]
double water_mass_volume(double volume) {
  // Check inputs
  std::cout << volume << std::endl;
  assert( volume > 0 
    && "The volume of the water should be over 0 mL.");

  return (volume / 1000) * (WATER_DENSITY / 1000);
}


// @brief                 - Find useful energy for heating water
// @param temp_array      - array with initial and final temperature measurements
// @param water_mass      - mass of water in kilograms
// @return                - energy transferred to water in joules
// @equation              - Q = m * c * T
double energy_transferred(double water_mass, double* temp_array) {
  // Check inputs
  assert(water_mass > 0 
    && "The mass of the water should be over 0 kg.");

  // Get change in first and last temperature datapoints
  double change_temperature = *(temp_array + 1) - *temp_array;
  
  // Multiply that by the mass of the water and the specific heat capacity (constant)
  double energy = water_mass * (WATER_HEAT_CAPACITY * 1000) * change_temperature;

  return energy;
}


// @brief                - Calculates energy consumption over time
// @param energy         - joules of energy consumed
// @param time           - seconds of time passed
// @return               - watts of power 
// @equation             - P = E / t
double power(double energy, double time) {
  // Check inputs
  assert(energy > 0 
    && "The energy consumed should be greater than 0 Joules.");
  assert(time > 0 
    && "The time passed should be over 0 seconds.");

  return energy / time;
}


// @brief                - Calculates ratio of useful heat to waste heat
// @param useful_power   - watts of power transferred to boiling water
// @param rated_power    - total watts of power consumed
// @return               - unitless ratio of useful power to total power
// @equation             - Eff = P_out / P_in
double efficiency(double useful_power, double rated_power) {
  // Check inputs
  assert(useful_power > 0 
    && "The power transferred to water should be over 0 joules.");
  assert(rated_power > 0 
    && "The power consumed by the stove should be over 0 joules.");

  return useful_power / rated_power;
}


// @brief                - Calculates energy consumed per year
// @param power          - watts of power consumed per second
// @param daily_use      - hours stove is used per day
// @param yearly_use     - days stove is used per year
// @return               - joules of energy consumed per year
// @equation             - Q = P * t
double annual_energy(double power, double daily_use, int yearly_use) {
  // Check inputs
  assert(power > 0 
    && "The energy consumed should be greater than 0 joules.");
  assert(daily_use >= 0 && daily_use <= 24 
    && "The hours of daily stove use should be at least 0.");
  assert(yearly_use >= 0 && yearly_use <= 365 
    && "The days of annual stove use should be at least 0");


  double time_in_seconds = 3600 * daily_use * yearly_use;
  return power * time_in_seconds;
}


// @brief                - Calculates wasted portion of energy consumption 
// @param energy         - joules of total energy consumption
// @param efficiency     - unitless ratio of waste energy to total energy consumption
// @return               - joules of energy wasted per year
// @equation             - Q = E * (1 - Eff)
double waste_energy(double energy, double efficiency) {
  // Check inputs
  assert(energy > 0 
    && "The amount of energy used should be at least 0 joules.");
  assert(efficiency >= 0 && efficiency <= 1 
    && "The efficency should be between 0 and 1.");


  return energy * (1 - efficiency);
}


// @brief                - Calculates variable cost from energy consumption 
// @param energy         - joules of total energy consumption
// @param unit_price     - price of energy in $CAD per kilowatt-hour
// @return               - cost of energy consumption in $CAD
double energy_variable_cost(double energy, double unit_price) {
  // Check inputs
  assert(energy > 0 
    && "The amount of energy used should be at least 0 joules.");
  assert(unit_price >= 0 
    && "The unit price of energy should $0 / kwH.");

  return energy * unit_price;
}


// @brief                - Calculates years of use before breaking even on initial investment 
// @param initial_cost   - upfront price in $CAD for purchasing stove 
// @param annual_savings - cost of waste energy consumption avoided per year
// @return               - Number of years until annual savings = initial cost
double ROI(double initial_cost, double annual_savings) {
  // Check inputs
  assert(initial_cost >= 0 
    && "The initial cost should be at least $0.");
  assert(annual_savings > 0 
    && "The amount of money saved per year should be over $0.");

  return initial_cost / annual_savings;
}