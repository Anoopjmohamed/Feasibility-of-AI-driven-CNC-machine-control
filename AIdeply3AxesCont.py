import serial
import numpy as np
import tensorflow as tf

# Load the pre-trained models for X, Y, and Z axes
model_x = tf.keras.models.load_model('.\Tuning\Control_MainX.h5')
model_y = tf.keras.models.load_model('.\Tuning\Control_MainY.h5')
model_z = tf.keras.models.load_model('.\Tuning\Control_MainZ.h5')

# Set up the serial connection
ser = serial.Serial('COM4', 115200)  # Replace 'COM3' with your Arduino's port
ser.flushInput()

# Buffers to store the incoming data for X, Y, and Z
data_buffer_x = []
data_buffer_y = []
data_buffer_z = []

# Continuous loop to keep reading data
while True:
    try:
        # Read a line of data from the serial port
        line = ser.readline().decode('ISO-8859-1').strip()
        
        # Split the string at each tab character
        values = line.split('\t')

        # Check that we have exactly 3 components (x, y, z)
        if len(values) == 3:
            x, y, z = map(float, values)
            data_buffer_x.append(x)
            data_buffer_y.append(y)
            data_buffer_z.append(z)
        else:
            print("Invalid data received:", values)
            continue
        
        # Check if we have collected 201 samples for each axis
        if len(data_buffer_x) == 201:
            # Convert to NumPy arrays for easier manipulation
            data_array_x = np.array(data_buffer_x).reshape(1, 201, 1)
            data_array_y = np.array(data_buffer_y).reshape(1, 201, 1)
            data_array_z = np.array(data_buffer_z).reshape(1, 201, 1)
            
            # Use the models to make predictions
            prediction_x = model_x.predict(data_array_x, verbose=0)
            prediction_y = model_y.predict(data_array_y, verbose=0)
            prediction_z = model_z.predict(data_array_z, verbose=0)

            # Get the predicted class for each axis
            predicted_class_x = np.argmax(prediction_x)
            predicted_class_y = np.argmax(prediction_y)
            predicted_class_z = np.argmax(prediction_z)
            
            # Print the results
            print(f"Predicted Classes - X: {predicted_class_x}, Y: {predicted_class_y}, Z: {predicted_class_z}")
            
            # Send the predictions to Arduino
            ser.write(f"{predicted_class_x},{predicted_class_y},{predicted_class_z}\n".encode('utf-8'))
            
            # Clear the buffers for the next set of samples
            data_buffer_x.clear()
            data_buffer_y.clear()
            data_buffer_z.clear()
            
    except Exception as e:
        # Handle exceptions (e.g., invalid data or communication errors)
        print("Error:", e)
        continue

# Note: Ensure you have the required hardware and environment setup before running this code.
