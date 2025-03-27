use unicode_segmentation::UnicodeSegmentation;

#[derive(Debug)]
pub enum Token {
    // Primitives included in the language that don't need the standard library
    Int,
    Float,
    Char,
    Bool,
    // Temporary and will be removed when I can get an actual standard library to work
    String,
    Print,
    // Math
    Add,
    Subtract,
    Multiply,
    Divide,
    // Literals
    IntLiteral(i32),
    FloatLiteral(f32),
    CharLiteral(char),
    BoolLiteral(bool),
    StringLiteral(String),
    // Bitwise Operators
    BitwiseAnd,
    BitwiseOr,
    BitwiseNot,
    BitwiseXor,
    LShift,
    RShift,
    // Logical Operators
    LogicalAnd,
    LogicalOr,
    LogicalNot,
    // Comparison
    Equality,
    NotEqual,
    GreaterThan,
    LessThan,
    // Comments
    Comment,
    DocComment,
    // Variable
    Variable(String),
    Assignment,
    // End of line
    Eol,
    // End of file
    Eof,
}

impl Token {
    pub fn from_str(text: &str, tokens: &mut Vec<Token>) {
        text.lines().for_each(|x| Token::from_line(x, tokens));
        tokens.push(Token::Eof);
    }
    fn from_line(line: &str, tokens: &mut Vec<Token>) {
        let mut skip = 0;
        let mut buf = String::new();
        for i in 0..line.len() {
            if skip == 0 {
                if let Some(curr) = line.get(i..i + 1) {
                    match curr {
                        "+" => tokens.push(Token::Add),
                        "*" => tokens.push(Token::Multiply),
                        "-" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == ">" {
                                    tokens.push(Token::Assignment);
                                    skip += 1;
                                } else {
                                    tokens.push(Token::Subtract);
                                }
                            } else {
                                tokens.push(Token::Subtract);
                            }
                        }
                        "/" => tokens.push(Token::Divide),
                        "=" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "=" {
                                    tokens.push(Token::Equality);
                                    skip += 1;
                                } else {
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                        "," => {
                            tokens.push(Token::Eol);
                        }
                        "~" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "~" {
                                    tokens.push(Token::Comment);
                                    skip += 1;
                                } else {
                                    tokens.push(Token::BitwiseNot);
                                }
                            } else {
                                tokens.push(Token::BitwiseNot);
                            }
                        }
                        "&" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "&" {
                                    tokens.push(Token::LogicalAnd);
                                    skip += 1;
                                } else {
                                    tokens.push(Token::BitwiseAnd);
                                }
                            } else {
                                tokens.push(Token::BitwiseAnd);
                            }
                        }
                        "^" => tokens.push(Token::BitwiseXor),
                        "|" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "|" {
                                    tokens.push(Token::LogicalOr);
                                    skip += 1;
                                } else {
                                    tokens.push(Token::BitwiseOr);
                                }
                            } else {
                                tokens.push(Token::BitwiseOr);
                            }
                        }
                        "!" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "=" {
                                    tokens.push(Token::NotEqual);
                                    skip += 1;
                                } else {
                                    tokens.push(Token::LogicalNot);
                                }
                            } else {
                                tokens.push(Token::LogicalNot);
                            }
                        }
                        "\"" => {
                            let mut literal = String::new();
                            if let Some(substr) = line.get(i + 1..line.len() - 1) {
                                for i in substr.graphemes(true) {
                                    if i == "\"" {
                                        break;
                                    } else {
                                        literal += i;
                                    }
                                }
                                tokens.push(Token::StringLiteral(literal));
                                skip += substr.len();
                            }
                        }
                        "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" => {
                            let mut literal = String::new();
                            literal += curr;
                            if let Some(substr) = line.get(i + 1..line.len()) {
                                println!("{}", line);
                                for i in substr.chars() {
                                    if i == '1'
                                        || i == '2'
                                        || i == '3'
                                        || i == '4'
                                        || i == '5'
                                        || i == '6'
                                        || i == '7'
                                        || i == '8'
                                        || i == '9'
                                        || i == '0'
                                        || i == '.'
                                    {
                                        literal.push(i);
                                    }
                                }
                                if literal.contains(".") {
                                    tokens.push(Token::FloatLiteral(literal.parse().unwrap()));
                                } else {
                                    tokens.push(Token::IntLiteral(literal.parse().unwrap()));
                                }
                                skip += literal.len();
                            }
                        }
                        _ => {
                            if curr != " " && curr != "." && curr != "(" && curr != ")" {
                                buf += curr;
                            } else if buf != " " && !buf.is_empty() {
                                if buf == "string" {
                                    tokens.push(Token::String);
                                } else if buf == "int" {
                                    tokens.push(Token::Int);
                                } else if buf == "float" {
                                    tokens.push(Token::Float);
                                } else if buf == "char" {
                                    tokens.push(Token::Char)
                                } else if buf == "bool" {
                                    tokens.push(Token::Bool)
                                } else if buf == "print" {
                                    tokens.push(Token::Print)
                                } else {
                                    tokens.push(Token::Variable(buf.clone()));
                                }
                                buf.clear();
                            }
                        }
                    }
                }
            } else {
                skip -= 1;
            }
        }
        tokens.push(Token::Eol);
    }
}

impl Default for Token {
    fn default() -> Self {
        Self::Comment
    }
}
