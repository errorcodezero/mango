use crate::token::{Token, TokenType};
use std::{borrow::Borrow, cell::RefCell, iter::Peekable};
use unicode_segmentation::{Graphemes, UnicodeSegmentation};

#[derive(Default)]
struct Scanner {
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
                "!" => self.match_push_token("=", TokenType::BangEqual, TokenType::Bang, &mut iter),
                "=" => {
                    self.match_push_token("=", TokenType::EqualEqual, TokenType::Equal, &mut iter)
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
                "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" => self.number(&mut iter),
                "\n" => self.line += 1,
                " " | "\t" | "\r" => {}
                _ => {}
            }
        }
        self.tokens.take()
    }

    fn number(&mut self, iter: &mut Peekable<Graphemes<'_>>) {
        let mut value = String::new();
        if let Some(next) = iter.next_if(|x| x.parse::<i8>().is_ok() || x == &".") {
            value += next
        };
        iter.next();
        if value.contains(".") {
            self.push_token_with_lexeme(TokenType::Float, value);
        }
    }

    fn string(&mut self, iter: &mut Peekable<Graphemes<'_>>) {
        let mut flag = false;
        let mut value = String::new();
        while let Some(next) = iter.next() {
            if next != "\"" {
                value += next;
                iter.next();
            } else {
                iter.next();
            }
        }
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

    fn push_token_with_lexeme(&mut self, token_type: TokenType, lexeme: String) {
        self.tokens.borrow_mut().push(Token::new(
            token_type,
            Some(lexeme),
            self.line,
            String::new(),
        ));
    }
}
