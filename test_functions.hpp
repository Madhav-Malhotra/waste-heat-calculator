// @file         - test_scripts.cpp
// @brief        - Testing functions for helper functions.
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-10-14
// @version      - 0.0.3
// @since 0.0.0  - Added test functions for all the functions in helper file.
// =======================================================================================


#include <iostream>
#include "test_data.hpp"


// Test function for water_mass_weight() --> defined in "helper_functions.cpp"
void test_water_mass_weight() {
  // Get num inputs
  int i_max = sizeof(TEST_weight_water_container) / sizeof(double);
  int j_max = sizeof(TEST_weight_container) / sizeof(double);

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double mass = water_mass_weight(TEST_weight_container[j], TEST_weight_water_container[i]);

      // Show results
      std:: cout << "With weight_container " << TEST_weight_container[j] 
        << " and weight_water_container " << TEST_weight_water_container[i] 
        << ", mass is " << mass << std::endl;
    }
  }
}


// Test function for water_mass_volume() --> defined in "helper_functions.cpp"
void test_water_mass_volume() {
  // Get num inputs
  int i_max = sizeof(TEST_volume) / sizeof(double);

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    // Get return
    double mass = water_mass_volume(TEST_volume[i]);

    // Show results
    std:: cout << "With volume " << TEST_volume[i]
      << ", mass is " << mass << std::endl;
  }
}


// Test function for energy_transferred() --> defined in "helper_functions.cpp"
void test_energy_transferred() {
  // Get num inputs
  int i_max = sizeof(TEST_mass) / sizeof(double);
  int j_max = sizeof(TEST_temp_array) / sizeof(TEST_temp_array[0]);  

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double energy = energy_transferred(TEST_mass[i], TEST_temp_array[j]);

      // Show results
      std:: cout << "With mass " << TEST_mass[i] 
        << ", initial temp " << TEST_temp_array[j][0] 
        << ", and final temp " << TEST_temp_array[j][1]
        << ", energy is " << energy << std::endl;
    }
  }
}