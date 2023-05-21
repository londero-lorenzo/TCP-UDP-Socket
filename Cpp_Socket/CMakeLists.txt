cmake_minimum_required(VERSION 3.24) # viene impostata la versione minima di Cmake
project(Cpp_Socket) # viene assegnato il nome del progetto


set(CMAKE_CXX_STANDARD 20) # viene impostata la versione di c++ (version: 20)


#[[
	Impostazioni per la creazione degli eseguibili 'Client.exe' e 'Server.exe' nella cartella 'src/TCP'.
	I socket realizzati utilizzeranno una comunicazione TCP.
]]

add_executable(Client_TCP src/TCP/Client.cpp src/TCP/Client.h src/TCP/Server.cpp src/TCP/Server.h src/main/TCP/client.cpp src/utils/IpResolver.cpp)
# viene aggiunto un eseguibile traget identificato dalla stringa 'Client_TCP', il quale fa riferimento ai vari file sorgente elencati
add_executable(Server_TCP src/TCP/Client.cpp src/TCP/Client.h src/TCP/Server.cpp src/TCP/Server.h src/main/TCP/Server.cpp src/utils/IpResolver.cpp)
# viene aggiunto un eseguibile traget identificato dalla stringa 'Server_TCP', il quale fa riferimento ai vari file sorgente elencati


set_target_properties(Client_TCP PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TCP" OUTPUT_NAME "Client")
# vengono modificate le proprietà dell'eseguibile target denominato 'Client_TCP' per permettere la sua creazione in uno spazio dedicato
set_target_properties(Server_TCP PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TCP" OUTPUT_NAME "Server")
# vengono modificate le proprietà dell'eseguibile target denominato 'Client_TCP' per permettere la sua creazione in uno spazio dedicato



#[[
	Impostazioni per la creazione degli eseguibili 'Client.exe' e 'Server.exe' nella cartella 'src/UDP'.
	I socket realizzati utilizzeranno una comunicazione UDP.
]]

add_executable(Client_UDP src/UDP/Client.cpp src/UDP/Client.h src/UDP/Server.cpp src/UDP/Server.h src/main/UDP/client.cpp src/utils/IpResolver.cpp)
# viene aggiunto un eseguibile traget identificato dalla stringa 'Client_UDP', il quale fa riferimento ai vari file sorgente elencati
add_executable(Server_UDP src/UDP/Client.cpp src/UDP/Client.h src/UDP/Server.cpp src/UDP/Server.h src/main/UDP/Server.cpp src/utils/IpResolver.cpp)
# viene aggiunto un eseguibile traget identificato dalla stringa 'Server_UDP', il quale fa riferimento ai vari file sorgente elencati

set_target_properties(Client_UDP PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/UDP" OUTPUT_NAME "Client")
# vengono modificate le proprietà dell'eseguibile target denominato 'Client_UDP' per permettere la sua creazione in uno spazio dedicato
set_target_properties(Server_UDP PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/UDP" OUTPUT_NAME "Server")
# vengono modificate le proprietà dell'eseguibile target denominato 'Client_UDP' per permettere la sua creazione in uno spazio dedicato
