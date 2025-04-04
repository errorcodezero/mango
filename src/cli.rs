use clap::Parser;

#[derive(Parser)]
pub enum Cli {
    Run { input: String },
    Check { file: String },
}
