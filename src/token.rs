pub enum TokenType {
    // Primitives included in the language that don't need the standard library
    Int,
    Float,
    Char,
    Bool,
    String,
    // Literals
    IntLiteral,
    FloatLiteral,
    CharLiteral,
    BoolLiteral,
    StringLiteral,
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
    // Comments
    Comment,
    DocComment,
    // Variable
    Variable,
    // End of File
    Eof,
}
