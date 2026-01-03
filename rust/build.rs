fn main() {
    // Compile all C sources directly into the Rust library
    cc::Build::new()
        .file("../sha3/blake.c")
        .file("../sha3/bmw.c")
        .file("../sha3/cubehash.c")
        .file("../sha3/echo.c")
        .file("../sha3/groestl.c")
        .file("../sha3/jh.c")
        .file("../sha3/keccak.c")
        .file("../sha3/luffa.c")
        .file("../sha3/shavite.c")
        .file("../sha3/simd.c")
        .file("../sha3/skein.c")
        .file("../x11.c")
        .file("../util.c")
        .include("../")
        .include("../sha3")
        .compile("x11");

    // Trigger rebuild if C sources change
    println!("cargo:rerun-if-changed=../x11.c");
    println!("cargo:rerun-if-changed=../x11.h");
    println!("cargo:rerun-if-changed=../util.c");
    println!("cargo:rerun-if-changed=../util.h");
    println!("cargo:rerun-if-changed=../sha3/");
}
