cmake_minimum_required(VERSION 3.4)
project(Library)

add_definitions(-DBOOST_ALL_DYN_LINK)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(SOURCE_FILES
        src/model/Client.cpp
	src/model/Address.cpp
	src/model/Vehicle.cpp
	src/model/Rent.cpp
	src/model/Bicycle.cpp
	src/model/MotorVehicle.cpp
	src/model/Moped.cpp
	src/model/Car.cpp
	src/model/ClientType.cpp
	include/repositories/Repository.h
	src/repositories/ClientRepository.cpp
	src/repositories/RentRepository.cpp
	src/repositories/VehicleRepository.cpp
	src/managers/ClientManager.cpp
	src/managers/VehicleManager.cpp
	src/managers/RentManager.cpp
	src/exceptions/ClientException.cpp
	src/exceptions/RentException.cpp
	src/exceptions/VehicleException.cpp
	src/predicates/FirstNamePredicate.cpp
	src/predicates/LastNamePredicate.cpp
	)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

enable_testing()

find_package(Boost 1.60.0 COMPONENTS "unit_test_framework" "regex" REQUIRED)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
	${Bcrypt_INCLUDE_DIR}
)

target_link_libraries(Library ${Boost_LIBRARIES} ${Bcrypt_LIBRARY})

set(SOURCE_TEST_FILES
	test/master.cpp	
	test/ClientTest.cpp
	test/AddressTest.cpp
	test/BicycleTest.cpp
	test/RentTest.cpp
	test/ClientRepositoryTest.cpp
	test/RentRepositoryTest.cpp
	test/VehicleRepositoryTest.cpp
	test/MopedTest.cpp
	test/CarTest.cpp
	test/ClientTypeTest.cpp
	test/ClientManagerTest.cpp
	test/VehicleManagerTest.cpp
	test/RentManagerTest.cpp
	test/FirstNamePredicateTest.cpp
	test/LastNamePredicate.cpp
	)

add_executable(LibraryTest ${SOURCE_TEST_FILES})

target_link_libraries(LibraryTest
	Library
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)

add_test(LibraryTest1 LibraryTest
	--report_level=detailed
	--log_level=all
	--color_output=yes
	)
