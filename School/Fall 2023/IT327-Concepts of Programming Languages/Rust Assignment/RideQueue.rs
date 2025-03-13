/**  Complex Program
 * IT 327 Fall 2023
 * By Derek Jennings & Shane Stevens
 * A virtual queue for a ride at a theme park
 *  Allows for fast passes, making it a priority queue
 *  Calculates wait time
 * Main program allows for user input to control an instance of the queue
 */

use std::io;

//contains information about people in line
struct SpotInLine {
    pub id: u32,
    pub fast: bool,

}

// A container which holds a vector of nodes which represent people waiting
// Methods:
//  is_empty()
//  size()
//  enqueue(SpotInLine)
//  dequeue()
//  get_wait_time(fast_pass)
//  print_queue_info()
//  print_entire_queue()

struct RideQueue {
    pub spots: Vec<SpotInLine>,
    pub last_fast: usize,
    pub ride_time: f32,
    total_spots_today: u32
}

// Initialize a queue with default values, including default ride time of 1 minute
impl Default for RideQueue {
    fn default() -> Self { RideQueue {spots: Vec::new(), total_spots_today: 0, last_fast: 0, ride_time: 1.0} }
}

impl RideQueue {
    /// Returns true if there is nobody in line
    fn is_empty(&self) -> bool {
        self.spots.is_empty()
    }

    /// Returns the size of the queue
    fn size(&self) -> usize {
        self.spots.len()
    }

    /// Adds a spot to the end of the line
    fn enqueue(& mut self, fast_pass: bool) {
        self.total_spots_today += 1;
        let new_spot = SpotInLine {id: self.total_spots_today, fast: fast_pass};
        if fast_pass {
            if  self.last_fast >= 3 && 
                self.spots[self.last_fast-1].fast && 
                self.spots[self.last_fast-2].fast && 
                self.spots[self.last_fast-3].fast {
                    
                if self.last_fast >= self.spots.len() {
                    self.last_fast += 1;
                } else {
                    self.last_fast += 2;
                }
                println!("{}", self.last_fast);
                self.spots.insert(self.last_fast-1, new_spot);
            }
            else{
                self.last_fast += 1;
                self.spots.insert(self.last_fast - 1, new_spot);
            }
            //print!("{} ", self.last_fast);
        }
        else{
            self.spots.push(new_spot);
        }
    }

    //removes the front node of the list 
    fn dequeue(& mut self) {
        if !self.is_empty() {
            self.spots.pop();
            if self.last_fast > 0 {
                self.last_fast -= 1;
            }  
        }
    }

    //returns the wait times
    fn get_wait_time(&self, fast_pass: bool) -> f32 {
        if !fast_pass {
            self.size() as f32 * self.ride_time
        } else {
            if self.last_fast == 0{
                0.0
            }
            else{
               (self.last_fast) as f32 * self.ride_time 
            }   
        }
    }

    //prints the wait times
    fn print_queue_info(&self) {
        println!("There are {} people in line.", self.size());
        println!("Estimated wait time: {:.1} minutes, or {:.1} minutes for fastpass holders.", self.get_wait_time(false), self.get_wait_time(true));
    }

    //prins the ids and fast pass status of everyone in line
    fn print_entire_queue(&self) {
        for i in 0..self.size() {
            print!("{}", self.spots[i].id);
            if self.spots[i].fast {
                print!("f ");
            } else {
                print!("s ");
            }
        }
        println!("");
    }
}

fn main() {
    let mut ride: RideQueue = Default::default();
    let mut input: String;
    let mut is_running = true;
    
    while is_running == true{
        input = "".to_string();
        println!("Please choose an option by typing the corresponding number");
        println!("1. change the time it takes to ride");
        println!("2. add a person to the line without a fast pass");
        println!("3. add a person to the line with a fast pass");
        println!("4. display information");
        println!("5. have a person get on the ride");
        println!("6. exit");
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let str_input = input.trim();
        
        match str_input {
            //change ride time
            "1" => {
                input = "".to_string();
                // Take a numeric value (float) to use as the new ride time
                println!("enter new time: ");
                io::stdin().read_line(&mut input).expect("Failed to read line");
                match input.trim().parse::<f32>() {
                    Ok(parsed_float) => {
                        ride.ride_time = parsed_float;
                    } Err(err) => {
                        println!("Error parsing float: {}", err);
                    }
                }
            },
            //add non fastpass person
            "2" => {
                ride.enqueue(false)
            },
            //add fastpass person
            "3" => {
                ride.enqueue(true);
            },
            //display information
            "4" => {
                ride.print_queue_info();
            },
            //have person get on ride
            "5" => {
                ride.dequeue()
            },
            // Exit
            "6" => {
                is_running = false;
            },
            // Else
            _ => {
                println!("Could not parse input, please try again.");
            }
        }
        ride.print_entire_queue();      
        println!(" ");
    }
}
