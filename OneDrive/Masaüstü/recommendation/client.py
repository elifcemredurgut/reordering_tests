import zmq
import sys
import zhelpers
from csv import reader


context = zmq.Context()
# Socket to talk to server
print("Connecting to the server...")
socket = context.socket(zmq.DEALER)
id = sys.argv[1]
formatted_id = "client" + id
identity = id.encode('ascii')
socket.setsockopt(zmq.IDENTITY, identity)
zhelpers.set_id(socket)
socket.connect("tcp://localhost:5555")
socket.send_string("Hello")
print("Introduction request sent")


while(True):
    message = socket.recv()
    print("Received reply:", message)

    encoding = 'utf-8'
    m = message.decode(encoding)
    print(message, m)
    if(m == "send"):
        profile = ""
        with open('ratings.csv', 'r') as read_obj:
            csv_reader = reader(read_obj)
            header = next(csv_reader)
            if header != None:
                # Iterate over each row after the header in the csv
                for row in csv_reader:
                    # row variable is a list that represents a row in csv
                    if row[0] == id:
                        profile += row[1] + ":" + row[2] + ","
        socket.send_string(profile)
