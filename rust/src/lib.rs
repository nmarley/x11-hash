//! Rust bindings for X11 hash algorithm

#[link(name = "x11")]
unsafe extern "C" {
    fn x11_hash(input: *const u8, output: *mut u8, len: u32);
}

/// Computes X11 hash of input data.
///
/// Returns 512-bit (64-byte) hash.
///
/// Note: Input larger than 4GB will be truncated to first 4GB.
pub fn hash(input: &[u8]) -> [u8; 64] {
    let mut output = [0u8; 64];
    let len = input.len().min(u32::MAX as usize) as u32;
    unsafe {
        x11_hash(input.as_ptr(), output.as_mut_ptr(), len);
    }
    output
}
