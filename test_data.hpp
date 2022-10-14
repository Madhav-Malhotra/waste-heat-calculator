// @file         - test_data.cpp
// @brief        - Hardcoded values to test functions with
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-10-11
// @version      - 0.2.1
// @since 0.2.0  - Adjusted some float data to double for increased precision.
// @since 0.1.0  - Created test cases for all input parameters
// @since 0.0.0  - Created file, organised functions to test.
// =======================================================================================



// @brief                         - Get the mass of the water with weight
// measurements
// @param weight_container        - Weight of the container without water [g]
// @param weight_water_container  - Weight of the container with water [g]
// @return                        - Mass of the water [kg]
// double water_mass_weight(double weight_container, double weight_water_container)
double TEST_weight_container[] = {0.010, 0.999, 1.00001, 55.0, 750.0, 1293.0};
double TEST_weight_water_container[] = {0.010, 0.011, 0.999,  1.00001,
                                       55.0,  750.0, 1293.0, 1293.1};

// @brief                         - Get the mass of the water with volume
// measurements
// @param volume                  - Volume of water used [mL]
// @return                        - Mass of the water [kg]
// float water_mass_volume(float volume)
float TEST_volume[] = {0.010, 0.999, 1.00001, 55.0, 750.0, 1293.0};

// @brief                 - Add new temperature datapoint to existing aray
// @param temp_array      - array with temperature measurements over time
// @param temp_array_size - number of temperature measurements (so far)
// @param temp_datapoint  - new temperature measurement to add to array
// [Celsius]
// @param new_array       - new array with capacity of temp_array_size + 1
// @return                - array with new temperature measurement added to
// existing ones void add_to_array(float temp_datapoint, float* temp_array, int
// temp_array_size)
float TEST_temp_datapoint[] = {-19.99, -3.2, -0.0001, 0.0,    0.0001,
                               0.34,   7.89, 53.23,   99.999, 114.99};
// Initialise TEST_temp_array with the sizes specified below and default values.
int TEST_temp_array_size[] = {0, 3, 53, 1000};
// Initialise TEST_new_array with the sizes specified above and default values.

// @brief                 - Find useful energy for heating water
// @param temp_array      - array with temperature measurements over time
// @param temp_array_size - number of temperature measurements
// @param water_mass      - mass of water in kilograms
// @return                - energy transferred to water in joules
// @equation              - Q = m * c * T
// float energy_transferred(float water_mass, float* temp_array, int
// temp_array_size) {
float TEST_mass[] = {0.0001, 0.3, 1.0001, 53.0, 12912.0};
// Reuse the TEST_temp_array and TEST_temp_array_size from above

// @brief                - Calculates energy consumption over time
// @param energy         - joules of energy consumed
// @param time           - seconds of time passed
// @return               - watts of power
// @equation             - P = E / t
// float power(float energy, float time)
float TEST_energy[] = {0.0001, 0.3, 1.0001, 53.0, 12912.0};
float TEST_time[] = {0.0001, 0.3, 1.0001, 53.0, 12912.0};

// @brief                - Calculates ratio of useful heat to waste heat
// @param useful_power   - watts of power transferred to boiling water
// @param rated_power    - total watts of power consumed
// @return               - unitless ratio of useful power to total power
// @equation             - Eff = P_out / P_in
// float efficiency(float useful_power, float rated_power)
float TEST_useful_power[] = {0.0001, 0.3, 1.0001, 53.0, 12912.0};
float TEST_rated_power[] = {0.0001, 0.3, 1.0001, 53.0, 12912.0};

// @brief                - Calculates energy consumed per year
// @param power          - watts of power consumed per second
// @param daily_use      - hours stove is used per day
// @param yearly_use     - days stove is used per year
// @return               - joules of energy consumed per year
// @equation             - Q = P * t
// float annual_energy(float power, float daily_use, int yearly_use)
float TEST_power[] = {0.0001, 0.3, 1.0001, 53.0, 12912.0};
float TEST_daily_use[] = {0.0001, 0.3, 1.0001, 1.5, 24.0};

// @brief                - Calculates wasted portion of energy consumption
// @param energy         - joules of total energy consumption
// @param efficiency     - unitless ratio of waste energy to total energy
// consumption
// @return               - joules of energy wasted per year
// @equation             - Q = E * (1 - Eff)
// float waste_energy(float energy, float efficiency)
// Reuse TEST_energy from above
float TEST_efficency[] = {0.0001, 0.02, 0.5, 0.799, 0.9999};

// @brief                - Calculates variable cost from energy consumption
// @param energy         - joules of total energy consumption
// @param unit_price     - price of energy in $CAD per kilowatt-hour
// @return               - cost of energy consumption in $CAD
// float energy_variable_cost(float energy, float unit_price)
// Reuse TEST_energy from above
float TEST_unit_price[] = {0.0001, 0.12, 0.9999, 2.231, 15.23, 100.12, 12000.1};

// @brief                - Calculates years of use before breaking even on
// initial investment
// @param initial_cost   - upfront price in $CAD for purchasing stove
// @param annual_savings - cost of waste energy consumption avoided per year
// @return               - Number of years until annual savings = initial cost
// float ROI(float initial_cost, float annual_savings)
float TEST_initial_cost[] = {0.0001, 0.12,   0.9999, 2.231,
                             15.23,  100.12, 12000.1};
float TEST_annual_savings[] = {0.0001, 0.12,   0.9999, 2.231,
                               15.23,  100.12, 12000.1};