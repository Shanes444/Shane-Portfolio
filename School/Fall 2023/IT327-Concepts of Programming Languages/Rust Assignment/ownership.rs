//Shane Stevens
//program that shows off ownership

fn main(){
    let word = String::from("Hello");
    showdata(&word);
    println!("{}",word);
}

fn showdata(word:&String){
    println!("{}",word);
}