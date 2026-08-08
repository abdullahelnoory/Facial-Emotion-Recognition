from PIL import Image 
import cv2
import torch
from torch import nn
import torchvision
from torchvision import transforms
import timm
import serial
import keyboard

class FacialEmotionClassifier(nn.Module):
  def __init__(self):
    super(FacialEmotionClassifier, self).__init__()

    self.base_model = timm.create_model('resnet152', pretrained=False)

    self.features = nn.Sequential(*list(self.base_model.children())[:-1])

    for param in self.features.parameters():
      param.requires_grad = False

    self.classifier = nn.Sequential(
        nn.Flatten(),
        nn.Linear(2048, 512),
        nn.ReLU(),
        nn.Dropout(0.3),
        nn.Linear(512, 7)
    )

  def forward(self, x):
    x = self.features(x)
    output = self.classifier(x)
    return output

cam = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
device = 'cuda' if torch.cuda.is_available() else 'cpu'

model = FacialEmotionClassifier()
model.load_state_dict(torch.load("./FacialEmotionClassifier.pt", map_location=device))
model.to(device)

status_dict = {0:"angry",1:"disgust",2:"fear",3:"happy",4:"neutral",5:"sad",6:"surprise"}

ser = None
try:    
    ser = serial.Serial('COM5', 9600)
except:
   print("Couldn't connect to this port")

while True:
    ret, frame = cam.read()
    
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray_frame)

    image_transform = transforms.Compose([
        transforms.Resize((224, 224)),
        transforms.ToTensor()
    ])
    
    txt = ""
    status = ""
    if len(faces) == 0:
        txt = "No faces detected"
    else:
        (x, y, w, h) = faces[0]
        cv2.rectangle(frame, (x,y),(x+w,y+h),(255,255,0),2)
        face_image = frame[y:y+h,x:x+w]
        face_image = cv2.cvtColor(face_image, cv2.COLOR_BGR2RGB)
        transformed_face_image = image_transform(Image.fromarray(face_image)).unsqueeze(0)     
        predictions = model(transformed_face_image)
        emotion_class = int(torch.argmax(predictions,1).cpu().numpy())
        status = status_dict[emotion_class]
        txt = f"Status: {status}"

        if(ser):
          ser.write(bytes([emotion_class]))

    cv2.putText(frame, txt, (30, 70), color=(0, 255, 127), fontFace=1, fontScale=3.5)
    
    cv2.imshow('Camera', frame)

    if cv2.waitKey(1) == ord('q'):
        break

cam.release()
cv2.destroyAllWindows