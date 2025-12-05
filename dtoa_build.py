from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    char *dtoa(double value, char *buffer);
""")

ffibuilder.set_source("_dtoa", 
"""
    #include "grisu.h"
""",
    include_dirs=["include"],
    sources=[
        "src/grisu.c",
        "src/diy_fp.c",
        "src/ieee754.c",
        "src/k_comp.c",
        "src/pow_10.c",
        "src/utils.c",
    ]
)

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)