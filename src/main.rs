use crate::cli::Cli;
use anyhow::Result;
use clap::Parser;
use scanner::Scanner;
use std::io::Read;

mod cli;
mod mango;
mod scanner;
mod token;

fn main() -> Result<()> {
    let args = Cli::parse();
    if let Cli::Run { input } = args {
        let mut file = clio::Input::new(&input)?;

        let mut source = String::new();

        let _ = file.read_to_string(&mut source);

        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        println!("{:#?}", tokens);
    }
    Ok(())
}
