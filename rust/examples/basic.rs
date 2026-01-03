use x11_hash;

fn main() {
    let input = b"\x00";
    let hash = x11_hash::hash(input);

    println!("Input: {:02x}", input[0]);
    print!("Hash (first 32 bytes): ");
    for byte in &hash[..32] {
        print!("{:02x}", byte);
    }
    println!();
}
