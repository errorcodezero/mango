use crate::token::Token;
use std::rc::Rc;

pub struct Tree {
    left: Rc<Option<Tree>>,
    right: Rc<Option<Tree>>,
    up: Rc<Option<Tree>>,
    data: Rc<Token>,
}

impl Tree {
    pub fn new(
        left: Rc<Option<Tree>>,
        right: Rc<Option<Tree>>,
        up: Rc<Option<Tree>>,
        data: Rc<Token>,
    ) -> Self {
        Self {
            left,
            right,
            up,
            data,
        }
    }
    pub fn get_left(&self) -> Rc<Option<Tree>> {
        self.left.clone()
    }
    pub fn get_right(&self) -> Rc<Option<Tree>> {
        self.right.clone()
    }
    pub fn get_up(&self) -> Rc<Option<Tree>> {
        self.up.clone()
    }
    pub fn get_data(&self) -> Rc<Token> {
        self.data.clone()
    }
}
