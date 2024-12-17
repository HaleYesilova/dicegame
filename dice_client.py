
import socket
from datetime import datetime  

SERVER = "127.0.0.1"
PORT = 8080

def main():
    print("Zar Atma İstemcisine Hoşgeldiniz! Çıkmak için 'q' tuşlayın.")
    
    while True:
        command = input("Komut girin ('zar at' yazın): ")
        if command.lower() == 'q':
            print("Bağlantı kapatılıyor...")
            break

        
        send_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"[{send_time}] Sunucuya istek gönderiliyor...")

        
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect((SERVER, PORT))

       
        client.sendall(command.encode("utf-8"))

        
        response = client.recv(1024).decode("utf-8")
        print(f"Sunucudan cevap: {response}")

        client.close()

if __name__ == "__main__":
    main()
