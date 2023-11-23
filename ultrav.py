import os
import serial
import subprocess

from twilio.rest import Client


account_sid = 'AC190a9418d8853a70ae2707247e73aa9b'
auth_token = '06040c26b3a16cb3e0167d66e0163bf0'
client = Client(account_sid, auth_token)

 # Abre a porta serial
#ser.reset_input_buffer()

ser = serial.Serial('COM8', 9600)  # Substitua 'COMx' pelo nome da porta do Arduino7

while True:
    data = ser.readline().decode().strip()

    print(data)
    
    if data:
          message = client.messages.create(
                from_='whatsapp:+14155238886',
                body=(f"Cuidado, melhor tomar cuidado e usar um protetor solar, raios UV atingiram o nivel de risco!!!! \nDados:\n{data}"),
                to='whatsapp:+559295143900'
                )
          print(message.sid)
        