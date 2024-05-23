from ctypes import CDLL, c_int, c_double, POINTER

f = CDLL("./build/libbluesolarangles.so")

f.sumInts.argtypes = [c_int, c_int]
f.sumInts.restype = c_int

print(f.sumInts(1, 2))

f.blueSolarAngles.argtypes = [
    c_double,
    c_double,
    c_double,
    c_double,
    c_double,
    c_double,
    c_double,
    c_double,
]
f.blueSolarAngles.restype = POINTER(c_double)

a = f.blueSolarAngles(1, 2, 3, 4, 5, 6, 7, 8)

print([a[i] for i in range(4)])
