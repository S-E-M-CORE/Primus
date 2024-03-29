-- Address table
CREATE TABLE Address (
    id INTEGER PRIMARY KEY,
    zipCode VARCHAR(255),
    city VARCHAR(255),
    state VARCHAR(255),
    houseNumber VARCHAR(255),
    street VARCHAR(255)
);

-- Department table
CREATE TABLE Department (
    id INTEGER PRIMARY KEY,
    name VARCHAR(255),
    active BOOLEAN
);

-- Email table
CREATE TABLE Email (
    id INTEGER PRIMARY KEY,
    email VARCHAR(255)
);

-- Member table
CREATE TABLE Member (
    id INTEGER PRIMARY KEY,
    firstName VARCHAR(255),
    lastName VARCHAR(255),
    birthDate VARCHAR(255),
    joinDate VARCHAR(255),
    active BOOLEAN
);

INSERT INTO Member
(firstName, lastName, birthDate, joinDate, active) VALUES ('Max', 'Mustermann', '0003-02-01', '0003-02-03', 1);

-- Membership table
CREATE TABLE Membership (
    id INTEGER PRIMARY KEY,
    membershipFee FLOAT,
    active BOOLEAN
);

-- PhoneNumber table
CREATE TABLE PhoneNumber (
    id INTEGER PRIMARY KEY,
    number VARCHAR(255)
);

-- Training table
CREATE TABLE Training (
    id INTEGER PRIMARY KEY,
    date VARCHAR(255),
    startTime VARCHAR(255),
    room VARCHAR(255),
    notes VARCHAR(255)
);

-- Junction tables

-- MemberAddressRel table
CREATE TABLE MemberAddressRel (
    memberID INTEGER,
    addressID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (addressID) REFERENCES Address(id),
    PRIMARY KEY (memberID, addressID)
);

-- MemberEmailRel table
CREATE TABLE MemberEmailRel (
    memberID INTEGER,
    emailID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (emailID) REFERENCES Email(id),
    PRIMARY KEY (memberID, emailID)
);

-- MemberPhoneNumberRel table
CREATE TABLE MemberPhoneNumberRel (
    memberID INTEGER,
    phoneNumberID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (phoneNumberID) REFERENCES PhoneNumber(id),
    PRIMARY KEY (memberID, phoneNumberID)
);

-- MemberMembershipRel table
CREATE TABLE MemberMembershipRel (
    memberID INTEGER,
    membershipID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (membershipID) REFERENCES Membership(id),
    PRIMARY KEY (memberID, membershipID)
);

-- MembershipDepartmentRel table
CREATE TABLE MembershipDepartmentRel (
    membershipID INTEGER,
    departmentID INTEGER,
    FOREIGN KEY (membershipID) REFERENCES Membership(id),
    FOREIGN KEY (departmentID) REFERENCES Department(id),
    PRIMARY KEY (membershipID, departmentID)
);

-- MemberTrainingRel table
CREATE TABLE MemberTrainingRel (
    memberID INTEGER,
    trainingID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (trainingID) REFERENCES Training(id),
    PRIMARY KEY (memberID, trainingID)
);

-- DepartmentTrainingRel table
CREATE TABLE DepartmentTrainingRel (
    departmentID INTEGER,
    trainingID INTEGER,
    FOREIGN KEY (departmentID) REFERENCES Department(id),
    FOREIGN KEY (trainingID) REFERENCES Training(id),
    PRIMARY KEY (departmentID, trainingID)
);
