trait Speak {
    fn say_name (&self);

    fn say_hello (&self){
        println!("Hello!");
    }
}

struct Human{
    name: String,
}

impl Speak for Human {
        fn say_name (&self){
            println!("{}", self.name);
        }
}


fn main() {
    let james = Human {
        name: "James".to_string(),
    };

    james.say_name();
    james.say_hello();
}

