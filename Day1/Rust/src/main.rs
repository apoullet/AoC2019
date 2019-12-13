use std::fs::File;
use std::io::{BufRead, BufReader};

fn get_fuel(mass: u32) -> u32 {
    mass / 3 - 2
}

fn get_total_fuel(mut mass: u32) -> u32 {
    let mut fuel = 0;

    loop {
        if mass > 6 {
            mass = get_fuel(mass);
            fuel += mass;
        } else {
            break fuel;
        }
    }
}

fn main() {
    let mut total = 0;

    let file = File::open("../input.txt").unwrap();

    for line in BufReader::new(file).lines() {
        match line {
            Ok(m) => {
                total += get_total_fuel(match m.parse::<u32>() {
                    Ok(f) => f,
                    Err(_) => 0,
                })
            }
            Err(e) => println!("Error parsing line: {:?}", e),
        }
    }

    println!("{}", total);
}
