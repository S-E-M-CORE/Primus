



// let client = new PrimusApiClient('http://localhost:8000');

// /*
// Wir extraieren/lesen die infomationen die der Benutzer in unseren Feldern hinterlegt hat.
// */
// async function getUserInput() 
// {
//     // Benutzereingaben erfassen
//     let firstName = document.getElementById("firstName").value;
//     let lastName = document.getElementById("LastName").value;
//     let birthDate = document.getElementById("birth_date").value;
//     let postalCode = document.getElementById("Poz").value;
//     let residence = document.getElementById("residence").value;
//     let street = document.getElementById("street").value;
//     let houseNumber = document.getElementById("H_Number").value;
//     let email = document.getElementById("Member_email").value;
//     let phoneNumber = document.getElementById("TeleNumber").value;
//     let joinDate = document.getElementById("date").value;
//     let notes = document.querySelector("textarea").value;
//     let membership = document.querySelector("select").value;


//     /*
//     Alle Eingaben sollen in einem Objekt gespeichert werden. So das sie zur Erstellung eines Members benutzt werden können.
//     */ 
//     let memberData = 
//     {
//         // Benutzereingaben in einem Objekt speichern
//         firstName: firstName,
//         lastName: lastName,
//         birthDate: birthDate,
//         postalCode: postalCode,
//         residence: residence,
//         street: street,
//         houseNumber: houseNumber,
//         email: email,
//         phoneNumber: phoneNumber,
//         joinDate: joinDate,
//         notes: notes,
//         membership: membership
//     };

//     uploadMember(memberData)
// }

// async function uploadMember(memberData)
// {

// let MemberId = 2;

// // Member erstellen und in der Datenbank speichern
// try 
// {
//     // Member erstellen und Antwort abwarten
//     let response = await client.updateMember(MemberId, memberData);
//     // Antwort verarbeiten (z. B. Erfolg oder Fehlermeldung anzeigen)
//     console.log(response);
// } 
// catch (error) 
// {
//     console.error("Fehler beim Erstellen des Mitglieds:", error);
// }
// }






// // Event-Listener für den Button hinzufügen
// //document.getElementById("resultButton").addEventListener("click", getUserInput);
