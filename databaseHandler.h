// databaseHandler.h
#include <vector>
#include <string>
#include <sstream>
#include "socket.h"
#include "message.h"
#include "conversation.h"

class DatabaseHandler {
public:
    virtual void save() = 0;
    virtual void load() = 0;
    virtual ~DatabaseHandler() {}
};

class ConversationsHandler : public DatabaseHandler {
public:
    ConversationsHandler(SocketCliente& socket) : socketCliente(socket) {}

    void save() override {
        for (const auto& conversation : conversations) {
            std::string data = serialize(conversation);
            socketCliente.enviarMensaje(data.c_str());
        }
    }

    void load() override {
        socketCliente.enviarMensaje("STARTED_CHATS");
        char buffer[MAX_BUFFER_SIZE * 10];
        socketCliente.recibirMensaje(buffer);
        conversations = deserializeConversations(buffer);
    }

    std::vector<Conversation> getMessages() const {
        return conversations;
    }

private:
    SocketCliente& socketCliente;
    std::vector<Conversation> conversations;

    std::string serialize(const Conversation& conv) {
        return std::to_string(conv.id) + ";" + conv.iniciadorCorreo + ";" + conv.destinatarioCorreo;
    }

    std::vector<Conversation> deserializeConversations(const char* buffer) {
        std::vector<Conversation> conversations;
        std::string data(buffer);
        std::istringstream stream(data);
        std::string line;
        while (std::getline(stream, line)) {
            Conversation conv;
            std::istringstream lineStream(line);
            std::string idStr;
            std::getline(lineStream, idStr, ';');
            conv.id = std::stoi(idStr);  // Convertir la cadena a un entero
            std::getline(lineStream, conv.iniciadorCorreo, ';');
            std::getline(lineStream, conv.destinatarioCorreo, ';');
            conversations.push_back(conv);
        }
        return conversations;
    }
};

class MessagesHandler : public DatabaseHandler {
public:
    MessagesHandler(SocketCliente& socket) : socketCliente(socket) {}

    void save() override {
        for (const auto& message : messages) {
            std::string data = serialize(message);
            socketCliente.enviarMensaje(data.c_str());
        }
    }

    void load() override {
        // Typically would request messages from the server here
    }

    void loadByConversationId(int conversationId) {
        std::string request = "GET_MESSAGES " + std::to_string(conversationId);
        socketCliente.enviarMensaje(request.c_str());
        char buffer[MAX_BUFFER_SIZE * 10];
        socketCliente.recibirMensaje(buffer);
        messages = deserializeMessages(buffer);
    }

    std::vector<Message> getMessages() const {
        return messages;
    }

private:
    SocketCliente& socketCliente;
    std::vector<Message> messages;

    std::string serialize(const Message& msg) {
        return std::to_string(msg.id) + ";" + msg.remitenteCorreo + ";" + msg.contenido + ";" + msg.timestamp;
    }

    std::vector<Message> deserializeMessages(const char* buffer) {
        std::vector<Message> messages;
        std::string data(buffer);
        std::istringstream stream(data);
        std::string line;
        while (std::getline(stream, line)) {
            Message msg;
            std::istringstream lineStream(line);
            std::string idStr;
            std::getline(lineStream, idStr, ';');
            msg.id = std::stoi(idStr);  // Convertir la cadena a un entero
            std::getline(lineStream, msg.remitenteCorreo, ';');
            std::getline(lineStream, msg.contenido, ';');
            std::getline(lineStream, msg.timestamp, ';');
            messages.push_back(msg);
        }
        return messages;
    }
};
