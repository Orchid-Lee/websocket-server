# WebSocket Server

This project implements a WebSocket server using C++ and the `httplib` library. It provides a simple HTTP interface and supports WebSocket connections.

## Project Structure

```
websocket-server
├── src
│   ├── server.cpp        # Main implementation of the WebSocket server
├── include
│   └── httplib.h        # Header for the HTTP library
├── CMakeLists.txt       # CMake configuration file
└── README.md            # Project documentation
```

## Setup Instructions

1. **Clone the repository:**
   ```
   git clone <repository-url>
   cd websocket-server
   ```

2. **Install dependencies:**
   Ensure you have CMake installed on your system. You may also need a C++ compiler that supports C++11 or later.

3. **Build the project:**
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the server:**
   After building, you can run the server executable:
   ```
   ./server
   ```

## Usage

- The server listens on port 8080.
- You can access the HTTP endpoint by navigating to `http://localhost:8080/hi` in your web browser. It will respond with "Hello World!".
- WebSocket connections can be established (implementation details to be added).

## Contributing

Feel free to submit issues or pull requests for improvements or bug fixes.