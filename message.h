#pragma once
#include <string>

struct Message {
    int id;
    std::string remitenteCorreo;
    std::string contenido;
    std::string timestamp;
};
