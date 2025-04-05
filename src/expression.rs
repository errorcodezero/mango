use crate::{token::Token, visitor::Visitor};

pub trait Expression {
    fn accept<T, V: Visitor<T>>(&mut self, visitor: &mut V) -> T;
}

pub struct DummyExpression {}

impl Expression for DummyExpression {
    fn accept<T, V: Visitor<T>>(&mut self, visitor: &mut V) -> T {
        panic!("Don't actually use this!")
    }
}

pub struct BinaryExpression<L: Expression, R: Expression> {
    pub left: L,
    pub right: R,
    pub operator: Token,
}

impl<L: Expression, R: Expression> Expression for BinaryExpression<L, R> {
    fn accept<T, V: Visitor<T>>(&mut self, visitor: &mut V) -> T {
        visitor.visit_binary::<L, R>(self)
    }
}

pub struct UnaryExpression<R: Expression> {
    pub right: R,
    pub operator: Token,
}

impl<R: Expression> Expression for UnaryExpression<R> {
    fn accept<T, V: Visitor<T>>(&mut self, visitor: &mut V) -> T {
        visitor.visit_unary::<R>(self)
    }
}

pub struct GroupingExpression<E: Expression> {
    pub expression: E,
}

impl<E: Expression> Expression for GroupingExpression<E> {
    fn accept<T, V: Visitor<T>>(&mut self, visitor: &mut V) -> T {
        visitor.visit_grouping::<E>(self)
    }
}

pub struct LiteralExpression<D> {
    pub data: D,
}

impl<D> LiteralExpression<D> {
    pub fn get_data(&self) -> &D {
        &self.data
    }
}

impl<D> Expression for LiteralExpression<D> {
    fn accept<T, V: Visitor<T>>(&mut self, visitor: &mut V) -> T {
        visitor.visit_literal::<D>(self)
    }
}
