use std::env;
use std::fs;
use std::process;

use std::error::Error;

struct Input {
    pathname: String,
}

impl Input {
    fn parse(args: &[String]) -> Result<Input, &'static str> {
        if args.len() < 2 {
            return Err("Missing input file");
        }

        let pathname = args[1].clone();

        return Ok(Input {pathname});
    }
}

struct Dial {
    pos: i32,
    acc: i32,
}

impl Dial {
    const DEFAULT_POSITION: i32 = 50;
    const MAX_VALUE: i32 = 100;

    fn new(pos: i32, acc: i32) -> Self {
        return Self {pos, acc};
    }

    fn rotate_left(&mut self, distance: i32) {
        if self.pos == 0 {
            self.acc = self.acc - 1;
        }

        self.pos = self.pos - distance;

        while self.pos <= 0 {
            self.pos = self.pos + Dial::MAX_VALUE;
            self.acc = self.acc + 1;
        }

        self.pos = self.pos % Dial::MAX_VALUE;
    }

    fn rotate_right(&mut self, distance: i32) {
        self.pos = self.pos + distance;
        self.acc = self.acc + (self.pos / Dial::MAX_VALUE);
        self.pos = self.pos % Dial::MAX_VALUE;
    }
}

fn run(input: Input) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(input.pathname)?;

    let mut dial = Dial::new(Dial::DEFAULT_POSITION, 0);

    for line in contents.lines() {
        let rotation = line.chars().nth(0).unwrap();
        let distance = &line[1..];

        let distance: i32 = distance.trim().parse()
            .expect("Input file is badly formatted");

        match rotation {
            'L' => dial.rotate_left(distance),
            'R' => dial.rotate_right(distance),
            r => panic!("Unexpected rotation {r}"),
        };
    }

    println!("{}", dial.acc);

    return Ok(());
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let input = Input::parse(&args).unwrap_or_else(|err| {
        eprintln!("Error while parsing command line: {err}");
        process::exit(1);
    });

    if let Err(e) = run(input) {
        eprintln!("Error: {e}");
        process::exit(1);
    }
}
