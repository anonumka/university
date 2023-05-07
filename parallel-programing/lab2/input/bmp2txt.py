import numpy as np
from PIL import Image

def binarize_array(numpy_array):
    """Binarize a numpy array."""
    n = len(numpy_array)
    k = len(numpy_array[0])
        
    arr_res = []
    for i in range(0, n):
            arr_res.append([0 for c in range(0, k)])

    for i in range(n):
        for j in range(k):
            arr_res[i][j] = 765 - sum(numpy_array[i][j])
    return arr_res

if __name__ == "__main__":
        img_data = Image.open('data_1.bmp')
        img_data.convert('L')
        img_arr = np.array(img_data)

        res_arr = binarize_array(img_arr)

        # print(res_arr)
        
        with open('output7.txt', 'w') as fp:
                fp.write(str(len(res_arr)))
                fp.write(' ')
                fp.write(str(len(res_arr[0])))
                fp.write('\n')
                for i in range(len(res_arr)):
                        for j in range(len(res_arr[0])):
                                fp.write(str(res_arr[i][j]))
                                fp.write(' ')
                        fp.write('\n')


