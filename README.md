<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->

<a  name="readme-top"></a>

<!--

*** Thanks for checking out the Best-README-Template. If you have a suggestion

*** that would make this better, please fork the repo and create a pull request

*** or simply open an issue with the tag "enhancement".

*** Don't forget to give the project a star!

*** Thanks again! Now go create something AMAZING! :D

-->

<!-- PROJECT SHIELDS -->

<!--

*** I'm using markdown "reference style" links for readability.

*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).

*** See the bottom of this document for the declaration of the reference variables

*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.

*** https://www.markdownguide.org/basic-syntax/#reference-style-links

-->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]


<!-- PROJECT LOGO -->

<br />
<div align="center">
  <a href="https://github.com/sebastianpenning/minitalk">
    <img src="resources/images/logo.png" alt="Logo" width="150" height="150">
  </a>

  <h3 align="center">minitalk</h3>

  <p align="center">
    Minitalk is a project about signals, binary, clients, and servers
    <br />
    <a href="https://github.com/sebastianpenning/minitalk"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/sebastianpenning/minitalk">View Demo</a>
    ·
    <a href="https://github.com/sebastianpenning/minitalk/issues">Report Bug</a>
    ·
    <a href="https://github.com/sebastianpenning/minitalk/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->

<details>
<summary>Table of Contents</summary>
<ol>
<li>
<a  href="#about-the-project">About The Project</a>
<ul>
<li><a  href="#built-with">Built With</a></li>
</ul>
</li>
<li>
<a  href="#getting-started">Getting Started</a>
<ul>
<li><a  href="#installation">Installation</a></li>
</ul>
</li>
<li><a  href="#usage">Usage</a></li>
<li><a  href="#architecture">Architecture</a></li>
<li><a  href="#structures">Structures</a></li>
<li><a  href="#debugging">debugging</a></li>
<li><a  href="#roadmap">Roadmap</a></li>
<li><a  href="#license">License</a></li>
<li><a  href="#acknowledgments">Acknowledgments</a></li>
</ol>
</details>


<!-- ABOUT THE PROJECT -->

# About The Project

  
Minitalk is the first project in the Codam curriculum that introduces you to the concepts of signals, and how to handle these signals. The main purpose of this project is to try to manipulate signals in order to send a string from a client process to a server process. In this project you learn how not only to handle signals and binary conversion, but also concepts about how to handle client<->server communication, and how to handle incomplete data.


<p  align="right">(<a  href="#readme-top">back to top</a>)</p>


# Built With

* [![C][C]][C-url]

