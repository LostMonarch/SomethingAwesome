# CMakeLists file for building fraud detector Something Awesome project

# CMake declarations
cmake_minimum_required (VERSION 3.6)
project (Awesome)
add_compile_options(-std=c++11)

# Pull in sources and headers
set(SOURCES 
    main.cpp
    Bank.cpp
    Customer.cpp
    TransactionHistory.cpp
    CustomerProfile.cpp
    FraudDetector.cpp
    DecisionTree.cpp
)

set(HEADERS
     CustomerProfile.h 
     card.h
     transaction.h
     vendorType.h
     TransactionHistory.h
     Customer.h
     Bank.h
     FraudDetector.h
     transactionTime.h
     DecisionTree.h
)

# Include headers
include_directories(${HEADERS})

# Add target executable
add_executable(main ${SOURCES})