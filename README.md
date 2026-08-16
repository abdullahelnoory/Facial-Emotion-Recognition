# Facial Emotion Recognition

A real-time facial emotion recognition system that combines a PyTorch computer-vision pipeline with bare-metal embedded firmware. A webcam feed is processed with OpenCV to detect and crop a face, a ResNet-152-based model classifies the emotion, and the result is sent over UART to an STM32F103 ("Blue Pill") microcontroller, which displays the emotion on an I2C LCD1602 and lights one of three status LEDs.

## Overview

- Trained a deep learning model based on the **ResNet-152** architecture (via `timm`), using transfer learning on a combined **FER2013 + RAF-DB** facial-emotion dataset.
- Achieved **~70.4% accuracy** on the held-out test set across 7 emotion classes.
- Built a real-time **Python + OpenCV** application (`FacialEmotionRecognition.py`) that captures webcam frames, detects and crops a face with a Haar Cascade classifier, and classifies the emotion.
- Sends the predicted emotion class over **UART (serial)** to an **STM32F103** microcontroller running custom, register-level (bare-metal) firmware.
- The STM32 displays the recognized emotion on an **I2C LCD1602** and lights one of **three status LEDs**, grouped by emotional valence (negative / neutral / positive).

## Repository Structure

```
Facial-Emotion-Recognition/
├── FacialEmotionRecognition.py             # Real-time capture → face crop → inference → UART send
├── haarcascade_frontalface_default.xml     # OpenCV Haar Cascade used for face detection
├── notebook/
│   └── Facial_Emotion_Recognition.ipynb    # Model training, evaluation, and export notebook
├── STM32/                                  # STM32CubeIDE bare-metal firmware project
│   ├── .cproject / .project                # STM32CubeIDE project files
│   ├── STM32F103C8TX_FLASH.ld              # Linker script (STM32F103C8T6 "Blue Pill")
│   ├── FacialEmotion_Classification_Display Debug.launch
│   ├── Drivers/
│   │   └── stm32f1xx.h                     # Register-level MCU peripheral definitions
│   ├── Src/
│   │   ├── main.c                          # UART receive → LCD1602 (I2C) + status LEDs
│   │   ├── syscalls.c
│   │   └── sysmem.c
│   └── Startup/
│       └── startup_stm32f103c8tx.s
└── README.md
```

> **Note:** The trained model weights (`FacialEmotionClassifier.pt`) are loaded at runtime by `FacialEmotionRecognition.py` but are not checked into the repository — regenerate them by running the training notebook, or supply your own checkpoint at the project root.

## Model & Training (`notebook/Facial_Emotion_Recognition.ipynb`)

- **Dataset:** downloaded via `kagglehub` (`fahadullaha/facial-emotion-recognition-dataset`), a combined **FER2013 + RAF-DB** facial emotion dataset, loaded with `torchvision.datasets.ImageFolder`.
- **Split:** stratified 70% train / 15% validation / 15% test.
- **Architecture:** `timm`'s `resnet152` backbone (ImageNet-pretrained) with a custom classification head — `Flatten → Linear(2048→512) → ReLU → Dropout(0.3) → Linear(512→7)` — for the 7 emotion classes (`angry`, `disgust`, `fear`, `happy`, `neutral`, `sad`, `surprise`).
- **Training strategy:** the backbone is frozen for the first 4 epochs (training only the classification head), then unfrozen with a reduced learning rate (0.0001 vs. the initial 0.001) for the remaining epochs — 10 epochs total, Adam optimizer, cross-entropy loss.
- **Result:** final test-set accuracy of **~70.4%**.

## Embedded Firmware (`STM32/Src/main.c`)

Bare-metal (register-level) firmware for an **STM32F103C8T6**, with no HAL/CubeMX-generated drivers — peripherals are configured by writing directly to their registers.

