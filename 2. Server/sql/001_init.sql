-- Address table
CREATE TABLE Address (
    id INTEGER PRIMARY KEY,
    zipCode VARCHAR(10),
    city VARCHAR(100),
    state CHAR(2),
    houseNumber VARCHAR(10),
    street VARCHAR(255)
);

-- Department table
CREATE TABLE Department (
    id INTEGER PRIMARY KEY,
    name VARCHAR(100),
    active BOOLEAN
);

-- Member table
CREATE TABLE Member (
    id INTEGER PRIMARY KEY,
    firstName VARCHAR(100),
    lastName VARCHAR(100),
    email VARCHAR(255),
    phoneNumber VARCHAR(100),
    birthDate DATE,
    createDate DATE,
    active BOOLEAN
);

-- Membership table
CREATE TABLE Membership (
    id INTEGER PRIMARY KEY,
    membershipFee DECIMAL(10,2),
    active BOOLEAN
);

-- Training table
CREATE TABLE Training (
    id INTEGER PRIMARY KEY,
    date DATE,
    startTime TIME,
    room VARCHAR(100),
    notes TEXT
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