-- Address table
CREATE TABLE Address (
    id          INTEGER PRIMARY KEY,
    postalCode  VARCHAR(10),
    city        VARCHAR(100),
    country     CHAR(50),
    houseNumber INTEGER,
    street      VARCHAR(255)
);

-- Department table
CREATE TABLE Department (
    id      INTEGER PRIMARY KEY,
    name    VARCHAR(50) UNIQUE
);

-- Insert departments if not already present
INSERT INTO Department (id, name) VALUES (1, 'Bogenschiessen'), (2, 'Luftdruck'), (3, 'Schusswaffen');


-- Member table
CREATE TABLE Member (
    id          INTEGER PRIMARY KEY,
    firstName   VARCHAR(100),
    lastName    VARCHAR(100),
    email       VARCHAR(255),
    phoneNumber VARCHAR(100),
    birthDate   DATE,
    createDate  DATE,
    notes       TEXT,
    active      BOOLEAN
);

-- Attendance table
CREATE TABLE Attendance (
    id              INTEGER PRIMARY KEY,
    date            DATE,

    dateOfCreation  DATE,

);



-- junction tables


CREATE TABLE Address_Member (
    address_id          INTEGER,
    member_id           INTEGER,
    PRIMARY KEY (address_id, member_id),
    FOREIGN KEY (address_id) REFERENCES Address(id),
    FOREIGN KEY (member_id) REFERENCES Member(id)
);

CREATE TABLE Department_Member (
    department_id       INTEGER,
    member_id           INTEGER,
    PRIMARY KEY (department_id, member_id),
    FOREIGN KEY (department_id) REFERENCES Department(id),
    FOREIGN KEY (member_id) REFERENCES Member(id)
);

CREATE TABLE Member_Attendance (
    member_id                   INTEGER,
    attendance_id               INTEGER,
    PRIMARY KEY (member_id, attendance_id),
    FOREIGN KEY (member_id)     REFERENCES Member(id),
    FOREIGN KEY (attendance_id) REFERENCES Attendance(id)
);

CREATE TABLE Training_Department (
    training_id         INTEGER,
    department_id       INTEGER,
    PRIMARY KEY (training_id, department_id),
    FOREIGN KEY (training_id) REFERENCES Training(id),
    FOREIGN KEY (department_id) REFERENCES Department(id)
);
