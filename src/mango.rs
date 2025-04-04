pub struct Mango {
    has_error: bool,
}

impl Mango {
    pub fn error(error: &str, file: &str, line: u32, line_contents: &str) {
        println!("{error} - {file}:{line}\n{line} | {line_contents}")
    }
}
