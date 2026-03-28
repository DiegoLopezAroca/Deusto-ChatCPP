# Deusto-ChatCPP

A C++ chat client application developed for Universidad de Deusto. The client connects to a server over TCP sockets and allows students and teachers to exchange messages through a console-based interface.

## Features

- User authentication (email and password)
- Role-based menus for students and teachers
- View and start conversations
- Real-time messaging within conversations
- Group and subject chat support
- Profile management

## Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Entry point – creates a `Cliente` instance and starts the session |
| `cliente.h` / `cliente.cpp` | Main client class with login flow, menus, and chat screens |
| `socket.h` / `socket.cpp` | Windows socket wrapper (`SocketCliente`) for TCP communication |
| `databaseHandler.h` | `ConversationsHandler` and `MessagesHandler` – serialize/deserialize data received from the server |
| `conversation.h` | `Conversation` struct |
| `message.h` | `Message` struct |

## Requirements

- Windows (uses Winsock2)
- C++17 or later
- A running chat server at `127.0.0.1:6000` (configurable in `socket.h`)

## Build

Compile with any MinGW/MSVC toolchain. Example using `g++`:

```bash
g++ main.cpp cliente.cpp socket.cpp -o chatcpp.exe -lws2_32 -std=c++17
```

The `-lws2_32` flag links the Windows Sockets library.

## Usage

1. Start the chat server.
2. Run the compiled executable:
   ```bash
   chatcpp.exe
   ```
3. Enter your email and password when prompted.
4. Navigate the menu to view conversations, start new chats, or access your profile.

## Configuration

The server address and port are defined in `socket.h`:

```cpp
#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 6000
```

Change these values before compiling to connect to a different server.
