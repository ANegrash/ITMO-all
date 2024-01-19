# -*- coding: utf-8 -*-
"""Practice3.ipynb

Automatically generated by Colaboratory.

# Импортируем необходимые библиотеки

Для того, чтобы импортировать библиотеку или пакет, используйте ключивое слово `import`. Если библиотека или пакет еще не установлены, то можно это сделать или из **cmd** или из **notebook**, начиная команду с `!`.

Пример: `$ pip install torchvision` or  `! pip install torchvision`

Для правильной установки pytorch на локальный ПК, ориентируйтесь на официальный сайт https://pytorch.org/
"""

import torch
import os
import torchvision.models as models
from sklearn.datasets import load_iris
import matplotlib.pyplot as plt
from pathlib import Path
from torchvision import datasets
from torchvision.transforms import ToTensor
from torch.utils.data import DataLoader
from torch import optim
from torch import nn
import torch.nn.functional as F
from torchvision import transforms

! pip install torchview
! pip install netron
! pip install onnx
! pip install onnxruntime
! pip install onnxscript

import torch.onnx
import torchvision
from torchview import draw_graph

from google.colab import drive
drive.mount('/content/drive')

base_path = 'drive/MyDrive/TNV'
labels_path = base_path + '/labels.csv'
labels_path_test = base_path + '/labels_test.csv'
labels_path_val = base_path + '/labels_val.csv'
train_path = base_path + '/train'
test_path = base_path + '/test'
val_path = base_path + '/val'

# Commented out IPython magic to ensure Python compatibility.
# %load_ext tensorboard

"""Переносим файлы из двух директорий PNEUMONIA и NORMAL с соответствующими им названиями в папки train и test соответственно"""

# c = 0
# for filename in os.listdir(test_path+'/PNEUMONIA'):
#    os.rename(test_path+'/PNEUMONIA/'+filename, test_path+'/pneumonia_'+str(c)+'.jpeg')
#    c = c + 1

"""Генерируем csv-файлик с названиями файлов и их меткой"""

# breed = {'normal': 0,
#          'pneumonia': 1}

# with open(labels_path_val, 'w+') as f:
#   for filename in os.listdir(test_path):
#     name = filename.split('_')[0]
#     f.write(filename + ',' + str(breed[name]) + '\n')

from torch.utils.tensorboard import SummaryWriter # TensorBoard support

tb = SummaryWriter(comment='Run cnn at pneumonia dataset')

# Device configuration
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
device

"""# Custom dataset
 Если Вы используйте набор данных из другого источника, то Вам необходимо описать класс CustomDataset и передавать его в Dataloader. Ниже приведен пример возможной реализации класса

Дополнительную информацию можно найти на оф.сайте https://pytorch.org/tutorials/beginner/basics/data_tutorial.html

"""

from torch.utils.data import Dataset
import pandas as pd
from torchvision.io import read_image

class CustomDataset(Dataset):
    def __init__(self, annotations_file, img_dir, transform=None):
        self.img_labels = pd.read_csv(annotations_file)
        self.img_dir = img_dir
        self.transform = transform

    def __len__(self):
        return len(self.img_labels)

    def __getitem__(self, idx):
        img_path = os.path.join(self.img_dir, self.img_labels.iloc[idx, 0])
        image = read_image(img_path)

        label = self.img_labels.iloc[idx, 1]
        if self.transform:
            image = self.transform(image)

        return image, label

transform = transforms.Compose([

        #gray scale
        transforms.Grayscale(),

        #resize
        transforms.Resize((224,224), antialias=True)
    ])
BATCH_SIZE = 64

train_dataset = CustomDataset(labels_path, train_path, transform)
test_dataset = CustomDataset(labels_path_test, test_path, transform)

train_loader =  torch.utils.data.DataLoader(train_dataset,
                                            batch_size=BATCH_SIZE,
                                            shuffle = True,
                                            drop_last=True)

test_loader = torch.utils.data.DataLoader(test_dataset,
                                          batch_size=BATCH_SIZE,
                                          shuffle = True,
                                          drop_last=True)

