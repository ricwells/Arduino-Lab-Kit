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
 
def webpage(value):
    html = """
            <!DOCTYPE html>
            <html>
            <head>
            <style>
                button{display: inline-block; background-color: #4286f4; border: none;border-radius: 4px; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
            </style>
            </head>
            <body>
            <form action="./submit">
                <div>
                <input type="text" name="redname" >
                </div>
                <button value="submit" class="button">submit</button>
            </form>
            """ +f"""<p>Temperature is {value} degrees Celsius</p>
            </body>
            </html>
            """
    return html
 
def serve(connection):
    while True:
        client = connection.accept()[0]
        request = client.recv(1024)
        request = str(request)
        
        print(f"request1: {request}")

        try:
            request = request.split()[1]
        except IndexError:
            pass
                
        print(f"request2: {request}")

        request = request.split('?')
        print(f"request3: {request}")
        request1 = request[0]
        
        if request1 == '/submit':
            print("submit")
        else:
            print("not submit")
 
        value='%.2f'%temperature()    
        html=webpage(value)
        client.send(html)
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