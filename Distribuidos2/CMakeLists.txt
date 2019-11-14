cmake_minimum_required(VERSION 3.5)

set(SERVICIOHTTP serv_http)
set(SERVICIOEJECUCION serv_ejecucion)
set(SERVICIOLECTOR serv_lector)
set(SERVICIOSUMADOR serv_sumador)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${SERVICIOHTTP})
add_executable(${SERVICIOHTTP} "Maquinas/http_server/main.cpp" "Maquinas/http_server/ClienteHttpServer.h" "Herramientas/File.h" "Herramientas/File.cpp" "Maquinas/http_server/ClienteHttpServer.cpp" 
"Maquinas/http_server/httpserver.h" "Maquinas/http_server/httpserver.cpp" "Maquinas/http_server/tools.h" "Maquinas/http_server/tools.cpp" "Maquinas/http_server/utils.h" 
"Maquinas/http_server/utils.cpp" "Herramientas/Singleton.h" "Herramientas/List.h" "Herramientas/String.h" "Herramientas/String.cpp" "Maquinas/Plantillas/Cliente.h" "Maquinas/Plantillas/Cliente.cpp"
"Maquinas/Puertos.h")
target_link_libraries(${PROJECT_NAME} mysqlcppconn mysqlclient pthread z m rt atomic dl)

project(${SERVICIOEJECUCION})
add_executable(${SERVICIOEJECUCION}  "Maquinas/ejecutador/ClienteEjecutacion.h" "Maquinas/ejecutador/ClienteEjecutacion.cpp" "Maquinas/ejecutador/ejecutacion.cpp" 
"Maquinas/ejecutador/ServicioEjecucion.h" "Maquinas/ejecutador/ServicioEjecucion.cpp" "Maquinas/Plantillas/Servicio.h" "Maquinas/Plantillas/Servicio.cpp"
"Maquinas/Plantillas//Cliente.h" "Maquinas/Plantillas//Cliente.cpp" "Herramientas/File.h" "Herramientas/List.h" "Herramientas/Singleton.h" "Herramientas/String.h"
"Herramientas/socket.h" "Herramientas/File.cpp" "Herramientas/String.cpp")

project(${SERVICIOLECTOR})
add_executable(${SERVICIOLECTOR} "Maquinas/Lector/ServicioLector.h" "Maquinas/Lector/ServicioLector.cpp" "Maquinas/Lector/lector.cpp" "Maquinas/Plantillas/Servicio.h"
"Maquinas/Plantillas/Servicio.cpp" "Herramientas/File.h" "Herramientas/List.h" "Herramientas/Singleton.h" "Herramientas/String.h" "Herramientas/socket.h"
"Herramientas/File.cpp" "Herramientas/String.cpp")


project(${SERVICIOSUMADOR})
add_executable(${SERVICIOSUMADOR} "Maquinas/Sumador/ServicioSumador.h" "Maquinas/Sumador/ServicioSumador.cpp" "Maquinas/Sumador/sumador.cpp" "Maquinas/Plantillas/Servicio.h"
"Maquinas/Plantillas/Servicio.cpp" "Herramientas/File.h" "Herramientas/List.h" "Herramientas/Singleton.h" "Herramientas/String.h" "Herramientas/socket.h" 
"Herramientas/File.cpp" "Herramientas/String.cpp")
