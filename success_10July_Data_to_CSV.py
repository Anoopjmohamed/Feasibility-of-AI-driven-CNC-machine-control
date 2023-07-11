import serial
import csv
import time

ser = serial.Serial('COM6', 115200) # replace 'COM6' with your Arduino's port
time.sleep(2) # waiting for the serial connection to initialize

with open('accel_data_0V_Bump2nd.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Time", "X", "Y", "Z"])  # Write header
    while True:
        try:
            if ser.isOpen():
                line = ser.readline().strip()  # read a '\n' terminated line
                vals = line.decode('ascii').split(',')
                print(vals)
                if len(vals) == 4:  # We expect 4 items in the line (Time, x_value, y_value, z_value)
                    writer.writerow(vals)
        except UnicodeDecodeError:
            print('Non-ASCII character encountered, ignoring...')
        except Exception as e:  # General exception handler
            print(f"An error occurred: {str(e)}")