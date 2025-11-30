use std::{collections::HashSet, error::Error, fs};

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
struct Beacon {
    x: i32,
    y: i32,
    z: i32,
}

impl Beacon {
    fn get_coordinate(&self, index: usize) -> i32 {
        match index {
            0 => self.x,
            1 => self.y,
            2 => self.z,
            _ => panic!("Out of bounds"),
        }
    }
    fn turn_beacon(&self) -> Vec<Beacon> {
        let mut all_configs = Vec::new();
        for x_index in 0..3 {
            let x_val = self.get_coordinate(x_index);
            for x in [x_val, -x_val] {
                for y_index in 0..3 {
                    if x_index == y_index {
                        continue;
                    }
                    let y_val = self.get_coordinate(y_index);
                    for y in [y_val, -y_val] {
                        for z_index in 0..3 {
                            if x_index == z_index || y_index == z_index {
                                continue;
                            }
                            let z_val = self.get_coordinate(z_index);
                            for z in [z_val, -z_val] {
                                all_configs.push(Beacon { x, y, z });
                            }
                        }
                    }
                }
            }
        }
        all_configs
    }

    fn subtract(self, other: Beacon) -> Beacon {
        Beacon {
            x: self.x - other.x,
            y: self.y - other.y,
            z: self.z - other.z,
        }
    }
    fn add(self, other: Beacon) -> Beacon {
        Beacon {
            x: self.x + other.x,
            y: self.y + other.y,
            z: self.z + other.z,
        }
    }

    fn manhattan(self, other: Beacon) -> u32 {
        self.x.abs_diff(other.x) + self.y.abs_diff(other.y) + self.z.abs_diff(other.z)
    }
}

#[derive(Debug, Clone)]
struct Scanner {
    beacons: Vec<Beacon>,
}

// https://stackoverflow.com/a/64499219
fn transpose<T>(v: Vec<Vec<T>>) -> Vec<Vec<T>>
where
    T: Clone,
{
    assert!(!v.is_empty());
    (0..v[0].len())
        .map(|i| v.iter().map(|inner| inner[i].clone()).collect::<Vec<T>>())
        .collect()
}

impl Scanner {
    fn new() -> Self {
        Self {
            beacons: Vec::new(),
        }
    }
    fn turn_beacons(self) -> Vec<Vec<Beacon>> {
        transpose(
            self.beacons
                .iter()
                .map(|beacon| beacon.turn_beacon())
                .collect(),
        )
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let input = fs::read_to_string("input.txt")?;
    let mut scanners = Vec::new();
    for line in input.lines() {
        if line.is_empty() {
            continue;
        }
        if line.starts_with("--") {
            scanners.push(Scanner::new());
            continue;
        }
        let mut split_line = line.split(",");
        let beacon = Beacon {
            x: split_line.next().unwrap().parse().unwrap(),
            y: split_line.next().unwrap().parse().unwrap(),
            z: split_line.next().unwrap().parse().unwrap(),
        };
        scanners.last_mut().unwrap().beacons.push(beacon);
    }

    // let all_beacons = scanners
    //     .iter()
    //     .enumerate()
    //     .flat_map(|(i, scanner)| {
    //         scanner.beacons.iter().map(|&beacon| BeaconFromScanner {
    //             scanner: i,
    //             relative: beacon,
    //         })
    //     })
    //     .collect::<Vec<_>>();
    let mut scanner_positions = vec![Beacon { x: 0, y: 0, z: 0 }];
    let mut scanner_iter = scanners.into_iter();
    let mut root = scanner_iter.next().unwrap();
    scanners = scanner_iter.collect();
    let mut tmp_scanners = scanners.clone();
    'aLoop: loop {
        scanners = tmp_scanners.clone();
        for (j, scanner2) in scanners.iter().enumerate() {
            for beacon_conf in scanner2.clone().turn_beacons() {
                for (i1, ground_beacon_1) in beacon_conf.iter().enumerate() {
                    for (j1, ground_beacon_2) in root.beacons.iter().enumerate() {
                        let relative_position =
                            ground_beacon_2.clone().subtract(ground_beacon_1.clone());
                        let mut matching_beacons = 1;
                        let mut used_beacons_1 = vec![i1];
                        let mut used_beacons_2 = vec![j1];
                        for (i, beacon1) in beacon_conf.iter().enumerate() {
                            if used_beacons_1.contains(&i) {
                                continue;
                            }
                            for (j, beacon2) in root.beacons.iter().enumerate() {
                                if used_beacons_2.contains(&j) {
                                    continue;
                                }
                                let diff = beacon2.clone().subtract(beacon1.clone());
                                if diff == relative_position {
                                    matching_beacons += 1;
                                    used_beacons_1.push(i);
                                    used_beacons_2.push(j);
                                    break;
                                }
                            }
                        }
                        if matching_beacons >= 12 {
                            // println!("Scanner 1: 0");
                            // println!("Scanner 2: {j}");
                            // println!("Relative scanner position: {:?}", relative_position);
                            // println!("Used beacons 1: {:?}", used_beacons_1);
                            // println!("Used beacons 2: {:?}", used_beacons_2);
                            // all_beacons.retain(|beacon| );
                            // final_scanners.get_mut(0).unwrap().beacons.extend(
                            //     used_beacons_2.iter().map(|beacon| {
                            //         scanner2
                            //             .beacons
                            //             .get(*beacon)
                            //             .unwrap()
                            //             .clone()
                            //             .subtract(ground_truth.clone())
                            //     }),
                            // );

                            // final_scanners.get_mut(j).unwrap().beacons.extend(
                            //     used_beacons_1.iter().map(|beacon| {
                            //         ground_truth
                            //             .clone()
                            //             .subtract(scanner1.beacons.get(*beacon).unwrap().clone())
                            //     }),
                            // );
                            //
                            scanner_positions.push(relative_position.clone());
                            root.beacons.extend(
                                beacon_conf
                                    .iter()
                                    .map(|beacon| relative_position.clone().add(beacon.clone())),
                            );
                            println!("{:?}", tmp_scanners.first().unwrap());
                            tmp_scanners.remove(j);
                            if tmp_scanners.is_empty() {
                                break 'aLoop;
                            }

                            continue 'aLoop;
                        }
                    }
                }
            }
        }
    }
    println!("{:?}", root.beacons.iter().collect::<HashSet<_>>().len());

    let mut max = 0;
    for scanner1 in scanner_positions.iter() {
        for scanner2 in scanner_positions.iter() {
            max = max.max(scanner1.clone().manhattan(scanner2.clone()));
        }
    }

    println!("{max}");

    // for _ in 0..1000 {
    //     let mut new_relatives = relatives.clone();
    //     for (i, relative1) in relatives.iter().enumerate() {
    //         for (j, relative2) in relatives.iter().enumerate() {
    //             if i == j {
    //                 continue;
    //             }
    //             if relative1.scanner1 == relative2.scanner2 {
    //                 new_relatives.push(Relative {
    //                     scanner1: relative1.scanner1,
    //                     scanner2: relative2.scanner2,
    //                     relative: relative2
    //                         .relative
    //                         .clone()
    //                         .subtract(relative1.relative.clone()),
    //                 })
    //             }
    //         }
    //     }
    //     relatives = new_relatives;
    // }

    Ok(())
}
