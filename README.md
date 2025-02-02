# Atividade da aula síncrona do dia 27/01 do curso de sistemas embarcados oferecido pela Embarcatech
## Descrição
Este código tem a finalidade de utilizar interrupção na placa Bitdoglab da seguinte forma: a matriz de led 5x5 contabiliza ao apertar o botão A, mostrando os números de 0 a 9, e decrementa ao apertar o botão B, enquanto que o led vermelho pisca 5 vezes por segundo.
Desta forma, foi implementado a funcionalidade de interrupção para os botões, enquanto que a matriz de led 5x5 e o led vermelho respondem ao loop da função main. Os botões também contam com o debouncing via software esperando 200 ms para contornar este problema.

## Pré-requesitos
- VS Code 
- Pico sdk
- Wokwi para o Vscode

## Instalação
1. Clone o repositório:
   ```sh
   git clone https://github.com/Ukobir/U4C4O12T.git
2. Compile no Pico-SDK
3. Faça o Upload para a placa Bitdoglab.
## Vídeo demonstração
[Link para o vídeo](https://www.dropbox.com/scl/fi/1mngpzel7lvn7t9rgqx7a/Video1.mp4?rlkey=6eojsezz7y02tnkx8s6u8pf1b&st=m3lhyndv&dl=0)