"""
## Готовим модель для обучения
Выбираем модель, оптимизатор и функцию потерь. Создаем функции обучения"""

# Пример импорта модели нейронной сети из бибилиотеки torchvision
cnn = models.alexnet().to(device)

loss_func = nn.CrossEntropyLoss()
optimizer = optim.Adam(cnn.parameters(), lr = 0.000001)

print(cnn)

"""## Обучение с валидацией

Описываем цикл обучения с промежуточной валидацией
"""

# Initialising variables

import numpy as np
from sklearn.metrics import accuracy_score
from torch.autograd import Variable

epochs = 25
steps = 0
print_every = BATCH_SIZE
trainLoss = []
testLoss = []

for e in range(epochs):
    running_loss = 0

    for images, labels in train_loader:
        # Forward pass
        steps += 1
        optimizer.zero_grad()

        images = Variable(images.view(-1,1,224,224).type(torch.Tensor))
        images = np.repeat(images, 3, axis=1)
        ready_image = images.to(device)

        log_ps = cnn(ready_image)

        # Loss calculation
        labels = Variable(labels).to(device)
        loss = loss_func(log_ps, labels)
        tb.add_scalar('Loss', loss, e)

        # Backward pass
        loss.backward()
        optimizer.step()

        running_loss += loss.item()


        # Validation step
        if steps % print_every == 0:
            accuracy, test_loss = 0, 0

            # Set mode without gradient calculation
            with torch.no_grad():
                cnn.eval()

                # Run validation on test dataset
                for images, labels in test_loader:
                    images = Variable(images.view(-1,1,224,224).type(torch.Tensor))
                    images = np.repeat(images, 3, axis=1)
                    ready_image = images.to(device)

                    log_ps = cnn(ready_image)

                    labels = Variable(labels).to(device)
                    testsample_loss = loss_func(log_ps, labels)
                    test_loss += testsample_loss

                    tb.add_scalar('Test Loss', testsample_loss, e)

                    ps = torch.exp(log_ps)

                    top_p, top_class = ps.topk(1, dim = 1)

                    accuracy += accuracy_score(labels.view(*top_class.shape).cpu(),top_class.cpu() )

            # Return train mode
            cnn.train()

            trainLoss.append(running_loss/len(train_loader))
            testLoss.append(test_loss/len(test_loader))
            testAccur = accuracy/len(test_loader)

            tb.add_scalar('Accuracy', testAccur, e)

            print("Epoch: {}/{}.. ".format(e + 1, epochs),
                  "Test Accuracy: {:.3f}".format(testAccur))

cnn = models.alexnet()
cnn.load_state_dict(torch.load(base_path+"/lab1.save", map_location=torch.device('cpu')))
cnn.eval()

from torch.autograd import Variable
cmodel_path = base_path+"/cust_model.onnx"
input_size=(64, 3, 224, 224)
dummy_input = Variable(torch.randn([64, 3, 224, 224]))

#onnx_program = torch.onnx.export(cnn,
#                                 dummy_input.cuda(),
#                                 cmodel_path,
#                                 input_names = ['input'],
#                                 output_names = ['label'])

import onnxruntime
options = onnxruntime.SessionOptions()
options.enable_profiling=True

session = onnxruntime.InferenceSession(
        cmodel_path,
        sess_options=options,
        providers=['AzureExecutionProvider', 'CPUExecutionProvider'] # For NVIDIA
)

import time

start_time = time.time()
outputs = session.run(None, {'input':  dummy_input.numpy()})
end_time = time.time()
print("Onnx: {}".format(end_time - start_time))

start_time_t = time.time()
torch_outputs = cnn(dummy_input)
end_time_t = time.time()
print("Normal: {}".format(end_time_t - start_time_t))

len(dummy_input.numpy())

len(dummy_input.cuda())

# Commented out IPython magic to ensure Python compatibility.
tb.close()
# %tensorboard --logdir=runs