use unicode_segmentation::UnicodeSegmentation;

pub const LAYERS_OF_PRECEDENCE: i8 = 14;

#[derive(Debug)]
pub enum Token {
    // Primitives included in the language that don't need the standard library
    Int,
    Float,
    Char,
    Bool,
    Null,
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
    CharLiteral(String),
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
    // Parenthesis
    OpeningParenthesis,
    ClosingParenthesis,
    // Comparison
    Equality,
    NotEqual,
    GreaterThan,
    GreaterThanEqual,
    LessThan,
    LessThanEqual,
    // Comments
    Comment,
    DocComment,
    // Variable
    Name(String),
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
    // from c++'s order of operations shortened since not all c++ operations exist in this yet
    pub fn get_precedence(&self) -> i8 {
        match *self {
            Token::String
            | Token::Int
            | Token::Float
            | Token::Char
            | Token::Bool
            | Token::Eol
            | Token::Eof
            | Token::Comment
            | Token::DocComment => -1,
            Token::IntLiteral(_)
            | Token::CharLiteral(_)
            | Token::BoolLiteral(_)
            | Token::FloatLiteral(_)
            | Token::StringLiteral(_)
            | Token::Null => 0,
            Token::Name(_) | Token::OpeningParenthesis | Token::ClosingParenthesis => 1,
            Token::LogicalNot | Token::BitwiseNot => 2,
            Token::Multiply | Token::Divide => 3,
            Token::Add | Token::Subtract => 4,
            Token::LShift | Token::RShift => 5,
            Token::GreaterThan
            | Token::LessThan
            | Token::GreaterThanEqual
            | Token::LessThanEqual => 6,
            Token::Equality | Token::NotEqual => 7,
            Token::BitwiseAnd => 8,
            Token::BitwiseXor => 9,
            Token::BitwiseOr => 10,
            Token::LogicalAnd => 11,
            Token::LogicalOr => 12,
            // 13
            Token::Assignment | Token::Print => 14,
        }
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
                        "<" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "<" {
                                    tokens.push(Token::LShift);
                                    skip += 1;
                                } else if next == "=" {
                                    tokens.push(Token::LessThanEqual)
                                } else {
                                    tokens.push(Token::LessThan);
                                }
                            } else {
                                tokens.push(Token::LessThan);
                            }
                        }
                        ">" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == ">" {
                                    tokens.push(Token::RShift);
                                    skip += 1;
                                } else if next == "=" {
                                    tokens.push(Token::GreaterThanEqual)
                                } else {
                                    tokens.push(Token::GreaterThan);
                                }
                            } else {
                                tokens.push(Token::GreaterThan);
                            }
                        }
                        "," => {
                            tokens.push(Token::Eol);
                        }
                        "~" => {
                            if let Some(next) = line.get(i + 1..i + 2) {
                                if next == "~" {
                                    if let Some(next) = line.get(i + 2..i + 3) {
                                        if next == "!" {
                                            tokens.push(Token::DocComment);
                                        } else {
                                            tokens.push(Token::Comment);
                                        }
                                    } else {
                                        tokens.push(Token::Comment);
                                    }
                                    break;
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
                                skip += literal.len() + 1;
                                tokens.push(Token::StringLiteral(literal));
                            }
                        }
                        "'" => {
                            // first if-let is there for emojis and whatnot
                            if let Some(substr) = line.get(i + 1..line.len()) {
                                if let Some(char) = substr.graphemes(true).nth(0) {
                                    tokens.push(Token::CharLiteral(char.to_string()));
                                    skip += 2;
                                }
                            }
                        }
                        "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" => {
                            let mut literal = String::new();
                            literal += curr;
                            if let Some(substr) = line.get(i + 1..line.len()) {
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
                                    } else {
                                        break;
                                    }
                                }
                                if literal.contains(".") {
                                    tokens.push(Token::FloatLiteral(literal.parse().unwrap()));
                                } else {
                                    tokens.push(Token::IntLiteral(literal.parse().unwrap()));
                                }
                                skip += literal.len() - 1;
                            }
                        }
                        "{" => tokens.push(Token::OpeningParenthesis),
                        "}" => tokens.push(Token::ClosingParenthesis),
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
                                } else if buf == "true" {
                                    tokens.push(Token::BoolLiteral(true))
                                } else if buf == "false" {
                                    tokens.push(Token::BoolLiteral(false))
                                } else if buf == "null" {
                                    tokens.push(Token::Null)
                                } else {
                                    tokens.push(Token::Name(buf.clone()));
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
