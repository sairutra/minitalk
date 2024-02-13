# minitalk

# c_msg_t 

the c_msg_t struct is included to make communication between server and client better. the members of the struct 
are used to hold information about the server pid, length communication, and message communication. Below a list can be found about the length_status member, used for length communication and the msg_status member, used for message communication.

## len_status

0	=	pending (waiting for message to send)
1	=	start (start of length communication)
2	=	confirmation (server ready to receive msg length)
3	=	sending (sending a length signal)
4	=	received (confirmation length signal received by server)
5	= 	end (send end signal to server)
6	=	complete (confirmation end signal received by server )

## msg_status

0	=	pending (waiting for message to send)
1	=	start (start of msg communication)
2	=	confirmation (server ready to receive msg )
3	=	sending (sending a msg signal)
4	=	received (confirmation msg signal received by server)
5	= 	end (send end signal to server)
6	=	complete (confirmation end signal received by server )

# s_msg_t 

the s_msg_t struct is included to make communication between server and client better. the members of the struct 
are used to hold information about the server pid, length communication, and message communication. Below a list can be found about the length_status member, used for length communication and the msg_status member, used for message communication.

## len_status

0	=	pending (waiting for message to send)
1	=	confirm (received len signal and send confirmation to client)
2	=	completion (server received end message and send completion message to client)

## msg_status

0	=	pending (waiting for message to send)
1	=	confirm (received msg signal and send confirmation to client)
2	= 	completion (server received end message and send completion message to client)