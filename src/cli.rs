use clap::Parser;
use clio::Input;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub enum Args {
    Run {
        #[clap(value_parser)]
        path: Input,
    },
}
