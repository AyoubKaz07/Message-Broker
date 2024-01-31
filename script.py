import socket
import threading

def send_command(client_socket, command):
    client_socket.sendall(command.encode())
    response = client_socket.recv(1024)
    print(response.decode())

def main():
    host = '127.0.0.1'
    port = 4222
    num_clients = 40
    commands = ["SUB CC", "PUB CC ", "JOHN"]

    client_sockets = []
    threads = []

    # Connect multiple clients
    for _ in range(num_clients):
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((host, port))
        client_sockets.append(client_socket)

    # Send commands concurrently
    for client_socket in client_sockets:
        for command in commands:
            thread = threading.Thread(target=send_command, args=(client_socket, command))
            threads.append(thread)
            thread.start()

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

    # Close client sockets
    for client_socket in client_sockets:
        client_socket.close()

if __name__ == "__main__":
    main()
