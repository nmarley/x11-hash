use std::path::PathBuf;

fn main() {
    // The x11-hash project root is one directory up from the rust/ crate
    let manifest_dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"));
    let x11_root = manifest_dir
        .parent()
        .expect("rust/ crate must be inside x11-hash/");

    let lib_path = x11_root.join("libx11.a");
    if !lib_path.exists() {
        panic!(
            "libx11.a not found at {:?}\n\
             Run `make libx11.a` in {:?} first.",
            lib_path, x11_root
        );
    }

    println!("cargo:rustc-link-search={}", x11_root.display());
    println!("cargo:rustc-link-lib=static=x11");
    println!("cargo:rerun-if-changed={}", lib_path.display());
}
