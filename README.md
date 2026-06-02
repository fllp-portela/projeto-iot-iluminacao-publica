# Projeto IoT - Iluminação Pública Automatizada

Sistema de iluminação pública inteligente com ESP32, sensor LDR e protocolo MQTT.

## Descrição

Este projeto automatiza o acionamento de iluminação pública com base na luminosidade ambiente. O sensor LDR detecta a ausência de luz e aciona o LED (simulando uma lâmpada pública). O status é publicado via protocolo MQTT para monitoramento remoto.

## Hardware utilizado

- ESP32 DevKit V1
- Sensor LDR (fotoresistor)
- LED amarelo
- Resistor 220Ω
- Resistor 10kΩ

## Comunicação MQTT

- Broker: broker.hivemq.com
- Porta: 1883
- Tópico publicado: luz/status (valores: LIGADA / DESLIGADA)
- Tópico subscrito: luz/comando (valores: LIGAR / DESLIGAR)

## Como reproduzir

1. Acesse https://wokwi.com e crie um projeto ESP32
2. Copie o código da pasta /codigo para o sketch.ino
3. Instale a biblioteca PubSubClient no Library Manager
4. Execute a simulação
5. Use o MQTTX conectado ao broker.hivemq.com para monitorar

## Fluxo de funcionamento

1. ESP32 conecta ao Wi-Fi
2. ESP32 conecta ao broker MQTT
3. LDR lê a luminosidade a cada 2 segundos
4. Se escuro: acende LE
