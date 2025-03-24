pub enum Token<'a> {
    // Primitives included in the language that don't need the standard library
    Int,
    Float,
    Char,
    Bool,
    // Temporary and will be removed when I can get an actual standard library to work
    String,
    Print,
    // Literals
    IntLiteral(i32),
    FloatLiteral(f32),
    CharLiteral(char),
    BoolLiteral(bool),
    StringLiteral(&'a str),
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
    Variable,
    // End of File
    Eof,
    // End of Statement
    Eos,
}

impl<'a> Token<'a> {}

impl<'a> Default for Token<'a> {
    fn default() -> Self {
        Self::Eof
    }
}
