pub fn error(message: &str, line: &str, fileName: &str, lineNum: i32) {
    eprintln!("{message} {fileName}\n {lineNum} | {line}");
}
