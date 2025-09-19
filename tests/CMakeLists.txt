cmake_minimum_required(VERSION 3.10)

# Create test executable
add_executable(financial_tests
    test_options.cpp
    test_black_scholes.cpp
    test_binomial.cpp
    test_monte_carlo.cpp
    test_greeks.cpp
)

target_link_libraries(financial_tests financial_valuation)

# Add test
add_test(NAME FinancialTests COMMAND financial_tests)