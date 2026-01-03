fn main() {
    println!("cargo:rustc-link-search=../");
    println!("cargo:rustc-link-lib=static=x11");
    println!("cargo:rerun-if-changed=../libx11.a");
}
