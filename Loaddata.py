import numpy as np
import pandas as pd

def loaddata(
    filename: str
) -> np.ndarray:
    x_trainset = []
    y_trainset = []
    z_trainset = []
    x_label = []
    y_label = []
    z_label = []
    with open(filename, "r") as f:
        while 1:
            line = f.readline()
            if line:
                str_arr = line.split(',')

                if str_arr[1].lower()=='x':
                    x_label.append(int(str_arr[0]))
                    x_trainset.append([float(i) for i in str_arr[2:]])
                elif str_arr[1].lower()=='y':
                    y_label.append(int(str_arr[0]))
                    y_trainset.append([float(i) for i in str_arr[2:]])
                elif str_arr[1].lower()=='z':
                    z_label.append(int(str_arr[0]))
                    z_trainset.append([float(i) for i in str_arr[2:]])
            else:
                break
    
    x_trainset = np.asarray(x_trainset)
    y_trainset = np.asarray(y_trainset)
    z_trainset = np.asarray(z_trainset)
    
    x_label = np.asarray(x_label)
    y_label = np.asarray(y_label)
    z_label = np.asarray(z_label)
    return x_trainset, y_trainset, z_trainset, x_label, y_label, z_label

if __name__ == '__main__':
    filename = '.\Data\Train_Data.csv'
    loaddata(filename)