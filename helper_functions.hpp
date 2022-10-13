// @file         - helper_functions.hpp
// @brief        - Physics and math functions for calculating the efficiency of a stove
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-09-21
// @version      - 0.7.1
// @since 0.7.0  - Minor syntax errors fixed
// @since 0.6.0  - Added parameter assertions and minor bug fixes
// @since 0.5.0  - Split into header files.
// @since 0.4.0  - Defined functions involving arrays and data storage
// @since 0.3.0  - Defined physics functions in file
// @since 0.2.0  - Defined physical constants
// @since 0.1.0  - Created file and outlined functions to include
// =======================================================================================



#include <cassert> 


// FUNCTION DECLARATIONS
float water_mass_weight(float weight_container, float weight_water_container);
float water_mass_volume(float volume);
void add_to_array(float temp_datapoint, float* temp_array, int temp_array_size, float* new_array);
float energy_transferred(float water_mass, float* temp_array, int temp_array_size);
float power(float energy, float time);
float efficiency(float useful_power, float rated_power);
float annual_energy(float power, float daily_use, int yearly_use);
float waste_energy(float energy, float efficiency);
float energy_variable_cost(float energy, float unit_price);
float ROI(float initial_cost, float annual_savings);



// FUNCTION DEFINITIONS


// @brief                         - Get the mass of the water with weight measurements
// @param weight_container        - Weight of the container without water [g]
// @param weight_water_container  - Weight of the container with water [g]
// @return                        - Mass of the water [kg]
float water_mass_weight(float weight_container, float weight_water_container) {
  // Check inputs
  assert( weight_container > 0 
    && "The weight of the container should be over 0 grams.");
  assert( weight_water_container > 0 
    && "The weight of the container and water should be over 0 grams.");

  float weight_water = (weight_water_container - weight_container) / 1000;
  return weight_water;
}


// @brief                         - Get the mass of the water with volume measurements
// @param volume                  - Volume of water used [mL]
// @return                        - Mass of the water [kg]
float water_mass_volume(float volume) {
  // Check inputs
  assert( volume > 0 
    && "The volume of the water should be over 0 mL.");

  return (volume / 1000) * WATER_DENSITY;
}


// @brief                 - Add new temperature datapoint to existing aray
// @param temp_array      - array with temperature measurements over time
// @param temp_array_size - number of temperature measurements (so far)
// @param temp_datapoint  - new temperature measurement to add to array [Celsius]
// @param new_array       - new array with capacity of temp_array_size + 1
// @return                - array with new temperature measurement added to existing ones
void add_to_array(float temp_datapoint, float* temp_array, int temp_array_size, float* new_array) {
  // Check inputs
  assert( temp_datapoint > -20 && temp_datapoint < 115 
    && "The temperature should be between -20 and 115 degrees celsius.");
  assert( temp_array_size >= 0 && temp_array_size <= 1000 
    && "The temperature array should have between 0 and 1000 measurements.");
  assert( sizeof(temp_array) / sizeof(float) == temp_array_size 
    && "The temperature array should have the same size as temp_array_size");
  assert( sizeof(new_array) / sizeof(float) == (temp_array_size + 1) 
    && "The new array should have a size that is one larger than the temperature array");

  // Transfer existing datapoints to it
  for (int i = 0; i < temp_array_size; i++) {
    *(new_array + i) = *(temp_array + i);
  }

  // Add new datapoint to it
  *(new_array + temp_array_size) = temp_datapoint;

  return;
}


// @brief                 - Find useful energy for heating water
// @param temp_array      - array with temperature measurements over time
// @param temp_array_size - number of temperature measurements
// @param water_mass      - mass of water in kilograms
// @return                - energy transferred to water in joules
// @equation              - Q = m * c * T
float energy_transferred(float water_mass, float* temp_array, int temp_array_size) {
  // Check inputs
  assert(water_mass > 0 
    && "The mass of the water should be over 0 kg.");
  assert(temp_array_size >= 2 
    && "There should be at least two temperature measurements.");

  // Get change in first and last temperature datapoint
  float change_temperature = *temp_array - *(temp_array + temp_array_size - 1);
  
  // Multiply that by the mass of the water and the specific heat capacity (constant)
  float energy = water_mass * WATER_HEAT_CAPACITY * change_temperature;

  return energy;
}


// @brief                - Calculates energy consumption over time
// @param energy         - joules of energy consumed
// @param time           - seconds of time passed
// @return               - watts of power 
// @equation             - P = E / t
float power(float energy, float time) {
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
float efficiency(float useful_power, float rated_power) {
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
float annual_energy(float power, float daily_use, int yearly_use) {
  // Check inputs
  assert(power > 0 
    && "The energy consumed should be greater than 0 joules.");
  assert(daily_use >= 0 && daily_use <= 24 
    && "The hours of daily stove use should be at least 0.");
  assert(yearly_use >= 0 && yearly_use <= 365 
    && "The days of annual stove use should be at least 0");


  float time_in_seconds = 3600 * daily_use * yearly_use;
  return power * time_in_seconds;
}


// @brief                - Calculates wasted portion of energy consumption 
// @param energy         - joules of total energy consumption
// @param efficiency     - unitless ratio of waste energy to total energy consumption
// @return               - joules of energy wasted per year
// @equation             - Q = E * (1 - Eff)
float waste_energy(float energy, float efficiency) {
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
float energy_variable_cost(float energy, float unit_price) {
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
float ROI(float initial_cost, float annual_savings) {
  // Check inputs
  assert(initial_cost >= 0 
    && "The initial cost should be at least $0.");
  assert(annual_savings > 0 
    && "The amount of money saved per year should be over $0.");

  return initial_cost / annual_savings;
}