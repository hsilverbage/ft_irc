# ft_irc - Custom IRC Server

## 📌 Introduction
ft_irc is a project that involves developing a custom IRC (Internet Relay Chat) server using C++98. This server allows multiple clients to connect, communicate in real-time, and interact in various chat channels following the IRC protocol.

## 📁 Project Structure
- **Core Components**:
  - `Server.cpp`: Handles client connections and communication.
  - `Client.cpp`: Manages individual client interactions.
  - `Channel.cpp`: Implements channel functionality.
  - `NumericReplies.cpp`: Handles IRC numeric replies.
- **Commands**:
  - `invite.cpp`, `ban.cpp`, `unban.cpp`, `join.cpp`, `kick.cpp`, `mode.cpp`, `nick.cpp`, `part.cpp`, `pass.cpp`, `privmsg.cpp`, `quit.cpp`, `topic.cpp`, `user.cpp`

## 🔧 Installation & Compilation
1. **Clone the repository**
   ```sh
   git clone <repo_url>
   cd ft_irc
   ```
2. **Compile the project**
   ```sh
   make
   ```
3. **Run the server**
   ```sh
   ./ircserv <port> <password>
   ```
   - `<port>`: The port on which the server will listen for connections.
   - `<password>`: The required password for clients to connect.

## 📜 Features
- Authentication with nickname and username setup.
- Creation and management of channels.
- Sending and receiving private messages.
- Operator functionalities:
  - `KICK`: Remove a client from a channel.
  - `INVITE`: Invite a client to a channel.
  - `TOPIC`: Change or view the channel topic.
  - `MODE`: Modify channel permissions (invite-only, topic restrictions, channel keys, operator privileges, user limits).
- Non-blocking I/O with `poll()`.
- Handles multiple clients simultaneously.

## 🏆 Bonus Features
- File transfer support.
- Custom IRC bot integration.

## 🎯 Objectives
- Implement a functional IRC server adhering to the IRC protocol.
- Utilize non-blocking I/O and event-driven programming.
- Ensure stability, efficiency, and compliance with C++98 standards.

## 📖 Documentation
For additional references and guidelines, check out the following resources:
- [Modern IRC Documentation](https://modern.ircdocs.horse/)

## 📄 License
Project developed as part of the 42 school curriculum.
