//
// Cons list that may be edited at any position
//

#[derive(Debug)]
pub enum Link<T> {
    Cons(Box<Node<T>>),
    Nil,
}

#[derive(Debug)]
pub struct Node<T> {
    val: T,
    next: Link<T>,
}

impl<T> Link<T> {
    fn take(&mut self) -> Link<T> {
        std::mem::replace(self, Link::Nil)
    }

    pub fn cons(self, val: T) -> Link<T> {
        Link::Cons(Box::new(Node {val, next: self}))
    }

    pub fn push(&mut self, val: T) {
        *self = self.take().cons(val)
    }

    pub fn pop(&mut self) -> Option<T> {
        if let Link::Cons(node) = self.take() {
            *self = node.next;
            Some(node.val)
        } else {
            None
        }
    }

    pub fn next(&mut self) -> &mut Link<T> {
        match self {
            Link::<T>::Cons(node) => &mut node.next,
            _ => self,
        }
    }

    pub fn ith(&mut self, i: i32) -> &mut Link<T> {
        let mut link = self;
        for _ in 0..i {
            match link {
                Link::<T>::Cons(node) => link = &mut node.next,
                _ => break,
            }
        }
        link
    }

    pub fn last(&mut self) -> &mut Link<T> {
        let mut link = self;
        while let Link::<T>::Cons(node) = link {
            link = &mut node.next
        }
        link
    }

    pub fn split(&mut self) {
        self.take();
    }

    pub fn merge(&mut self, list: Link<T>) {
        *self = list;
    }

    pub fn splice(&mut self, mut list: Link<T>) {
        *list.last() = self.take();
        *self = list;
    }

    pub fn extract(&mut self, i: i32) -> Link<T> {
        let mut head = self.take();
        *self = head.ith(i).take();
        head
    }

    pub fn iter_mut(&mut self) -> IterMut<T> {
        IterMut { at: Some(self) }
    }
}

pub struct IterMut<'a, T> {
    at: Option<&'a mut Link<T>>,
}

impl<'a, T> Iterator for IterMut<'a, T> {
    type Item = &'a mut T;

    fn next(&mut self) -> Option<Self::Item> {
        match self.at.take() {
            Some(Link::Cons(node)) => {
                self.at = Some(&mut node.next);
                Some(&mut node.val)
            }
            _ => None,
        }
    }
}

fn main() {
    let mut head = Link::Nil.cons(44).cons(33).cons(22).cons(11);

    // push at any position, including last
    head.last().push(55);
    
    // pop at any position, not just head
    assert_eq!(head.next().pop(), Some(22));

    // splice list into list at any position
    println!("{:?}", head);
    head.ith(2).splice(Link::Nil.cons(222).cons(111));
    println!("{:?}", head);
    
    // extract sublist from list
    println!("{:?}", head.extract(2));
    println!("{:?}", head);
    for v in head.iter_mut() {
        *v += 1;
        println!("{}", v);
    }
}