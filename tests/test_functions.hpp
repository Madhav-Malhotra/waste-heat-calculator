// @file         - test_scripts.cpp
// @brief        - Testing functions for helper functions.
// @author       - Madhav Malhotra
// @author       - Cynthia Shen
// @date         - 2022-10-14
// @version      - 0.0.8
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

// Test function for power() --> defined in "helper_functions.cpp"
void test_power() {
  // Get num inputs
  int i_max = sizeof(TEST_energy) / sizeof(double);
  int j_max = sizeof(TEST_time) / sizeof(double);  

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double returned_power = power(TEST_energy[i], TEST_time[j]);

      // Show results
      std:: cout << "With energy " << TEST_energy[i] 
        << " and time " << TEST_time[j] 
        << ", power is " << returned_power << std::endl;
    }
  }
}

// Test function for efficency() --> defined in "helper_functions.cpp"
void test_efficiency() {
  // Get num inputs
  int i_max = sizeof(TEST_useful_power) / sizeof(double);
  int j_max = sizeof(TEST_rated_power) / sizeof(double);  

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double returned_efficiency = efficiency(TEST_useful_power[i], TEST_rated_power[j]);

      // Show results
      std:: cout << "With P_out " << TEST_useful_power[i] 
        << " and P_in " << TEST_rated_power[j] 
        << ", effiency is " << returned_efficiency << std::endl;
    }
  }
}

// Test function for annual_energy() --> defined in "helper_functions.cpp"
void test_annual_energy() {
  // Get num inputs
  int i_max = sizeof(TEST_power) / sizeof(double);
  int j_max = sizeof(TEST_daily_use) / sizeof(double);  
  int k_max = sizeof(TEST_yearly_use) / sizeof(int);

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      for (int k = 0; k < k_max; ++k) {
        // Get return
        double total_energy = annual_energy(TEST_power[i], TEST_daily_use[j], TEST_yearly_use[k]);
  
        // Show results
        std:: cout << "With power " << TEST_power[i] 
          << ", daily use " << TEST_daily_use[j] 
          << ", and yearly use " << TEST_yearly_use[k]
          << ", energy consumption is " << total_energy << std::endl;
      }
    }
  }
}

// Test function for test_waste_energy() --> defined in "helper_functions.cpp"
void test_waste_energy() {
  // Get num inputs
  int i_max = sizeof(TEST_energy) / sizeof(double);
  int j_max = sizeof(TEST_efficiency) / sizeof(double);  

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double waste_heat = waste_energy(TEST_energy[i], TEST_efficiency[j]);

      // Show results
      std:: cout << "With energy " << TEST_energy[i] 
        << " and efficiency " << TEST_efficiency[j] 
        << ", waste energy is " << waste_heat << std::endl;
    }
  }
}

// Test function for energy_variable_cost() --> defined in "helper_functions.cpp"
void test_energy_variable_cost() {
  // Get num inputs
  int i_max = sizeof(TEST_energy) / sizeof(double);
  int j_max = sizeof(TEST_unit_price) / sizeof(double);  

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double price = energy_variable_cost(TEST_energy[i], TEST_unit_price[j]);

      // Show results
      std:: cout << "With energy " << TEST_energy[i] 
        << " and unit price " << TEST_unit_price[j] 
        << ", running cost is " << price << std::endl;
    }
  }
}

// Test function for ROI() --> defined in "helper_functions.cpp"
void test_ROI() {
  // Get num inputs
  int i_max = sizeof(TEST_initial_cost) / sizeof(double);
  int j_max = sizeof(TEST_annual_savings) / sizeof(double);  

  // Go through all input combinations
  for (int i = 0; i < i_max; ++i) {
    for (int j = 0; j < j_max; ++j) {
      // Get return
      double years = ROI(TEST_initial_cost[i], TEST_annual_savings[j]);

      // Show results
      std:: cout << "With initial cost " << TEST_initial_cost[i] 
        << " and annual savings " << TEST_annual_savings[j] 
        << ", ROI is " << years << std::endl;
    }
  }
}