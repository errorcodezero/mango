use anyhow::Result;
use clap::Parser;
use cli::Args;
use std::io::Read;
use token::Token;

mod cli;
mod error;
mod token;
mod tree;

fn main() -> Result<()> {
    let args = Args::parse();

    match args {
        Args::Run { path } => {
            let mut path = path;
            let mut text: String = String::new();
            if let Some(file) = path.get_file() {
                file.read_to_string(&mut text)?;
            }
            let mut tokens = Vec::new();
            Token::from_str(&text, &mut tokens);

            println!("{text}");
            println!("{:#?}", tokens);
        }
    }

    Ok(())
}
