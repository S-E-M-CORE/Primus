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
CREATE TABLE IF NOT EXISTS Department (
    id INTEGER PRIMARY KEY,
    name VARCHAR(50)
);
-- Insert departments if not already present
INSERT OR IGNORE INTO Department (id, name) VALUES
    (1, 'Bogenschieﬂen'),
    (2, 'Luftdruck'),
    (3, 'Schusswaffen');


-- Member table
CREATE TABLE Member (
    id INTEGER PRIMARY KEY,
    firstName VARCHAR(100),
    lastName VARCHAR(100),
    email VARCHAR(255),
    phoneNumber VARCHAR(100),
    birthDate DATE,
    createDate DATE,
    notes TEXT,
    active BOOLEAN
);

-- Training table
CREATE TABLE Training (
    id INTEGER PRIMARY KEY,
    date DATE,
    createDate DATE,
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

-- MemberTrainingRel table
CREATE TABLE MemberTrainingRel (
    memberID INTEGER,
    trainingID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (trainingID) REFERENCES Training(id),
    PRIMARY KEY (memberID, trainingID)
);

CREATE TABLE MemberDepartmentRel (
    memberID INTEGER,
    departmentID INTEGER,
    FOREIGN KEY (memberID) REFERENCES Member(id),
    FOREIGN KEY (departmentID) REFERENCES Department(id),
    PRIMARY KEY (memberID, departmentID)
);

CREATE VIEW MemberDetails AS
SELECT m.id AS memberID, 
       m.firstName, 
       m.lastName, 
       m.email, 
       m.phoneNumber, 
       m.birthDate, 
       m.createDate AS memberCreateDate, 
       m.active, 
       a.id AS addressID, 
       a.zipCode, 
       a.city, 
       a.state, 
       a.houseNumber, 
       a.street, 
       d.id AS departmentID, 
       d.name AS departmentName
FROM Member m
JOIN MemberAddressRel mar ON m.id = mar.memberID
JOIN Address a ON mar.addressID = a.id
JOIN MemberDepartmentRel mdr ON m.id = mdr.memberID
JOIN Department d ON mdr.departmentID = d.id;
