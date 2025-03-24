use crate::token::Token;
//use crate::tree::Tree;

pub struct Scanner<'a> {
    source: &'a str,
    tokens: Vec<Token<'a>>,
}

impl<'a> Scanner<'a> {
    pub fn new() -> Self {
        Self {
            source: "",
            tokens: Vec::new(),
        }
    }
    pub fn new_with_source(source: &'a str) -> Self {
        Self {
            source,
            ..Default::default()
        }
    }
    pub fn get_tokens(&self) -> &[Token] {
        &self.tokens
    }
    pub fn get_source(&self) -> &str {
        self.source
    }
    //pub fn scan(&mut self) -> Tree {
    //    for line in self.source.lines() {
    //        for c in line.chars() {}
    //    }
    //}
}

#[allow(clippy::needless_lifetimes)]
impl<'a> Default for Scanner<'a> {
    fn default() -> Self {
        Scanner::new()
    }
}
