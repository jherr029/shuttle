link_directories(/usr/include)
set(CMAKE_CXX_STANDARD 11)

include_directories(../include/)
include_directories(src)

add_library(Curl_ curl.cpp ../include/curl.h)
add_library(Json jsonParse.cpp ../include/jsonParse.h)
add_library(MatrixCell distanceMatrixCell.cpp ../include/distanceMatrixCell.h)
add_library(Matrix distanceMatrix.cpp ../include/distanceMatrix.h)
add_library(CoordCache cacheCoords.cpp ../include/cacheCoords.h)
# add_library(Sql sqlConnector.cpp ../includes/sqlConnector.h)
# add_library(errorFlag errorFlag.cpp ../includes/errorFlag.h)
# add_library(lyticsGather lyticsGather.cpp ../includes/lyticsGather.h)
# add_library(analyzer analyzer.cpp ../includes/analyzer.h)

# add_executable(lytics main.cpp curl.cpp errorFlag.cpp jsonParse.cpp sqlConnector.cpp )
add_executable(shuttle main.cpp)
target_link_libraries(shuttle Curl_ Json MatrixCell Matrix CoordCache curl)