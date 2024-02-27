use std::ops::{Add, Mul};

fn value_at_index<T>(i: T) -> T
where
    T: Add<Output = T> + Mul<Output = T> + Copy,
{
    let three: T = T::from(3).unwrap();

    3 + (2 * i)
}


fn main() {
    println!("Hello, world!");
    let x: u64 = 3;
    println!("value_at_index(3) = {}", value_at_index(x));
}

