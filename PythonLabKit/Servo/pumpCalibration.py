"""
    Pumps Calibration Program
    *  This program allows you to calibrate 3 servo driven 10 mL syringe pumps by recording 
    *  their microseconds at 0 mL and 10 mL. The values are stored in EEPROM. The syringe pumps
    *  are designed from 3D printed parts (linear pump v8.stl). Standard 20 Kg 270 degree servos
    *  are used to drive BD 10 mL syringes. The program is used on the Arduino Uno platform.

    The Core Unit uses digital pins 6-13 and analog pins A4 and A5 on the Arduion Uno. 
    7(dout)(red)&8(sck)(brown)=balance & VDD(purple); 9=pump1; 10=pump2; 11=pump 3; 12=DallasTemperature sensor; 
    6=MOSFET for heater; A4 (SDA)(orange) & A5 (CL)(yellow) balance display; 13=balance tare button (green). 
    The calibration constants for the syringe pumps and balance are stored in EEPROM
    as SHORT variables.pump1=0-3;pump4-7, pump3=8-11. The calibration coeficient for 
    the balance is stored in EEPROM 12.
    All the remaining pins (2-5 and A0-A3) are available for the Experiemnt Modules. 
"""
import machine
import socket
import network
import time

def Setup():
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

def webPage1():
    html = """
            <!DOCTYPE html>
            <html>
            <head>
            <style>
                button {
                    display: inline-block; 
                    background-color: #4286f4; 
                    border: none;
                    border-radius: 4px; 
                    color: white; 
                    padding: 16px 40px; 
                    text-decoration: none; 
                    font-size: 30px; 
                    margin: 2px; 
                    cursor: pointer;
                }
            </style>
            </head>
            <body>
            <form action="./submit">
                <div>
                <input type="text" name="redname" >
                </div>
                <button value="submit" class="button">submit</button>
            </form>
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
 
        html=webPage1()
        client.send(html)
        client.close()
 
def open_socket(ip):
    # Open a socket
    address = (ip, 80)
    connection = socket.socket()
    connection.bind(address)
    connection.listen(1)
    print(connection)
    return connection

try:
    if ip is not None:
        connection=open_socket(ip)
        serve(connection)
except KeyboardInterrupt:
    machine.reset()