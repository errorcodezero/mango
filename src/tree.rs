use crate::token::Token;
use std::rc::Rc;

pub struct Tree<'a> {
    left: Rc<Option<Tree<'a>>>,
    right: Rc<Option<Tree<'a>>>,
    up: Rc<Option<Tree<'a>>>,
    data: Rc<Token<'a>>,
}

impl<'a> Tree<'a> {
    pub fn new(
        left: Rc<Option<Tree<'a>>>,
        right: Rc<Option<Tree<'a>>>,
        up: Rc<Option<Tree<'a>>>,
        data: Rc<Token<'a>>,
    ) -> Self {
        Self {
            left,
            right,
            up,
            data,
        }
    }
    pub fn get_left(&self) -> Rc<Option<Tree<'a>>> {
        self.left.clone()
    }
    pub fn get_right(&self) -> Rc<Option<Tree<'a>>> {
        self.right.clone()
    }
    pub fn get_up(&self) -> Rc<Option<Tree<'a>>> {
        self.up.clone()
    }
    pub fn get_data(&self) -> Rc<Token<'a>> {
        self.data.clone()
    }
}
