# Facial Emotion Recognition

A real-time facial emotion recognition system that combines a deep learning classifier with embedded hardware output. A webcam feed is processed with OpenCV to detect and crop the face, the cropped region is classified by a ResNet-152-based model, and the predicted emotion is sent over UART to an STM32 microcontroller, which displays it on an LCD and lights a corresponding status LED.

## Overview

- Trained a deep learning model based on the **ResNet-152** architecture for facial emotion classification, using transfer learning on the **FER2013** and **RAF-DB** datasets.
- Achieved approximately **70% accuracy** on the held-out test set across multiple emotion classes.
- Built a real-time **Python + OpenCV** application that detects and crops the face region from a live camera feed before passing it to the trained model for classification.
- Integrated the vision pipeline with embedded hardware by transmitting the predicted emotion from the Python application to an **STM32** microcontroller over **UART**.
- The STM32 displays the recognized emotion on an **I2C LCD1602** screen and lights one of **three status LEDs** corresponding to the detected emotion category.

## How It Works

1. **Capture** — A webcam feed is read frame by frame using OpenCV.
2. **Face detection & cropping** — Each frame is scanned for a face; the detected face region is cropped and preprocessed (resized/normalized) for the model.
3. **Classification** — The cropped face is passed through the trained ResNet-152 model, which outputs the predicted emotion class.
4. **Communication** — The predicted emotion label is encoded and sent from the PC to the STM32 over a UART serial connection.
5. **Hardware feedback** — The STM32 firmware parses the incoming label, displays the emotion name on the I2C LCD1602, and lights the LED assigned to that emotion category.

## Tech Stack

**Machine Learning / Vision**
- Python
- PyTorch (ResNet-152, transfer learning)
- OpenCV (face detection, cropping, real-time video pipeline)
- FER2013, RAF-DB datasets

**Embedded**
- STM32 microcontroller
- UART (PC ↔ MCU communication)
- I2C (LCD1602 display driver)
- GPIO (status LEDs)

## Datasets

- **FER2013** — grayscale facial expression dataset used for training/evaluation.
- **RAF-DB** (Real-world Affective Faces Database) — real-world facial expression images used to improve generalization.

## Results

- Test accuracy: **~70%** across the emotion classes evaluated.

## Repository Structure

```
Facial-Emotion-Recognition/
├── FacialEmotionRecognition.py       # Real-time capture, face crop, inference, UART send
├── haarcascade_frontalface_default.xml  # Face detection cascade used for cropping
└── README.md
```

## Getting Started

### Requirements

- Python 3.x
- `opencv-python`
- `torch` / `torchvision` (or the framework used for the trained model)
- `timm` (for getting ResNet 152 model)
- `pyserial` (for UART communication)
- An STM32 board flashed with firmware that reads UART input and drives the LCD1602 (I2C) and LEDs

### Running

```bash
pip install opencv-python torch torchvision pyserial
python FacialEmotionRecognition.py
```

Connect the STM32 board over USB/serial before running so the predicted emotion can be transmitted over UART.

## Author

**Abdullah Ahmed Abdelfattah Ahmed**
[GitHub](https://github.com/abdullahelnoory) · [LinkedIn](https://www.linkedin.com/in/abdallah-elnory-b45126282/)
