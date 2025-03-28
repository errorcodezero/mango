use crate::token::{LAYERS_OF_PRECEDENCE, Token};
use std::rc::Rc;

pub struct Tree {
    left: Option<Rc<Tree>>,
    right: Option<Rc<Tree>>,
    up: Option<Rc<Tree>>,
    data: Option<Rc<Token>>,
}

impl Tree {
    pub fn new(
        left: Option<Rc<Tree>>,
        right: Option<Rc<Tree>>,
        up: Option<Rc<Tree>>,
        data: Option<Rc<Token>>,
    ) -> Self {
        Self {
            left,
            right,
            up,
            data,
        }
    }
    pub fn builder(tokens: &[Token]) -> Self {
        let main = Tree::new(None, None, None, None);
        let mut lowest_precedence: Vec<&Token> = Vec::new();
        let mut precedence: i8 = LAYERS_OF_PRECEDENCE;

        for i in tokens.iter() {
            tokens.iter().for_each(|x| {
                if x.get_precedence() > 0 && x.get_precedence() == precedence {
                    lowest_precedence.push(x)
                }
            });
            lowest_precedence.clear();
            precedence -= 1;
        }

        main
    }
    pub fn get_right(&self) -> Option<Rc<Tree>> {
        if let Some(right) = &self.right {
            Some(right.clone())
        } else {
            None
        }
    }
    pub fn get_up(&self) -> Option<Rc<Tree>> {
        if let Some(up) = &self.up {
            Some(up.clone())
        } else {
            None
        }
    }
    pub fn get_data(&self) -> Option<Rc<Token>> {
        if let Some(data) = &self.data {
            Some(data.clone())
        } else {
            None
        }
    }
    pub fn set_left(&mut self, left: Option<Rc<Tree>>) {
        self.left = left;
    }
    pub fn set_right(&mut self, right: Option<Rc<Tree>>) {
        self.right = right;
    }
    pub fn set_up(&mut self, up: Option<Rc<Tree>>) {
        self.up = up;
    }
    pub fn set_data(&mut self, data: Option<Rc<Token>>) {
        self.data = data;
    }
}
