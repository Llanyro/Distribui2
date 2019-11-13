cmake_minimum_required(VERSION 3.5)

set(SERVICIOEJECUCION serv_ejecucion)
#set(SERVICIOLECTOR serv_lector)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${SERVICIOEJECUCION})
add_executable(${SERVICIOEJECUCION} "ejecutacion.cpp" "ServicioEjecucion.h" "ServicioEjecucion.cpp" "ClienteEjecutacion.h" "ClienteEjecutacion.cpp"
 "Singleton.h" "String.h" "String.cpp" "List.h" "File.h" "File.cpp" "Cliente.h" "Cliente.cpp" "Servicio.h" "Servicio.cpp")
