use std::io::Read;

use anyhow::Result;
use clap::Parser;
use cli::Args;

mod cli;

fn main() -> Result<()> {
    let args = Args::parse();

    match args {
        Args::Run { path } => {
            let mut path = path;
            let mut text: String = String::new();
            if let Some(file) = path.get_file() {
                file.read_to_string(&mut text)?;
            }

            println!("{}", text)
        }
    }

    Ok(())
}
