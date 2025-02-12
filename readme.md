# 🚀 Controle de Servomotor por PWM no RP2040

## 📚 Descrição do Projeto
Este projeto implementa o controle de um **servomotor** utilizando **PWM (Pulse Width Modulation)** no microcontrolador **RP2040 (Raspberry Pi Pico W)**. O objetivo é simular e movimentar o braço do servo em diferentes ângulos (0°, 90° e 180°) e criar uma movimentação suave contínua entre 0° e 180°.

### 🔧 Funcionalidades Implementadas:
- **Configuração do PWM na GPIO 22 (50Hz, 20ms)**
- **Movimentação fixa do servomotor** para 0°, 90° e 180°
- **Movimentação suave e contínua** entre 0° e 180°
- **Controle do LED RGB na GPIO 12** para observação dos sinais PWM

---

## 🎯 Requisitos do Projeto

1. **Definir a frequência PWM para aproximadamente 50Hz** (20ms de período).
2. **Configurar ciclos ativos de PWM para movimentar o servo**:
   - **2400µs** → Posição **180°** (aguardar 5s)
   - **1470µs** → Posição **90°** (aguardar 5s)
   - **500µs** → Posição **0°** (aguardar 5s)
3. **Criar uma movimentação suave entre 0° e 180°**, com incrementos de 5µs e atraso de 10ms.
4. **Utilizar o LED RGB na GPIO 12** para visualizar o comportamento do PWM.
5. **Executar o experimento no BitDogLab** e documentar os resultados.

---

## 🛠️ Hardware e Software Utilizados

### **Hardware:**
- **Raspberry Pi Pico W** (RP2040)
- **Servomotor Micro Servo Padrão**
- **LED RGB**
- **Fonte de alimentação 5V**

### **Software:**
- **Pico SDK (RP2040 C SDK)**
- **Simulador Wokwi**
- **BitDogLab**

---

## 📂 Organização do Código

- **`embarcatech-pwm-servo.c`**
  - Configuração do PWM para servomotor e LED RGB.
  - Implementação dos movimentos fixos (0°, 90°, 180°).
  - Implementação do movimento suave entre 0° e 180°.
  - Loop principal para controle contínuo do servo e LED.

---

## ⚙️ Instruções de Compilação e Execução

1. **Clone o repositório**:
   ```sh
   git clone https://github.com/gouveiamdb/embarcatech-pwm-servo.git
   ```
2. **Configure o Pico SDK**.
3. **Compile o código**.
4. **Carregue o firmware no Raspberry Pi Pico W**.
5. **Conecte ao monitor serial** para visualizar as mensagens de depuração.

---

## 📹 Demonstração do Projeto

### Vídeo de Demonstração
O vídeo de demonstração exibe:
- Funcionamento do código.
- Explicação das funcionalidades implementadas.

📌 **[Link para o vídeo](https://drive.google.com/file/d/1HE52dFNtYhwgroXTrPvK50rI78rzq9hW/view?usp=drive_link)** []

---

## 💻 Autor
- **Matheus Gouveia de Deus Bastos**

---

## 📜 Licença
Este projeto é de uso acadêmico e segue as diretrizes da Embarcatech.

