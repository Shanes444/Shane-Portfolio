//Shane Stevens
//a simple integer calculator

use std::io;

fn main(){
    let mut num1;
    let mut num2;
    let mut result = 0;
    let mut num1str = String::new();
    let mut num2str = String::new();
    let mut operator = String::new();
    let mut correctoperator;
    let mut continuestr = String::new();
    let mut continuebool = true;

    while continuebool == true{
        println!("Enter the first number: ");
        io::stdin().read_line(& mut num1str).expect("please enter a string");
        num1 = num1str.trim().parse::<i32>().unwrap();
        num1str = " ".to_string();

        println!("Enter the second number: ");
        io::stdin().read_line(& mut num2str).expect("please enter a string");
        num2 = num2str.trim().parse::<i32>().unwrap();
        num2str = " ".to_string();

        correctoperator = false;
        while correctoperator == false{
            println!("Enter the operator (+,-,*, or /)");
            io::stdin().read_line(& mut operator).expect("please enter a string");
            correctoperator = true;

            if operator.trim() == "+" { 
                result = add(num1,num2);
            }
            else if operator.trim() == "-" { 
                result = subtract(num1,num2);
            }
            else if operator.trim() == "*" { 
                result = multiply(num1,num2);
            }
            else if operator.trim() == "/" { 
                result = divide(num1,num2);
            }
            else{
                println!("That is not a valid operator");
                result = 0;
                correctoperator = false;
            }
            operator = " ".to_string();
        }

        println!("______________");
        println!("{} {} {} = {}", num1, operator.trim(), num2, result);

        println!("Contiue calculating? (Type y to continue)");
        io::stdin().read_line(& mut continuestr).expect("please enter a string");
        if continuestr.trim() != "y"{
            continuebool = false;
        }
        continuestr = " ".to_string();
    }
}

//adds two integers and returns the result
fn add(num1: i32, num2: i32)->i32{
    return num1+num2;
}

//subtracts two integers and returns the result
fn subtract(num1: i32, num2: i32)->i32{
    return num1-num2;
}

//multiplies two integers and returns the result
fn multiply(num1: i32, num2: i32)->i32{
    return num1*num2;
}

//divides two integers and returns the result
fn divide(num1: i32, num2: i32)->i32{
    return num1/num2;
}