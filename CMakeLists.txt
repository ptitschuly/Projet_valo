cmake_minimum_required(VERSION 3.10)
project(FinancialValuationLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Create the library
add_library(financial_valuation STATIC
    src/instrument.cpp
    src/option.cpp
    src/european_option.cpp
    src/american_option.cpp
    src/black_scholes.cpp
    src/binomial_tree.cpp
    src/monte_carlo.cpp
    src/greeks.cpp
    src/collateralized_product.cpp
    src/total_return_swap.cpp
    src/basket_total_return_forward.cpp
)

# Include directories for the library
target_include_directories(financial_valuation PUBLIC include)

# Create example executable
add_executable(example example.cpp)
target_link_libraries(example financial_valuation)

# Enable testing
enable_testing()

# Add tests
add_subdirectory(tests)

# Install targets
install(TARGETS financial_valuation
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)