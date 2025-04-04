#[derive(Default)]
pub enum TokenType {
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Comma,
    Dot,
    Minus,
    Plus,
    Semicolon,
    Slash,
    Star,
    Colon,
    Bang,
    BangEqual,
    Equal,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    Identifier,
    String,
    Float,
    Int,
    And,
    Class,
    Else,
    False,
    Sub,
    For,
    If,
    Nil,
    Or,
    Print,
    Return,
    Super,
    This,
    True,
    Var,
    While,
    End,
    #[default]
    EndOfFile,
}

#[derive(Default)]
pub struct Token {
    token_type: TokenType,
    lexeme: Option<String>,
    line: usize,
    file: String,
}

impl Token {
    pub fn new(token_type: TokenType, lexeme: Option<String>, line: usize, file: String) -> Token {
        Token {
            token_type,
            lexeme,
            line,
            file,
        }
    }
    pub fn get_lexeme(&self) -> &Option<String> {
        &self.lexeme
    }
    pub fn get_line(&self) -> usize {
        self.line
    }
    pub fn get_file(&self) -> &str {
        &self.file[..]
    }
    pub fn get_token_type(&self) -> &TokenType {
        &self.token_type
    }
}
