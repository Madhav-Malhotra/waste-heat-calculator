// @file         - test_scripts.cpp
// @brief        - Testing functions for helper functions.
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-10-14
// @version      - 0.0.0
// =======================================================================================


#include <iostream>
#include "test_data.hpp"



void test_water_mass_weight() {
  // Test water_mass_weight function
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
        << " mass is " << mass << std::endl;
    }
  }
}