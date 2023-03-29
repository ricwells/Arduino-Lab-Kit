import machine
import socket
import math
import utime
import network
import time

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect("wells04","busterbrown")
 
# rgb led
red=machine.Pin(13,machine.Pin.OUT)
green=machine.Pin(14,machine.Pin.OUT)
blue=machine.Pin(15,machine.Pin.OUT)
 
# Wait for connect or fail
wait = 10
while wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    wait -= 1
    print('waiting for connection...')
    time.sleep(1)
 
# Handle connection error
if wlan.status() != 3:
    raise RuntimeError('wifi connection failed', wlan.status())
else:
    print('connected')
    ip=wlan.ifconfig()[0]
    print('IP: ', ip)
 
# Temperature Sensor
sensor_temp = machine.ADC(4)
conversion_factor = 3.3 / (65535)
 
def temperature():
    temperature_value = sensor_temp.read_u16() * conversion_factor 
    temperature_Celcius = 27 - (temperature_value - 0.706)/0.00172169/ 8 
    print(temperature_Celcius)
    utime.sleep(2)
    return temperature_Celcius

def getFile(file_name):
    try:
        file = open(file_name,'r')
        data = file.read()
        return data
    except IOError:
        print(f"failed reading file {file_name}")
    finally:
        file.close()

def startTest(device):
    pass

def startCalibration(device, amount):
    pass

def serve(connection):
    actionName = ""
    device = ""
    amount = ""

    while True:
        client = connection.accept()[0]
        request = client.recv(1024)
        request = str(request)
        
        print(f"request1: {request}")
 
        try:
            params = request.split()
            requestType = params[0]
            if len(params) > 1:
                commandList = params[1].split('?')
            print(f"type: {requestType}, list: {str(commandList)}")
            if "POST" in requestType:
                html = "Started "
                command = commandList[0]
                if command == "/Calibrate":
                    result = f"Calibrate: Pump #{commandList[1]}, "
                    if commandList[2] == 0:
                        result += "0mLs"
                    else:
                        result += "10mLs"
                    html = html + result

                    actionName = "Calibrate"
                    device = commandList[1]
                    amount = commandList[2]

                elif command == "/Tests":
                    result = f"Syringe Test: Device #{commandList[1]}, "
                    html = html + result

                    actionName = "Test"
                    device = commandList[1]
                else:
                    pass
            elif "GET" in requestType:
                command = commandList[0]
                if command == "/Data":
                    print("Data")
                    html = f"Action: {actionName}, device: {device}"
                    if actionName == "Calibrate":
                        html += f", amount: {amount}"
                    t = time.time()
                    html += f", time: {t}"
                elif command == "/app.js":
                    html = getFile("app.js")
                else:
                    html = getFile("index.html")
                    t = time.time()
                    print(f"actionName: {actionName}")
                    print(f"device: {device}")
                    print(f"amount: {amount}")
                    print(f"time: {t}")
                    result = f"Action: {actionName}, Device: {device}, amount: {amount}, time: {t}"
                    html = html % result
            else:
                html = html % "unknown"
            
            client.send(html)
        except Exception as e:
            print(f"Error: {e}")
            raise
        finally:
            client.close()
 
def open_socket(ip):
    # Open a socket
    address = (ip, 80)
    connection = socket.socket()
    connection.bind(address)
    connection.listen(1)
    print(connection)
    return(connection)
 
 
try:
    if ip is not None:
        connection=open_socket(ip)
        serve(connection)
except KeyboardInterrupt:
    machine.reset()