#include <iostream>

// CONSTANTS
#define GRAV_ACCELERATION 9.807       // [ m / (s^2)   ]
#define WATER_DENSITY 997.77          // [ kg / (m^3)  ]
#define WATER_HEAT_CAPACITY 4.186     // [ J / g / K   ]
#define DAILY_USE 2.0                 // [ hours / day ]
#define YEARLY_USE 365                // [ days / year ]
#define UNIT_PRICE 0.13               // [ $ / kWh     ]
#define ALT_RATED_POWER 1700.0        // [ W / hour    ]
#define ALT_INITIAL_COST 944.0        // [ $CAD        ]
#define ALT_REBATE_PERCENT 0.25       // [ %           ]



// FUNCTION DECLARATIONS
int main();
float water_mass_weight(float weight);
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
int main() {
  return 0;
}

float water_mass_weight(float weight) {
  return 0;
}

float water_mass_volume(float volume) {
  return 0;
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