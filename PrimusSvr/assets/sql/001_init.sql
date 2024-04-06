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
    member_id   INTEGER,
    date        DATE,
    PRIMARY KEY (member_id, date),
    FOREIGN KEY (member_id) REFERENCES Member(id)
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


-- Test cases

-- Address table
INSERT INTO Address (postalCode, city, country, houseNumber, street) 
VALUES 
    ('12345', 'Musterstadt', 'Germany', 123, 'Musterstrasse'),
    ('54321', 'Beispielstadt', 'USA', 456, 'Beispielweg');

-- Member table
INSERT INTO Member (firstName, lastName, email, phoneNumber, birthDate, createDate, notes, active) 
VALUES 
    ('Max', 'Mustermann', 'max@example.com', '123-456-7890', '1990-01-01', '2020-01-01', 'Notizen fuer Max', 1),
    ('Maria', 'Musterfrau', 'maria@example.com', '987-654-3210', '1995-05-05', '2020-01-01', 'Notizen fuer Maria', 1),
    ('John', 'Doe', 'john@example.com', '555-555-5555', '1980-12-31', '2020-01-01', 'Notizen fuer John', 0);

-- Attendance table
INSERT INTO Attendance (member_id, date) 
VALUES 
    (1, '2024-04-01'),
    (2, '2024-04-01'),
    (1, '2024-04-02');

-- Address_Member junction table
INSERT INTO Address_Member (address_id, member_id) 
VALUES 
    (1, 1),
    (2, 2),
    (1, 2);

-- Department_Member junction table
INSERT INTO Department_Member (department_id, member_id) 
VALUES 
    (1, 1),
    (2, 2),
    (3, 1);