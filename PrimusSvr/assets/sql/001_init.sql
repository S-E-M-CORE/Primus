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
    name VARCHAR(50)
);

-- Insert departments if not already present
INSERT into Department (id, name) VALUES
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
    notes TEXT
);



-- junction tables


CREATE TABLE Address_Member (
    address_id INTEGER,
    member_id INTEGER,
    PRIMARY KEY (address_id, member_id),
    FOREIGN KEY (address_id) REFERENCES Address(id),
    FOREIGN KEY (member_id) REFERENCES Member(id)
);

CREATE TABLE Department_Member (
    department_id INTEGER,
    member_id INTEGER,
    PRIMARY KEY (department_id, member_id),
    FOREIGN KEY (department_id) REFERENCES Department(id),
    FOREIGN KEY (member_id) REFERENCES Member(id)
);

CREATE TABLE Training_Member (
    training_id INTEGER,
    member_id INTEGER,
    PRIMARY KEY (training_id, member_id),
    FOREIGN KEY (training_id) REFERENCES Training(id),
    FOREIGN KEY (member_id) REFERENCES Member(id)
);

CREATE TABLE Department_Training (
    department_id INTEGER,
    training_id INTEGER,
    PRIMARY KEY (department_id, training_id),
    FOREIGN KEY (department_id) REFERENCES Department(id),
    FOREIGN KEY (training_id) REFERENCES Training(id)
);

CREATE VIEW AllData AS
SELECT 
    A.id AS address_id,
    A.zipCode,
    A.city,
    A.state,
    A.houseNumber,
    A.street,
    D.id AS department_id,
    D.name AS department_name,
    M.id AS member_id,
    M.firstName AS member_firstName,
    M.lastName AS member_lastName,
    M.email AS member_email,
    M.phoneNumber AS member_phoneNumber,
    M.birthDate AS member_birthDate,
    M.createDate AS member_createDate,
    M.notes AS member_notes,
    M.active AS member_active,
    T.id AS training_id,
    T.date AS training_date,
    T.createDate AS training_createDate,
    T.notes AS training_notes
FROM 
    Address A
LEFT JOIN 
    Address_Member AM ON A.id = AM.address_id
LEFT JOIN 
    Member M ON AM.member_id = M.id
LEFT JOIN 
    Department_Member DM ON M.id = DM.member_id
LEFT JOIN 
    Department D ON DM.department_id = D.id
LEFT JOIN 
    Training_Member TM ON M.id = TM.member_id
LEFT JOIN 
    Training T ON TM.training_id = T.id;
