use crate::cli::Cli;
use anyhow::Result;
use clap::Parser;
use expression::{BinaryExpression, GroupingExpression, LiteralExpression, UnaryExpression};
use scanner::Scanner;
use std::io::Read;
use token::{Lexeme, Token, TokenType};
use visitor::ASTPrinter;

mod cli;
mod expression;
mod mango;
mod scanner;
mod token;
mod visitor;

fn main() -> Result<()> {
    let args = Cli::parse();
    if let Cli::Run { input } = args {
        let mut file = clio::Input::new(&input)?;

        let mut source = String::new();

        let _ = file.read_to_string(&mut source);

        //let mut scanner = Scanner::new(source);
        //let tokens = scanner.scan();
        //
        //println!("{:#?}", tokens);
        let mut printer = ASTPrinter {};
        let mut expr = BinaryExpression {
            right: UnaryExpression {
                operator: Token::new(TokenType::Plus, Some(Lexeme::String("".to_string())), 0),
                right: LiteralExpression::<i32> { data: 32 },
            },
            left: GroupingExpression {
                expression: LiteralExpression::<i32> { data: 423 },
            },
            operator: Token::new(TokenType::Plus, Some(Lexeme::String("+".to_string())), 0),
        };
        let output = printer.print(&mut expr);
        println!("{output}");
    }
    Ok(())
}
