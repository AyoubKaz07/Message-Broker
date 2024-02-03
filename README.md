# C++ Message Broker

## Overview

This project implements a concurrent message broker using C++ with some object-oriented programming (OOP). The message broker allows clients to subscribe to topics, publish messages, and receive messages from subscribed topics.

## Features

- **Subscription**: Clients can subscribe to specific topics to receive messages.
- **Publishing**: Clients can publish messages to specific topics, which are then delivered to subscribed clients.
- **Unsubscription**: Clients can unsubscribe from topics to stop receiving messages.

- The server has a simple thread per client concurrency.

## Project Structure

- `server.cpp`: Contains the implementation of the server, which handles client connections and message routing.
- `handlers.cpp` and `handlers.h`: Define the command handlers for different commands like SUB, PUB, UNSUB, and PING.
- `parser.h`: Implements the command parser, which creates command handlers based on received commands.
- `server.h`: Header file for the server class.

## Usage

### Building the Server

``` mkdir build ``` + ``` cd build ``` + ``` make ```

### Running the Server

``` ./server ```

### Connecting Clients

Clients can connect to the server using a socket connection. For testing purposes, you can use tools like telnet or create a simple client in C++.
### Example Commands
``` telnet localhost 4222 ```

``` SUB my_topic ```

### Publish a Message:

``` PUB my_topic 8 ```
"Hello!"
and we get:
Hello! as the subscribers too
(In this case our client is both the subscriber and the publisher), you can open another terminal and connect with a different client and experience it

Unsubscribe from a Topic:
 ``` UNSUB my_topic ```

### Classes details:

#### Prerequisites: abstract base classes, interfaces and polymorphism.

    AbsractHandler: Abstract base class for command handlers, defining the common interface.
    SubCommandHandler, PubCommandHandler, UnsubCommandHandler, PingCommandHandler: Concrete implementations of command handlers.
    CommandParser: Responsible for creating the appropriate command handler based on the received command.

#### Contributing

Feel free to contribute to the project by opening issues or creating pull requests. Your feedback and contributions are highly appreciated!