<p  align="right">(<a  href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

# Getting Started

  

This is an example of how you may give instructions on setting up your project locally.

To get a local copy up and running follow these simple example steps.


# Installation
1. Clone the repo


```sh

git clone https://github.com/sebastianpenning/minitalk.git

```
2. cd into directory

```sh

cd minitalk

```

3. Clone libft

```sh

git clone https://github.com/sebastianpenning/libft.git --recursive


```

4. Make the project

```sh

Make

```

5. Start server

```sh

./server

```
<p  align="right">(<a  href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

# Usage

After the server has started you should see a pid id of the server showing up on the terminal such as below.

<a href="https://github.com/sebastianpenning/minitalk">
    <img src="resources/images/server_start_example.png" alt="server_start" width="1100" height="200">
</a>

Start a second terminal in order to send a message to the server, with the following paramaters

```sh

./client {server_pid} {"string"}

```

As can be seen here below.

<a href="https://github.com/sebastianpenning/minitalk">
    <img src="resources/images/client_msg_example.png" alt="client_msg" width="1100" height="200">
</a>

As can be seen by the messages in the terminal, the server can receive another message after the previous message has finished printing. The client process finishes after sending the string. Therefore it needs to be executed again with the paramaters explained above. 

# Architecture

For this project, the server and client programs work together to achieve a correct transmission of the string to the server. 
<!-- Below you can find a image which illustrates this communication and the different sub-modules both the client and server contain. -->

The server and client both contain several sub-modules:

**Client**

- CLM (**C**lient **L**ength **M**odule)
- CMM (**C**lient **M**essage **M**odule)
- CSM (**C**lient **S**tatus **M**odule)

**Server**

- SLM (**S**erver **L**ength **M**odule)
- SMM (**S**erver **M**essage **M**odule)
- SSM (**S**erver **S**tring **M**odule)


### CLM

In the CLM are most of the functions used to communicate the length with the server. 
In these functions either signals are send to the server to communicate or the len_status of a message is
changed. Check <a  href="#structures">Usage</a> for more information about the structures used in this project.

### CMM

In the CCM functions are gathered which are relevent for the message itself and the communication of the message to the server. 

### CSM

This module helps with changing the statuses of the t_msg_s struct which is used for communication with the server. Check <a  href="#structures">Usage</a> for more information.

### SLM

In the SLM are functions which are used to keep track of the length of the string that is about to be received from the client, as well as statuses the length communication. Check <a  href="#structures">Usage</a> for more information about the structures used in this project.

### SMM

In the CCM functions are gathered to initiliaze the server message, to communicate back to the client regarding the message itself, and to confirm it's completion.  

### SSM

This module check wether the string has finished after the binary of a new character has been received. If the character received is '\0' then the server will print the message, otherwise it will append it to the allocated string in the server.


<p  align="right">(<a  href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

# Structures

## t_msg_s

the t_msg_s struct is included to make communication between server and client better. the members of the struct

are used to hold information about the server pid, length communication, and message communication. Below a list can be found about the length_status member, used for length communication and the msg_status member, used for message communication.

### len_status

0 = pending (waiting for message to send)

1 = start (start of length communication)

2 = confirmation (server ready to receive msg length)

3 = sending (sending a length signal)

4 = received (confirmation length signal received by server)

5 = end (send end signal to server)

6 = complete (confirmation end signal received by server )

### msg_status

0 = pending (waiting for message to send)

1 = start (start of msg communication)

2 = confirmation (server ready to receive msg )

3 = sending (sending a msg signal)

4 = received (confirmation msg signal received by server)

5 = end (send end signal to server)

6 = complete (confirmation end signal received from server )

7 = fin (completion of message delivery )

## t_msg_s

the t_msg_s struct is included to make communication between server and client better. the members of the struct

are used to hold information about the server pid, length communication, and message communication. Below a list can be found about the length_status member, used for length communication and the msg_status member, used for message communication.

### len_status

0 = pending (waiting for message to send)

1 = confirm (received len signal and send confirmation to client)

2 = completion (server received end message and send completion message to client)

### msg_status

0 = pending (waiting for message to send)

1 = confirm (received msg signal and send confirmation to client)

2 = completion (server received end message and send completion message to client)

<p  align="right">(<a  href="#readme-top">back to top</a>)</p>


# Debugging

In the Makefile an extra paramater can be given during the compilation of the server / client program. if the paramater "-D VERBOSE=1" is added in the all: rule then log messages will be printed on the terminal to give more detail about what the programs are doing. 

<!-- ROADMAP -->

# Roadmap

- [ ] Tester

See the [open issues](https://github.com/sebastianpenning/minitalk/issues) for a full list of proposed features (and known issues).

<p  align="right">(<a  href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->

# License

Distributed under the MIT License. See `LICENSE.txt` for more information.

 
<p  align="right">(<a  href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->

# Acknowledgments

* [Codam](https://www.codam.nl/about-codam) 
* [Readme Template](https://github.com/othneildrew/Best-README-Template/tree/master)

<p  align="right">(<a  href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->

<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/sebastianpenning/minitalk.svg?style=for-the-badge

[contributors-url]: https://github.com/sebastianpenning/minitalk/graphs/contributors

[forks-shield]: https://img.shields.io/github/forks/sebastianpenning/minitalk.svg?style=for-the-badge

[forks-url]: https://github.com/sebastianpenning/minitalk/network/members

[stars-shield]: https://img.shields.io/github/stars/sebastianpenning/minitalk.svg?style=for-the-badge

[stars-url]: https://github.com/sebastianpenning/minitalk/stargazers

[issues-shield]: https://img.shields.io/github/issues/sebastianpenning/minitalk.svg?style=for-the-badge

[issues-url]: https://github.com/sebastianpenning/minitalk/issues

[license-shield]: https://img.shields.io/github/license/sebastianpenning/minitalk.svg?style=for-the-badge

[license-url]: https://github.com/sebastianpenning/minitalk/blob/main/LICENSE

[C]:https://img.shields.io/badge/-c-black?logo=c&style=social

[C-url]: https://www.learn-c.org/
  