- **UART (USART2):** receives one byte per prediction from the Python application; only the lower nibble is used, so the meaningful values are `0–6` for the 7 emotion classes (any other value is treated as "no data" / unknown).
- **I2C (I2C2):** drives a 16×2 character LCD through a PCF8574 I2C backpack (address `0x27`), using the standard 4-bit HD44780 command/data protocol.
- **Status LEDs (GPIOB):** three LEDs are grouped by emotional valence:
  - `PB7` — negative emotions (`angry`, `disgust`, `fear`)
  - `PB8` — neutral/ambiguous emotions (`neutral`, `sad`, `surprise`)
  - `PB9` — positive emotion (`happy`)
- **Control loop:** the firmware polls USART2, and only refreshes the LCD/LEDs when the received class changes (avoiding unnecessary LCD re-writes), displaying `"Class : <Emotion>"` on the screen.
- **Timing:** a simple millisecond delay routine is implemented using `TIM3` for LCD initialization timing.

## How It Works — End to End

1. **Capture** — `cv2.VideoCapture(0)` reads frames from the webcam.
2. **Face detection** — each frame is converted to grayscale and scanned with `haarcascade_frontalface_default.xml` via `cv2.CascadeClassifier`.
3. **Crop & preprocess** — the detected face is cropped, converted to RGB, resized to 224×224, and converted to a tensor.
4. **Classification** — the tensor is passed through the trained `FacialEmotionClassifier` (ResNet-152 backbone + custom head); the highest-scoring class is taken as the prediction.
5. **UART send** — the predicted class index (0–6) is written as a single byte over the serial port to the STM32.
6. **Embedded display** — the STM32 firmware reads the byte over USART2, updates the LCD1602 with the emotion name, and lights the LED corresponding to that emotion's valence group.
7. **Live overlay** — the webcam window displays the bounding box and predicted emotion as text; the app exits when `q` is pressed.

## Requirements

**Python application**
- Python 3.x
- `pillow`, `opencv-python`, `torch`, `torchvision`, `timm`, `pyserial`, `keyboard`

```bash
pip install pillow opencv-python torch torchvision timm pyserial keyboard
```

**Training notebook**
- `torch`, `torchvision`, `timm`, `kagglehub`, `scikit-learn`, `pandas`, `numpy`, `matplotlib`, `seaborn`, `tqdm`

**Embedded firmware**
- STM32CubeIDE (or a compatible ARM GCC toolchain) to build and flash the `STM32/` project
- An STM32F103C8T6 ("Blue Pill") board, a PCF8574-based I2C LCD1602, 3 LEDs, and a USB-to-serial/Bluetooth UART link to the PC

## Setup & Usage

1. **Train or obtain a model checkpoint** — run `notebook/Facial_Emotion_Recognition.ipynb` end-to-end (or supply your own) to produce `FacialEmotionClassifier.pt`, and place it in the project root.
2. **Flash the STM32** — open the `STM32/` project in STM32CubeIDE, build it, and flash it to an STM32F103C8T6 board wired to an I2C LCD1602 (PCF8574 backpack) and 3 status LEDs on `PB7`/`PB8`/`PB9`.
3. **Connect the boards** — wire the STM32's USART2 to a UART/Bluetooth link to the PC, and update the serial port in `FacialEmotionRecognition.py` (currently hardcoded to `COM5` at `9600` baud) to match your system, e.g. `/dev/ttyUSB0` on Linux.
4. **Run the app:**

```bash
python FacialEmotionRecognition.py
```

5. A window opens showing the live camera feed with the detected face and predicted emotion; the STM32 updates its LCD/LEDs in real time. Press `q` to quit.

> If no serial device is found on the configured port, the script prints a message and continues running in webcam-only mode (no data is sent to the STM32).

## Author

**Abdullah Ahmed Abdelfattah Ahmed**
[GitHub](https://github.com/abdullahelnoory) · [LinkedIn](https://www.linkedin.com/in/abdullah-elnoory-b45126282/)
