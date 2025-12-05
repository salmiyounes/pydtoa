from _dtoa import ffi, lib
import math

def create_string_buffer(size: int):
    return ffi.new("char[]", size)

def dtoa(value: float) -> str:
    buff = create_string_buffer(128)
    lib.dtoa(value, buff)

    return ffi.string(buff).decode()

if __name__ == "__main__":
    print (dtoa(math.pi))
