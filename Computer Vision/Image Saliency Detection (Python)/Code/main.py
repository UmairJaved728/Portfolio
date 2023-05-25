import cv2
import numpy
import numpy as np


def find_mean(img):
    sum = 0
    rows = img.shape[0]
    cols = img.shape[1]

    for i in range(rows):
        for j in range(cols):
            sum = sum + img[i][j]
    return sum / (rows * cols)


def luminance_contrast(img, n):
    rows = img.shape[0]
    cols = img.shape[1]
    S = np.zeros((rows, cols), np.float32)
    sum = 0.0
    I_bar = find_mean(img)

    for k in range(rows - 4):
        for l in range(cols - 4):
            sum = 0.0
            for i in range(5):
                for j in range(5):
                    sum = sum + img[k + i][l + j]
            average = sum / 25
            S[k][l] = abs(I_bar - average)
            S[k][l] = S[k][l] ** n
    return S


def normalize(img):
    rows = img.shape[0]
    cols = img.shape[1]

    fmin = np.min(img)
    fmax = np.max(img)
    L_C = np.interp(img, (fmin, fmax), (0, 255)).astype(np.uint8)
    # for i in range(rows):
    #     for j in range(cols):
    #         newimg[i][j] = ((img[i][j] - fmin) / (fmax - fmin)) * 255
    return L_C


def tensor_index(I1, I2):
    rows = I1.shape[0]
    cols = I1.shape[1]
    output = np.zeros((rows, cols), np.float32)

    I1 = I1 * I2

    for k in range(rows - 4):
        for l in range(cols - 4):
            sum = 0.0
            for i in range(5):
                for j in range(5):
                    sum = sum + (I1[k + i][l + j])
            output[k][l] = sum
    return output


def structure_tensor(img):
    # Gaussian Blur
    img = cv2.GaussianBlur(img, (3, 3), 7)

    # derivative in x-direction
    Ix = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=5)

    # derivative in y-direction
    Iy = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=5)

    Ix = tensor_index(Ix, Ix)
    Iy = tensor_index(Iy, Iy)
    IxIy = tensor_index(Ix, Iy)
    return Ix, Iy, IxIy


def Epsilon_calculation(Ix, Iy, IxIy):
    A = np.zeros((2, 2), np.float32)
    rows = img.shape[0]
    cols = img.shape[1]
    Epsilon = np.zeros((rows, cols), np.float32)
    sum = 0.0
    for i in range(rows):
        for j in range(cols):
            A[0][0] = Ix[i][j]
            A[0][1] = IxIy[i][j]
            A[1][0] = IxIy[i][j]
            A[1][1] = Iy[i][j]
            try:
                eigenvalues = np.linalg.eigvals(A)
                if np.any(np.isinf(eigenvalues)):
                    Epsilon[i][j] = 0
                else:
                    Epsilon[i][j] = abs(eigenvalues[1] - eigenvalues[0])
            except np.linalg.LinAlgError:
                Epsilon[i][j] = 0
    return Epsilon


def orientation_contrast(E1):
    rows = E1.shape[0]
    cols = E1.shape[1]
    S1 = np.zeros((rows, cols), np.float32)
    E1 = normalize(E1)
    for k in range(rows - 6):
        for o in range(cols - 6):
            sum = 0.0
            for i in range(7):
                for j in range(7):
                    sum = sum + abs(E1[k + i][o + j] - E1[k + 3][o + 3])
            S1[k][o] = sum
    return S1


def combination(SL, SD):
    rows = SL.shape[0]
    cols = SL.shape[1]
    S = np.zeros((rows, cols), np.float64)
    for i in range(rows):
        for j in range(cols):
            S[i][j] = SL[i][j] * SD[i][j]
    return S


img = cv2.imread('cat.jpg')
print(img.shape[0], img.shape[1])
cv2.imshow('Original Image', img)

# conversion to 2D
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

L_C = luminance_contrast(img, 2)
L_C_show = normalize(L_C)
cv2.imshow('2nd order statistics', L_C_show)

Ix, Iy, IxIy = structure_tensor(img)
Ix = cv2.GaussianBlur(Ix, (3, 3), 3)
Iy = cv2.GaussianBlur(Iy, (3, 3), 3)
IxIy = cv2.GaussianBlur(IxIy, (3, 3), 3)
E = Epsilon_calculation(Ix, Iy, IxIy)
S = orientation_contrast(E)
S_show = normalize(S)
cv2.imshow('Directional Coherence Image', S_show)
S = combination(L_C, S)
S = normalize(S)
cv2.imshow('Output Image', S)

cv2.waitKey(0)
