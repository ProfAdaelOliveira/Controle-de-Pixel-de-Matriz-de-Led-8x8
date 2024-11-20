# Controle-de-Pixel-de-Matriz-de-Led-8x8
Esse é um projeto que utiliza um sensor de movimento MPU6050 para controlar um pixel em uma matriz de LED 8x8 baseada no controlador MAX7219. O pixel se move conforme a inclinação do sensor, permitindo uma interação visual direta com o movimento. Esse projeto é ideal para iniciantes em eletrônica e programação que desejam explorar o uso de sensores e displays.

Vamos nos conectar ? Segue meu perfil: https://github.com/ProfAdaelOliveira/SobreMim_Portifolio

Instruções de Montagem:

<h3> Componentes Necessários </h3>

-   MPU6050 - Sensor de movimento (acelerômetro e giroscópio).
-   Matriz de LED 8x8 com MAX7219 - Para exibir o pixel em movimento.
-  duino Uno (ou equivalente).
-  Cabos jumper para conexão.
-  Protoboard para montagem (opcional, mas recomendado).
-  Fonte de alimentação (via USB ou bateria 9V para o Arduino).

<h2> Esquema de Conexão </h2>

<h3> MPU6050 </h3>

- VCC → 3.3V do Arduino
- GND → GND do Arduino
- SCL → A5 (ou pino SCL, dependendo da placa)
- SDA → A4 (ou pino SDA, dependendo da placa)

<h3> Matriz de LED 8x8 (MAX7219) </h3>

- VCC → 5V do Arduino
- GND → GND do Arduino
- DIN → Pino 11 do Arduino
- CS → Pino 10 do Arduino
- CLK → Pino 13 do Arduino
