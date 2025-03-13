fn main(){
    let num1 = 7;
    let num2 = 8;
    let num3 = 7.2;
    let num4 = 7.8;
    add(num1, num2);
}

fn add(num1: i32, num2: i32){
    println!("{}",(num1+num2));
}

fn add(num1: f64, num2: f64){
    println!("{}",(num1+num2));
}
