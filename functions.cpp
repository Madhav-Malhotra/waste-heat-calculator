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
float* temp_to_array(float temp_datapoint);
float energy_transferred(float* temp_array, float water_mass);
float power(float energy, float time);
float efficiency(float useful_power, float rated_power);
float annual_energy(float power, float daily_use, int yearly_use);
float waste_energy(float energy, float efficiency);
float energy_running_cost(float energy, float unit_price);
float ROI(float initial_cost, float savings_per_year);



// FUNCTION DEFINITIONS
int main() {
  return 0;
}