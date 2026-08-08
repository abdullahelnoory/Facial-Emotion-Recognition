# Facial Emotion Recognition

A real-time facial emotion recognition application that captures webcam video, detects and crops the face with a Haar Cascade classifier, runs it through a ResNet-152-based PyTorch model to classify the emotion, and streams the predicted class over a serial (UART) connection to an STM32 microcontroller for hardware-side display/feedback (LCD1602 + status LEDs).

## Overview

- Trained a deep learning model based on the **ResNet-152** architecture (via `timm`) for facial emotion classification, using transfer learning on the **FER2013** and **RAF-DB** datasets.
- Achieved approximately **70% accuracy** on the held-out test set across the 7 emotion classes.
- Built a real-time **Python + OpenCV** application (`FacialEmotionRecognition.py`) that captures webcam frames, detects a face with a Haar Cascade classifier, crops it, and classifies the emotion.
- Sends the predicted emotion class over **UART (serial)** to an STM32 microcontroller, which displays the result on an **I2C LCD1602** and lights a corresponding status LED.

## Repository Contents

```
Facial-Emotion-Recognition/
├── FacialEmotionRecognition.py          # Real-time capture → face crop → inference → serial send
├── haarcascade_frontalface_default.xml  # OpenCV Haar Cascade used for face detection
└── README.md
```

> **Note:** The trained model weights (`FacialEmotionClassifier.pt`) are loaded at runtime but are not included in this repository — train the model separately or supply your own checkpoint at the project root. The STM32 firmware that receives the serial byte and drives the LCD/LEDs is likewise maintained outside this repo.

## Model

`FacialEmotionClassifier` (defined in `FacialEmotionRecognition.py`):

- **Backbone:** `timm`'s `resnet152`, used as a frozen feature extractor (backbone weights are not updated during training of the head).
- **Head:** `Flatten → Linear(2048 → 512) → ReLU → Dropout(0.3) → Linear(512 → 7)`
- **Output:** 7 emotion classes — `angry`, `disgust`, `fear`, `happy`, `neutral`, `sad`, `surprise`
- **Input:** face crop resized to `224×224` and converted to a tensor before inference

## How It Works

1. **Capture** — `cv2.VideoCapture(0)` reads frames from the webcam.
2. **Face detection** — Each frame is converted to grayscale and passed to `haarcascade_frontalface_default.xml` via `cv2.CascadeClassifier` to locate a face.
3. **Crop & preprocess** — The first detected face is cropped from the frame, converted to RGB, resized to 224×224, and converted to a tensor.
4. **Classification** — The tensor is passed through the `FacialEmotionClassifier` model; the class with the highest score is taken as the predicted emotion.
5. **Serial send** — If a serial connection is available, the predicted class index (0–6) is written as a single byte over the serial port to the STM32.
6. **Display** — The webcam feed is shown in a window with the detected face boxed and the predicted emotion overlaid as text; the app exits when `q` is pressed.

## Requirements

- Python 3.x
- `pillow`
- `opencv-python`
- `torch`
- `torchvision`
- `timm`
- `pyserial`
- `keyboard`

```bash
pip install pillow opencv-python torch torchvision timm pyserial keyboard
```

## Setup & Usage

1. Place a trained checkpoint named `FacialEmotionClassifier.pt` in the project root (the model architecture must match `FacialEmotionClassifier` in `FacialEmotionRecognition.py`).
2. Connect the STM32 board and update the serial port in the script (currently hardcoded to `COM5` at `9600` baud) to match your system — e.g. `/dev/ttyUSB0` on Linux or `/dev/tty.usbserial-*` on macOS.
3. Run the application:

```bash
python FacialEmotionRecognition.py
```

4. A window will open showing the live camera feed with the detected face and predicted emotion. Press `q` to quit.

> If no serial device is found on the configured port, the script will print a message and continue running in webcam-only mode (no data is sent to the STM32).

## Author

**Abdullah Ahmed Abdelfattah Ahmed**
[GitHub](https://github.com/abdullahelnoory) · [LinkedIn](https://www.linkedin.com/in/abdallah-elnory-b45126282/)
