use crate::token::{Lexeme, Token, TokenType};
use std::{cell::RefCell, collections::HashMap, iter::Peekable};
use unicode_segmentation::{Graphemes, UnicodeSegmentation};

#[derive(Default)]
pub struct Scanner {
    start: usize,
    current: usize,
    line: usize,
    file: String,
    source: RefCell<String>,
    tokens: RefCell<Vec<Token>>,
}

impl Scanner {
    pub fn new(source: String) -> Scanner {
        Scanner {
            source: RefCell::new(source),
            ..Default::default()
        }
    }

    pub fn scan(&mut self) -> Vec<Token> {
        let source = self.source.take();
        let mut iter = source.graphemes(true).peekable();
        let mut keywords: HashMap<&str, TokenType> = HashMap::new();
        keywords.insert("end", TokenType::End);
        keywords.insert("int", TokenType::Int);
        keywords.insert("float", TokenType::Float);
        keywords.insert("super", TokenType::Super);
        keywords.insert("this", TokenType::This);
        keywords.insert("if", TokenType::If);
        keywords.insert("else", TokenType::Else);
        keywords.insert("for", TokenType::For);
        keywords.insert("while", TokenType::While);
        keywords.insert("sub", TokenType::Sub);
        keywords.insert("return", TokenType::Return);
        keywords.insert("nil", TokenType::Nil);
        keywords.insert("true", TokenType::True);
        keywords.insert("while", TokenType::While);
        keywords.insert("string", TokenType::String);
        keywords.insert("false", TokenType::False);
        keywords.insert("print", TokenType::Print);
        keywords.insert("class", TokenType::Class);
        // used while let instead of for loop since that would move the value and not let
        // me use iter inside the loop
        while let Some(c) = iter.next() {
            match c {
                "(" => self.push_token(TokenType::LeftParen),
                ")" => self.push_token(TokenType::RightParen),
                "{" => self.push_token(TokenType::LeftBrace),
                "}" => self.push_token(TokenType::RightBrace),
                "," => self.push_token(TokenType::Comma),
                "." => self.push_token(TokenType::Dot),
                "+" => self.push_token(TokenType::Plus),
                "-" => self.push_token(TokenType::Minus),
                "*" => self.push_token(TokenType::Star),
                "/" => self.push_token(TokenType::Slash),
                "!" => self.match_push_token(
                    "=",
                    TokenType::BangEqual,
                    TokenType::LogicalNot,
                    &mut iter,
                ),
                "=" => {
                    self.match_push_token("=", TokenType::EqualEqual, TokenType::Equal, &mut iter)
                }
                "&" => {
                    self.match_push_token(
                        "&",
                        TokenType::LogicalAnd,
                        TokenType::BitwiseAnd,
                        &mut iter,
                    );
                }
                "^" => {
                    self.push_token(TokenType::BitwiseXor);
                }
                "<" => self.match_push_token("=", TokenType::LessEqual, TokenType::Less, &mut iter),
                ">" => self.match_push_token(
                    "=",
                    TokenType::GreaterEqual,
                    TokenType::Greater,
                    &mut iter,
                ),
                "~" => {
                    while let Some(next) = iter.next() {
                        if next == "\n" {
                            self.line += 1;
                            break;
                        }
                        iter.next();
                    }
                }
                "\"" => self.string(&mut iter),
                "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" => {
                    self.number(&mut iter, c)
                }
                "\n" => self.line += 1,
                " " | "\t" | "\r" => {}
                _ => {
                    if self.is_alphanumeric(c) {
                        self.identifier(&mut iter, c, &keywords);
                    }
                }
            }
        }
        self.push_token(TokenType::EndOfFile);
        self.tokens.take()
    }

    fn number(&mut self, iter: &mut Peekable<Graphemes<'_>>, c: &str) {
        let mut value = String::new();
        value += c;
        let mut token_type = TokenType::IntLiteral;
        for next in iter {
            match next {
                "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" => {
                    value += next;
                }
                "." => {
                    token_type = TokenType::FloatLiteral;
                    value += next;
                }
                _ => {
                    break;
                }
            }
        }
        match token_type {
            TokenType::IntLiteral => {
                self.push_token_with_lexeme(token_type, Lexeme::Int(value.parse().unwrap()));
            }
            TokenType::FloatLiteral => {
                self.push_token_with_lexeme(token_type, Lexeme::Float(value.parse().unwrap()));
            }
            _ => (),
        }
    }

    fn string(&mut self, iter: &mut Peekable<Graphemes<'_>>) {
        let mut value = String::new();
        while let Some(next) = iter.peek() {
            if next != &"\"" {
                value += next;
                iter.next();
            } else {
                iter.next();
                break;
            }
        }
        self.push_token_with_lexeme(TokenType::StringLiteral, Lexeme::String(value));
    }

    fn identifier(
        &mut self,
        iter: &mut Peekable<Graphemes<'_>>,
        c: &str,
        keywords: &HashMap<&str, TokenType>,
    ) {
        let mut value = String::new();
        value += c;
        while let Some(next) = iter.peek() {
            if self.is_alphanumeric(next) {
                value += next;
                iter.next();
            } else {
                iter.next();
                break;
            }
        }
        if !value.is_empty() {
            if let Some(value) = keywords.get(value.as_str()) {
                self.push_token(value.clone());
            } else {
                self.push_token_with_lexeme(TokenType::Identifier, Lexeme::Identifier(value));
            }
        }
    }

    fn is_alphanumeric(&self, target: &str) -> bool {
        let mut flag = true;
        for c in target.chars() {
            if !c.is_alphanumeric() {
                flag = false;
                break;
            }
        }
        flag
    }

    fn match_push_token(
        &mut self,
        target: &str,
        target_type: TokenType,
        fallback_type: TokenType,
        iter: &mut Peekable<Graphemes<'_>>,
    ) {
        if let Some(next) = iter.next() {
            if next == target {
                self.push_token(target_type);
            } else {
                self.push_token(fallback_type);
            }
        } else {
            self.push_token(fallback_type);
        }
    }

    fn push_token(&mut self, token_type: TokenType) {
        self.tokens
            .borrow_mut()
            .push(Token::new(token_type, None, self.line, String::new()));
    }

    fn push_token_with_lexeme(&mut self, token_type: TokenType, lexeme: Lexeme) {
        self.tokens.borrow_mut().push(Token::new(
            token_type,
            Some(lexeme),
            self.line,
            String::new(),
        ));
    }
}
