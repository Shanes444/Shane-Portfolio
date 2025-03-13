--PART 2
-- Bradley Prokop, Trevor Leamon , Shane Stevens
CREATE TABLE course (
    courseID INTEGER PRIMARY KEY,
    courseName VARCHAR(50) NOT NULL,
    creditHours INTEGER NOT NULL, 
    department VARCHAR(50) NOT NULL
);

CREATE TABLE professor (
    professorID INTEGER PRIMARY KEY,
    profFirstName VARCHAR(50) NOT NULL,
    profLastName VARCHAR(50) NOT NULL,
    email VARCHAR(50)
);

CREATE TABLE courseSection (
     sectionID INTEGER PRIMARY KEY,
     classTime VARCHAR(50) NOT NULL,
     classLocation VARCHAR(50) NOT NULL,
     textbook VARCHAR(50),
     courseID INTEGER,
     professorID INTEGER,
     FOREIGN KEY (courseID)  REFERENCES course (courseID),
     FOREIGN KEY (professorID) REFERENCES professor (professorID)
);


CREATE TABLE student (
    studentID INTEGER PRIMARY KEY,
    firstName VARCHAR(50) NOT NULL,
    lastName VARCHAR(50) NOT NULL,
    major VARCHAR(50),
    gpa FLOAT(2),
    sectionID INTEGER,
    FOREIGN KEY (sectionID) REFERENCES courseSection (sectionID)
);  

-- PART 3
-- Trevor Eagleton, Bradley Prokop 
INSERT ALL
INTO professor (professorID, profFirstName, profLastName, email) VALUES (1, 'Angel', 'hernandez', 'Ahern@ilstu.edu')
INTO professor (professorID, profFirstName, profLastName, email) VALUES (2, 'Vance', 'Gilligan', 'Vgilli@ilstu.edu')
INTO professor (professorID, profFirstName, profLastName, email) VALUES (3, 'Nacho', 'Varga', 'Nvarga@ilstu.edu')
INTO professor (professorID, profFirstName, profLastName, email) VALUES (4, 'Jesse', 'Pinkman', 'Jpink@ilstu.edu')
INTO professor (professorID, profFirstName, profLastName, email) VALUES (5, 'Walter', 'White', 'Wwhite@ilstu.edu')
INTO professor (professorID, profFirstName, profLastName, email) VALUES (6, 'Micheal', 'Mire', 'Mmire@ilstu.edu')
INTO professor (professorID, profFirstName, profLastName, email) VALUES (7, 'Saul', 'Goodman', 'Sgood@ilstu.edu')
INTO professor (professorID, profFirstname, profLastName, email) VALUES (8, 'Mike', 'Ehrmantraut', 'Merm@ilstu.edu')
INTO professor (professorID, profFirstname, profLastName, email) VALUES (9, 'Steven', 'Harvey', 'SHarv@ilstu.edu')
INTO professor (professorID, profFirstname, profLastName, email) VALUES(10, 'Kevin', 'Smith', 'Kevsmith@ilstu.edu')
Select * FROM dual;

-- Trevor Leamon, Cam Nemeth 
INSERT ALL
INTO course (courseID, courseName, creditHours, department) VALUES (1, 'Database Processing', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (2, 'Web Development', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (3, 'Advanced Web Development', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (4, 'Intro to Application Programming', 4, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (5, 'Ethics in IT', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (6, 'Hardware and Software Concepts', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (7, 'Systems Development I', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (8, 'IT Project Management', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (9, 'Mobile & Cloud Computing', 3, 'IT')
INTO course (courseID, courseName, creditHours, department) VALUES (10, 'Telecommunications', 3, 'IT')
Select * FROM dual;

-- CAM NEMETH 
INSERT ALL
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (1, '12:00 PM', 'Julian Hall', 'Processing Data', 1, 1)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (2, '1:00 PM', 'Old Union', 'Developing the Web',  2, 2)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (3, '12:35 PM', 'Julian Hall', 'Developing the Web: Advanced', 3, 3)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (4, '12:45 PM', 'Old Union', 'Programming for Beginners', 4, 4)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (5, '11:05 AM', 'Schroeder Hall', 'IT Ethics', 5, 5)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (6, '1:25 PM', 'Hovey Hall', 'Computer Hardware',  6, 6)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (7, '8:00 AM', 'Fell Hall', 'Developing the Web', 2, 6)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (8, '9:00 AM', 'Julian Hall', 'Project Management in IT', 8, 8)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (9, '10:30 AM', 'Old Union', 'Cloud Computing', 9, 9)
INTO courseSection (sectionID, classTime, classLocation, textbook, courseID, professorID) VALUES (10, '10:00 AM', 'Schroeder Hall', 'IT Ethics', 5, 5)
Select * FROM dual;

-- Trevor Eagleton, Shane Stevens
INSERT  ALL
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (2, 'Steve', 'Jobs', 'Computer science', 4.0, 1)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (1, 'Trevor', 'Eagleton', 'Cybersecurity', 2.9, 2)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (3, 'Jim','Jackson', 'Computer science', 3.5, 3)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (4, 'Mason', 'Many', 'Cybersecurity', 3.0, 4) 
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (5, 'Bobby', 'Joseph', 'Geology', 3.7, 5)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (6, 'Steven', 'Mary', 'Mathematics', 2.7, 6)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (7, 'Peter', 'Parker', 'photography', 3.9, 7)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (8, 'Bill', 'Butcher', 'Geology', 3.5, 8)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (9, 'Nancy', 'Fellhart', 'mathematics', 3.6, 9)
INTO student (studentID, firstName, lastName, major, gpa, sectionID) VALUES (10, 'Ethan', 'Earthheart', 'Computer science', 3.5, 10)
Select * FROM dual;
