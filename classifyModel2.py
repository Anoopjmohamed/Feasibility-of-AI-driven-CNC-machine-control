import numpy as np
import tensorflow as tf
from tensorflow import keras
from Loaddata import *
import matplotlib.pyplot as plt

def build_and_compile_model(input_shape, num_classes):
    model = make_model(input_shape, num_classes)
    model.compile(
        optimizer="adam",
        loss="sparse_categorical_crossentropy",
        metrics=["sparse_categorical_accuracy"]
    )
    return model

def make_model(input_shape, num_classes):
    input_layer = keras.layers.Input(input_shape)

    conv1 = keras.layers.Conv1D(filters=64, kernel_size=3, padding="same")(input_layer)
    conv1 = keras.layers.BatchNormalization()(conv1)
    conv1 = keras.layers.ReLU()(conv1)

    conv2 = keras.layers.Conv1D(filters=64, kernel_size=3, padding="same")(conv1)
    conv2 = keras.layers.BatchNormalization()(conv2)
    conv2 = keras.layers.ReLU()(conv2)

    conv3 = keras.layers.Conv1D(filters=64, kernel_size=3, padding="same")(conv2)
    conv3 = keras.layers.BatchNormalization()(conv3)
    conv3 = keras.layers.ReLU()(conv3)

    gap = keras.layers.GlobalAveragePooling1D()(conv3)

    output_layer = keras.layers.Dense(num_classes, activation="softmax")(gap)

    return keras.models.Model(inputs=input_layer, outputs=output_layer)

def plothist(history):
    plt.plot(history.history['loss'], label='loss')
    plt.plot(history.history['val_loss'], label='val_loss')
    plt.title('Training History')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    filename = '.\Data\Train_Data.csv'
    x_train, y_train, z_train, x_label, y_label, z_label = loaddata(filename)

    for i in range(len(x_label)):
        if x_label[i] == 1:
            x_label[i] = 0
        elif x_label[i] == 2 or x_label[i] == 3:
            x_label[i] = 1
    for i in range(len(y_label)):
        if y_label[i] == 1:
            y_label[i] = 0
        elif y_label[i] == 2 or y_label[i] == 3:
            y_label[i] = 1
    for i in range(len(x_label)):
        if z_label[i] == 1:
            z_label[i] = 0
        elif z_label[i] == 2 or z_label[i] == 3:
            z_label[i] = 1

    axes_data = {
        'X': (x_train, x_label),
        'Y': (y_train, y_label),
        'Z': (z_train, z_label)
    }

    for axis, (train_data, labels) in axes_data.items():
        print(f"Training model for {axis} axis...")

       
        train_data = train_data.reshape((train_data.shape[0], train_data.shape[1], 1))
        num_classes = len(np.unique(labels))
        idx = np.random.permutation(len(train_data))
        train_data = train_data[idx]
        labels = labels[idx]
        labels[labels == -1] = 0

        model = build_and_compile_model(input_shape=train_data.shape[1:], num_classes=num_classes)

        epochs = 200
        batch_size = 50

        callbacks = [
            keras.callbacks.ModelCheckpoint(f"Control_Model{axis}.h5", save_best_only=True, monitor="val_loss"),
            keras.callbacks.ReduceLROnPlateau(monitor="val_loss", factor=0.5, patience=20, min_lr=0.0001)
        ]

        history = model.fit(
            train_data,
            labels,
            batch_size=batch_size,
            epochs=epochs,
            callbacks=callbacks,
            validation_split=0.2,
            verbose=1,
        )

        # Visualization of history
        plothist(history=history)

        loss, acc = model.evaluate(train_data, labels)
        print(f"acc: {acc}, loss: {loss}")
