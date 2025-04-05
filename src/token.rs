#[derive(Default, Debug, Clone)]
pub enum TokenType {
    LeftParen,
    RightParen,
    BitwiseAnd,
    LogicalAnd,
    BitwiseOr,
    LogicalOr,
    BitwiseNot,
    BitwiseXor,
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
    LogicalNot,
    BangEqual,
    Equal,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    Identifier,
    StringLiteral,
    FloatLiteral,
    IntLiteral,
    Class,
    Else,
    False,
    Sub,
    For,
    If,
    Nil,
    Print,
    Return,
    Super,
    This,
    True,
    String,
    Char,
    Int,
    Float,
    While,
    End,
    #[default]
    EndOfFile,
}

#[derive(Debug)]
pub enum Lexeme {
    String(String),
    Identifier(String),
    Int(i32),
    Float(f32),
    Bool(bool),
}

#[derive(Default, Debug)]
pub struct Token {
    token_type: TokenType,
    lexeme: Option<Lexeme>,
    line: usize,
}

impl Token {
    pub fn new(token_type: TokenType, lexeme: Option<Lexeme>, line: usize) -> Token {
        Token {
            token_type,
            lexeme,
            line,
        }
    }
    pub fn get_lexeme(&self) -> &Option<Lexeme> {
        &self.lexeme
    }
    pub fn get_line(&self) -> usize {
        self.line
    }
    pub fn get_token_type(&self) -> &TokenType {
        &self.token_type
    }
}
