use crate::expression::{
    BinaryExpression, DummyExpression, Expression, GroupingExpression, LiteralExpression,
    UnaryExpression,
};

pub trait Visitor<T> {
    fn visit_binary<L: Expression, R: Expression>(
        &mut self,
        expression: &mut BinaryExpression<L, R>,
    ) -> T;
    fn visit_unary<R: Expression>(&mut self, expression: &mut UnaryExpression<R>) -> T;
    fn visit_literal<D>(&mut self, expression: &mut LiteralExpression<D>) -> T;
    fn visit_grouping<E: Expression>(&mut self, expression: &mut GroupingExpression<E>) -> T;
}

pub struct ASTPrinter {}

impl ASTPrinter {
    pub fn print<E: Expression>(&mut self, expression: &mut E) -> String {
        expression.accept(self)
    }
    fn parenthesis<A: Expression, B: Expression>(
        &mut self,
        name: &str,
        e1: Option<&mut A>,
        e2: Option<&mut B>,
    ) -> String {
        let mut result = String::from("( ");
        result += name;
        if let Some(e1) = e1 {
            result += " ";
            result += e1.accept(self).as_str();
        }
        if let Some(e2) = e2 {
            result += " ";
            result += e2.accept(self).as_str();
        }
        result += " )";
        result
    }
}

impl Visitor<String> for ASTPrinter {
    fn visit_unary<R: Expression>(&mut self, expression: &mut UnaryExpression<R>) -> String {
        self.parenthesis::<R, DummyExpression>("operator", Some(&mut expression.right), None)
    }
    fn visit_binary<L: Expression, R: Expression>(
        &mut self,
        expression: &mut BinaryExpression<L, R>,
    ) -> String {
        self.parenthesis::<L, R>(
            "operator",
            Some(&mut expression.left),
            Some(&mut expression.right),
        )
    }
    fn visit_grouping<E: Expression>(&mut self, expression: &mut GroupingExpression<E>) -> String {
        self.parenthesis::<E, DummyExpression>("group", Some(&mut expression.expression), None)
    }
    fn visit_literal<D>(&mut self, expression: &mut LiteralExpression<D>) -> String {
        self.parenthesis::<DummyExpression, DummyExpression>("literal", None, None)
    }
}
