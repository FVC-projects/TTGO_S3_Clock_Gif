# TTGO_S3_Clock_Gif

Projeto de um Relógio com imagens animadas.

Configurado para o LILYGO T-Display Esp32-S3 (resolução 170 x 320)

![image](https://github.com/FVC-projects/TTGO_S3_Clock_Gif/assets/157984341/801eddf2-8038-472a-a283-0b954a90e6f5)

Devido ao ficheiro com as imagens (Clock.h) ser bastante pesado é necessário, antes do Upload, configurar a Placa:

-> "ESP32S3 Dev Module":

    -> Partition Scheme: "Huge APP (3MB No OTA)

![image](https://github.com/FVC-projects/TTGO_S3_Clock_Gif/assets/157984341/e7b92599-b27b-48a0-b28c-ded3653a0c42)

Configurações no Ficheiro TTGO_S3_Clock.ino:

- Configurar Nome da Rede WIFI e Password

- Configurar TimeZone de acordo com o país (está configurado para GMT+0 - Lisboa)
