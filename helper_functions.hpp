// @file         - helpers.hpp
// @brief        - Physics and math functions for calculating the efficiency of a stove
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-09-21
// @version      - 0.6.0
// @since 0.5.0  - Split into header files.
// @since 0.4.0  - Defined functions involving arrays and data storage
// @since 0.3.0  - Defined physics functions in file
// @since 0.2.0  - Defined physical constants
// @since 0.1.0  - Created file and outlined functions to include
// =======================================================================================



// FUNCTION DECLARATIONS
float water_mass_weight(float weight_container, float weight_water_container);
float water_mass_volume(float volume);
float* temp_to_array(float temp_datapoint, float* temp_array, int temp_array_size);
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
// @return                        - Mass of the water [g]
float water_mass_weight(float weight_container, float weight_water_container) {
  float weight_water = weight_water_container - weight_container;
  return weight_water / GRAV_ACCELERATION;
}


// @brief                         - Get the mass of the water with volume measurements
// @param volume                  - Volume of water used [L]
// @return                        - Mass of the water [g]
float water_mass_volume(float volume) {
  return volume * WATER_DENSITY;
}


// @brief                 - Add new temperature datapoint to existing aray
// @param temp_array      - array with temperature measurements over time
// @param temp_array_size - number of temperature measurements (so far)
// @param temp_datapoint  - new temperature measurement to add to array
// @return                - array with new temperature measurement added to existing ones
float* temp_to_array(float temp_datapoint, float* temp_array, int temp_array_size) {
  // Make new array
  float new_array[temp_array_size + 1];

  // Transfer existing datapoints to it
  for {int i = 0; i < temp_array_size + 1; i++} {
    new_array[i] = *(temp_array + i);
  }

  // Add new datapoint to it
  new_array[temp_array_size] = temp_datapoint;

  return new_array;
}


// @brief                 - Find useful energy for heating water
// @param temp_array      - array with temperature measurements over time
// @param temp_array_size - number of temperature measurements
// @param water_mass      - mass of water in kilograms
// @return                - energy transferred to water in joules
// @equation              - Q = m * c * T
float energy_transferred(float water_mass, float* temp_array, int temp_array_size) {
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
  return energy / time;
}


// @brief                - Calculates ratio of useful heat to waste heat
// @param useful_power   - watts of power transferred to boiling water
// @param rated_power    - total watts of power consumed
// @return               - unitless ratio of useful power to total power
// @equation             - Eff = P_out / P_in
float efficiency(float useful_power, float rated_power) {
  return useful_power / rated_power;
}


// @brief                - Calculates energy consumed per year
// @param power          - watts of power consumed per second
// @param daily_use      - hours stove is used per day
// @param yearly_use     - days stove is used per year
// @return               - joules of energy consumed per year
// @equation             - Q = P * t
float annual_energy(float power, float daily_use, int yearly_use) {
  int time_in_seconds = 3600 * daily_use * yearly_use;
  return power * time_in_seconds;
}


// @brief                - Calculates wasted portion of energy consumption 
// @param energy         - joules of total energy consumption
// @param efficiency     - unitless ratio of waste energy to total energy consumption
// @return               - joules of energy wasted per year
// @equation             - Q = E * (1 - Eff)
float waste_energy(float energy, float efficiency) {
  return energy * (1 - efficiency);
}


// @brief                - Calculates variable cost from energy consumption 
// @param energy         - joules of total energy consumption
// @param unit_price     - price of energy in $CAD per kilowatt-hour
// @return               - cost of energy consumption in $CAD
float energy_variable_cost(float energy, float unit_price) {
  return energy * unit_price;
}


// @brief                - Calculates years of use before breaking even on initial investment 
// @param initial_cost   - upfront price in $CAD for purchasing stove 
// @param annual_savings - cost of waste energy consumption avoided per year
// @return               - Number of years until annual savings = initial cost
float ROI(float initial_cost, float annual_savings) {
  return initial_cost / annual_savings;
}